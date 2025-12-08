#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"

// Qt de base
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QVBoxLayout>

// Pour PDF
#include <QPdfWriter>
#include <QPainter>

// QtCharts
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>

// QtLocation / QQuickWidget
#include <QtLocation/QGeoServiceProvider>
#include <QtLocation/QGeoCodingManager>
#include <QtLocation/QGeoCodeReply>
#include <QtPositioning/QGeoCoordinate>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQuickItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

// ----------------------------------------------------------------
// Constructeur
// ----------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Charger les données SQL
    chargerClientsDepuisSQL();
    genererStatistiquesCRUD();
    checkAnniversaire();

    // -----------------------------
    // CONFIGURATION DU WIDGET CARTE
    // -----------------------------

    // Supprimer l’ancien layout si présent (évite les doublons)
    if (ui->widget_map->layout()) {
        delete ui->widget_map->layout();
    }

    // Nouveau layout propre
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    ui->widget_map->setLayout(layout);

    // Création du QQuickWidget
    m_mapWidget = new QQuickWidget(ui->widget_map);
    m_mapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Important pour Qt 6 (chargement QML dans resources)
    m_mapWidget->engine()->addImportPath("qrc:/");

    // Charger la carte QML
    m_mapWidget->setSource(QUrl("qrc:/MapView.qml"));

    // Ajouter au layout
    layout->addWidget(m_mapWidget);

    // Activation réseau
    networkManager = new QNetworkAccessManager(this);

    // Appuyer sur le bouton → localisation
    connect(ui->btn_localisation, &QPushButton::clicked,
            this, &MainWindow::on_btn_localisation_clicked);

    // Quand QML est complètement chargé, on centre la carte
    connect(m_mapWidget, &QQuickWidget::statusChanged, this, [this](QQuickWidget::Status status) {
        if (status == QQuickWidget::Ready) {
            QQuickItem *root = m_mapWidget->rootObject();
            if (root) {
                QMetaObject::invokeMethod(root, "setCenter",
                                          Q_ARG(QVariant, 36.8),
                                          Q_ARG(QVariant, 10.2));
            }
        }
    });
}


// ----------------------------------------------------------------
// Destructeur
// ----------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

// ----------------------------------------------------------------
// SLOT : Ajouter un client
// ----------------------------------------------------------------
void MainWindow::on_pushButton_ajouter_clicked()
{
    QString idStr = ui->lineEdit_id->text();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString tel = ui->lineEdit_telephone->text();
    QDate dateN = ui->dateEdit_naissance->date();

    QRegularExpression regexNom("^[A-Za-z]{4,}$");
    QRegularExpression regexTel("^[0-9]{8}$");
    QRegularExpression regexEmail("^[A-Za-z0-9._%+-]+@gmail\\.com$");
    QRegularExpression regexId("^[0-9]+$");

    if (!regexId.match(idStr).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir uniquement des chiffres.");
        return;
    }
    if (!regexNom.match(nom).hasMatch() || !regexNom.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le nom et le prénom doivent contenir au moins 4 lettres alphabétiques.");
        return;
    }
    if (!regexTel.match(tel).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit contenir exactement 8 chiffres.");
        return;
    }
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "L'email doit être une adresse Gmail valide.");
        return;
    }

    int id = idStr.toInt();
    Client c(id, nom, prenom, email, tel, dateN);

    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès !");
        chargerClientsDepuisSQL();        // 🔄 Recharger clients
        genererStatistiquesCRUD();        // 🔄 Mettre à jour graphique
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client. Vérifiez que l'ID est unique.");
    }
}

// ----------------------------------------------------------------
// SLOT : Afficher tous les clients
// ----------------------------------------------------------------
void MainWindow::on_pushButton_afficher_clicked()
{
    Client c;
    ui->tableView_client->setModel(c.afficher());
}

// ----------------------------------------------------------------
// SLOT : Supprimer un client
// ----------------------------------------------------------------
void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_id_supprimer->text().toInt();
    Client c;

    if (c.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Client supprimé avec succès !");
        chargerClientsDepuisSQL();
        genererStatistiquesCRUD();
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression du client.");
    }
}

// ----------------------------------------------------------------
// SLOT : Chercher client par ID
// ----------------------------------------------------------------
void MainWindow::on_pushButton_chercher_clicked()
{
    QString idStr = ui->lineEdit_id_recherche->text().trimmed();
    if(idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID !");
        return;
    }
    int id = idStr.toInt();
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENTS, NOM, PRENOM, MAIL, NUM, DATE_NAISSANCE FROM CLIENTS WHERE ID_CLIENTS=:id");
    query.bindValue(":id", id);
    if(!query.exec()) return;

    if(query.next()) {
        ui->lineEdit_id_modif->setText(query.value(0).toString());
        ui->lineEdit_nom_modif->setText(query.value(1).toString());
        ui->lineEdit_prenom_modif->setText(query.value(2).toString());
        ui->lineEdit_email_modif->setText(query.value(3).toString());
        ui->lineEdit_telephone_modif->setText(query.value(4).toString());
        ui->dateEdit_naissance_modif->setDate(query.value(5).toDate());
        QMessageBox::information(this, "Résultat", "Client trouvé !");
    } else {
        QMessageBox::warning(this, "Erreur", "Aucun client trouvé avec cet ID.");
    }
}

// ----------------------------------------------------------------
// SLOT : Sauvegarder (modifier) client
// ----------------------------------------------------------------
void MainWindow::on_pushButton_sauvegarder_clicked()
{
    int id = ui->lineEdit_id_modif->text().toInt();
    QString nom = ui->lineEdit_nom_modif->text();
    QString prenom = ui->lineEdit_prenom_modif->text();
    QString email = ui->lineEdit_email_modif->text();
    QString tel = ui->lineEdit_telephone_modif->text();
    QDate dateN = ui->dateEdit_naissance_modif->date();

    Client c(id, nom, prenom, email, tel, dateN);
    if (c.modifier())
        QMessageBox::information(this, "Succès", "Modification enregistrée !");
    else
        QMessageBox::warning(this, "Erreur", "Échec de la modification.");
}

// ----------------------------------------------------------------
// SLOT : Recherche par nom
// ----------------------------------------------------------------
void MainWindow::on_pushButton_rechercheNom_clicked()
{
    QString nom = ui->lineEdit_rechercheNom->text().trimmed();
    if(nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un nom !");
        return;
    }
    Client c;
    ui->tableView_recherche->setModel(c.rechercherParNom(nom));
}

// ----------------------------------------------------------------
// SLOT : Inscrire client à un événement
// ----------------------------------------------------------------
void MainWindow::on_pushButton_inscrire_clicked()
{
    QString idClient = ui->lineEdit_id_client->text();
    QString idEvent = ui->lineEdit_id_evenement->text();
    QDateTime dateInscription = ui->dateTimeEdit_inscription->dateTime();

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Clients WHERE id_clients = :id");
    query.bindValue(":id", idClient);
    query.exec();
    query.next();
    if(query.value(0).toInt() == 0) {
        QMessageBox::warning(this,"Erreur","L'ID client n'existe pas.");
        return;
    }

    query.prepare("SELECT COUNT(*) FROM Evenements WHERE id_evenements = :id");
    query.bindValue(":id", idEvent);
    query.exec();
    query.next();
    if(query.value(0).toInt() == 0) {
        QMessageBox::warning(this,"Erreur","L'ID événement n'existe pas.");
        return;
    }

    QSqlQuery insert;
    insert.prepare("INSERT INTO INSCRIPTIONS (id_client, id_event, date_inscription) "
                   "VALUES (:id_client, :id_event, :date_ins)");
    insert.bindValue(":id_client", idClient);
    insert.bindValue(":id_event", idEvent);
    insert.bindValue(":date_ins", dateInscription);

    if(insert.exec()) {
        QMessageBox::information(this,"Succès","Client inscrit avec succès !");
    } else {
        QMessageBox::critical(this,"Erreur SQL", insert.lastError().text());
    }
}

// ----------------------------------------------------------------
// Export PDF
// ----------------------------------------------------------------
void MainWindow::exportPDF(QSqlQueryModel *model)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Télécharger PDF", "", "PDF Files (*.pdf)");
    if(fileName.isEmpty()) return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);
    QPainter painter(&pdf);
    if(!painter.isActive()) return;

    int pageWidth = pdf.width();
    int pageMargin = 60;
    int colWidth = (pageWidth-2*pageMargin)/model->columnCount();
    int rowHeight = 45;
    int x = pageMargin;
    int y = 150;

    painter.setFont(QFont("Arial",22,QFont::Bold));
    QString title = "Liste des Clients";
    int titleWidth = painter.fontMetrics().horizontalAdvance(title);
    painter.drawText((pageWidth-titleWidth)/2,100,title);

    painter.setFont(QFont("Arial",12,QFont::Bold));
    painter.setPen(Qt::black);
    painter.setBrush(QColor(230,230,230));
    painter.drawRect(x,y,colWidth*model->columnCount(),rowHeight);
    for(int col=0;col<model->columnCount();col++) {
        QRect rect(x+col*colWidth,y,colWidth,rowHeight);
        painter.drawRect(rect);
        painter.drawText(rect.adjusted(8,0,-8,0),Qt::AlignVCenter|Qt::AlignLeft,
                         model->headerData(col,Qt::Horizontal).toString());
    }
    y+=rowHeight;
    painter.setFont(QFont("Arial",11));
    painter.setBrush(Qt::NoBrush);

    for(int row=0; row<model->rowCount(); row++) {
        for(int col=0; col<model->columnCount(); col++) {
            QRect rect(x+col*colWidth,y,colWidth,rowHeight);
            painter.drawRect(rect);
            QString text = model->data(model->index(row,col)).toString();
            painter.drawText(rect.adjusted(8,0,-8,0),Qt::AlignVCenter|Qt::AlignLeft,text);
        }
        y+=rowHeight;
        if(y > pdf.height()-100) { pdf.newPage(); y=150; }
    }
    painter.end();
}

void MainWindow::on_pushButtonpdf_clicked()
{
    Client c;
    QSqlQueryModel *model = c.afficher();
    exportPDF(model);
}

void MainWindow::on_pushButton_trier_clicked()
{
    Client c;
    ui->tableView_client->setModel(c.afficherTri());
}

// ----------------------------------------------------------------
// Anniversaire
// ----------------------------------------------------------------
void MainWindow::checkAnniversaire()
{
    QSqlQuery query = tmpClient.getAnniversairesDuJour();
    while(query.next()) {
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString message = QString("🎉 Aujourd'hui c'est l'anniversaire de :\n\n%1 %2\nID : %3")
                              .arg(nom).arg(prenom).arg(id);
        QMessageBox::information(this,"Anniversaire",message);
    }
}

// ----------------------------------------------------------------
// Recommandation atelier
// ----------------------------------------------------------------
void MainWindow::on_pushButton_verifier_clicked()
{
    QString idStr = ui->lineEdit_id_client_reco->text().trimmed();
    if(idStr.isEmpty()) {
        QMessageBox::warning(this,"Erreur","Veuillez entrer un ID !");
        return;
    }
    bool ok;
    int id = idStr.toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this,"Erreur","ID invalide !");
        return;
    }
    QString message = tmpClient.recommanderAtelier(id);
    ui->label_reco->setText(message);
}

// ----------------------------------------------------------------
// Localisation
// ----------------------------------------------------------------
void MainWindow::on_btn_localisation_clicked()
{
    QString idEvent = ui->lineEdit_id_evenement->text();
    QSqlQuery query;
    query.prepare("SELECT NOM,LIEU FROM EVENEMENTS WHERE ID_EVENEMENTS=:id");
    query.bindValue(":id",idEvent);
    if(!query.exec() || !query.next()) {
        QMessageBox::warning(this,"Erreur","Événement introuvable !");
        return;
    }

    QString nomEvent = query.value(0).toString();
    QString lieu = query.value(1).toString();

    QString url = QString("https://nominatim.openstreetmap.org/search?format=json&q=%1").arg(lieu);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader,"Qt App");
    QNetworkReply *reply = networkManager->get(request);

    connect(reply,&QNetworkReply::finished,this,[this,reply,nomEvent](){
        if(reply->error() != QNetworkReply::NoError) {
            QMessageBox::warning(this,"Erreur","Impossible de récupérer la localisation !");
            reply->deleteLater();
            return;
        }
        QByteArray data = reply->readAll();
        reply->deleteLater();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(!doc.isArray() || doc.array().isEmpty()) {
            QMessageBox::warning(this,"Erreur","Adresse introuvable !");
            return;
        }

        QJsonObject obj = doc.array().first().toObject();
        double lat = obj["lat"].toString().toDouble();
        double lon = obj["lon"].toString().toDouble();

        QQuickItem *rootItem = m_mapWidget->rootObject();
        if(rootItem) {
            QMetaObject::invokeMethod(rootItem,"setCenter",Q_ARG(QVariant,lat),Q_ARG(QVariant,lon));
            QMetaObject::invokeMethod(rootItem,"addMarker",Q_ARG(QVariant,lat),Q_ARG(QVariant,lon));
        }

        QMessageBox::information(this,"Localisation",
                                 QString("Localisation de \"%1\" affichée sur la carte.").arg(nomEvent));
    });
}

// ----------------------------------------------------------------
// Actualiser statistiques
// ----------------------------------------------------------------
void MainWindow::onActualiserStatsClicked()
{
    qDebug() << "=== ACTUALISATION STATISTIQUES ===";
    chargerClientsDepuisSQL();      // 🔄 Recharger clients
    genererStatistiquesCRUD();      // 🔄 Mettre à jour graphique
}

// ----------------------------------------------------------------
// Génération graphique
// ----------------------------------------------------------------
void MainWindow::genererStatistiquesCRUD()
{
    // Charger clients depuis SQL pour être sûr d'avoir les données à jour
    chargerClientsDepuisSQL();

    qDebug() << "🔍 Génération des statistiques par âge";

    // Calcul des stats
    QMap<QString, int> stats = calculerStatsParAge();

    // -----------------------------
    // 1️⃣ Mise à jour du texte
    // -----------------------------
    QString statsText = "📊 STATISTIQUES CLIENTS PAR ÂGE\n";
    statsText += "==============================\n\n";

    int totalClients = clients.size();
    if (totalClients == 0) {
        statsText += "Aucun client enregistré.\n";
    } else {
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            double pourcentage = (it.value() * 100.0) / totalClients;
            statsText += QString("• %1: %2 clients (%3%)\n")
                             .arg(it.key())
                             .arg(it.value())
                             .arg(QString::number(pourcentage, 'f', 1));
        }
        statsText += QString("\n• TOTAL: %1 clients\n").arg(totalClients);
    }

    ui->textEdit_stat->setPlainText(statsText);
    qDebug() << "✅ Texte des statistiques mis à jour";

    // -----------------------------
    // 2️⃣ Création du graphique
    // -----------------------------
    QPieSeries *series = new QPieSeries();
    for(auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques par âge");
    chart->legend()->setVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Supprimer ancien layout / widget
    if(ui->graphicsView_2->layout()) {
        QLayoutItem *item;
        while((item = ui->graphicsView_2->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->graphicsView_2->layout();
    }

    // Ajouter le nouveau chart
    QVBoxLayout *layout = new QVBoxLayout(ui->graphicsView_2);
    layout->addWidget(chartView);
    ui->graphicsView_2->setLayout(layout);

    qDebug() << "✅ Graphique affiché dans graphicsView_2";
}


// ----------------------------------------------------------------
// Calcul stats par âge
// ----------------------------------------------------------------
QMap<QString, int> MainWindow::calculerStatsParAge()
{
    QMap<QString, int> stats;
    stats["10-17 ans"] = 0;     // Jeunes
    stats["18-25 ans"] = 0;     // Jeunes adultes
    stats["26-35 ans"] = 0;     // Adultes

    for (const Client &client : clients)
    {
        int age = QDate::currentDate().year() - client.getDateNaissance().year();

        // Corriger si l'anniversaire n'est pas encore passé cette année
        if (QDate::currentDate() < QDate(QDate::currentDate().year(),
                                         client.getDateNaissance().month(),
                                         client.getDateNaissance().day()))
        {
            age--;
        }

        if (age >= 10 && age <= 17)
            stats["10-17 ans"]++;
        else if (age >= 18 && age <= 25)
            stats["18-25 ans"]++;
        else if (age >= 26 && age <= 35)
            stats["26-35 ans"]++;
        // les clients en dehors de 10-35 ans ne sont pas comptés
    }

    qDebug() << "📊 Stats par âge (10-35 ans) calculées:" << stats;
    return stats;
}


// ----------------------------------------------------------------
// Calcul stats opérations
// ----------------------------------------------------------------
QMap<QString,int> MainWindow::calculerStatsOperations()
{
    QMap<QString,int> stats;
    stats["Clients enregistrés"] = clients.size();
    int emailsValides = 0;
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    for(const Client &client : clients)
        if(emailRegex.match(client.getEmail()).hasMatch()) emailsValides++;
    stats["Emails valides"] = emailsValides;
    stats["Téléphones valides"] = clients.size();

    QMap<QString,int> statsAge = calculerStatsParAge();
    for(auto it=statsAge.begin(); it!=statsAge.end(); ++it)
        stats[it.key()] = it.value();

    return stats;
}

// ----------------------------------------------------------------
// Charger clients depuis SQL
// ----------------------------------------------------------------
void MainWindow::chargerClientsDepuisSQL()
{
    clients.clear();
    QSqlQuery q("SELECT ID_CLIENTS,NOM,PRENOM,MAIL,NUM,DATE_NAISSANCE FROM CLIENTS");
    while(q.next()) {
        Client c(q.value(0).toInt(),
                 q.value(1).toString(),
                 q.value(2).toString(),
                 q.value(3).toString(),
                 q.value(4).toString(),
                 q.value(5).toDate());
        clients.append(c);
    }
    qDebug() << "📥 Clients chargés:" << clients.size();
}

