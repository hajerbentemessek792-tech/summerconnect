#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(nullptr)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->tabajouter);

    setupDatabase();

    populateComboBoxes();

    model = new QSqlTableModel(this);
    model->setTable("EVENEMENTS");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    // === CONFIGURATION CALENDRIER ===
    // Connexions des signaux
    connect(ui->calendarWidget, &QCalendarWidget::clicked,
            this, &MainWindow::on_calendarWidget_clicked);
    connect(ui->listEventsToday, &QListWidget::itemClicked,
            this, &MainWindow::on_listEventsToday_itemClicked);

    // Configuration initiale
    ui->planDate->setDate(QDate::currentDate());
    ui->eventDetailsDate->setDate(QDate::currentDate());

    // Peupler les combobox du calendrier
    ui->planLieu->clear();
    ui->planLieu->addItem("Salle des fêtes");
    ui->planLieu->addItem("Jardin");
    ui->planLieu->addItem("Plage");
    ui->planLieu->addItem("Restaurant");
    ui->planLieu->addItem("Hôtel");
    ui->planLieu->addItem("Salle de conférence");

    ui->planType->clear();
    ui->planType->addItem("Romantique");
    ui->planType->addItem("Élégant");
    ui->planType->addItem("Festif");
    ui->planType->addItem("Soft/Doux");
    ui->planType->addItem("Formel");
    ui->planType->addItem("Informel");

    // Mêmes valeurs pour les détails
    ui->eventDetailsLieu->clear();
    ui->eventDetailsLieu->addItem("Salle des fêtes");
    ui->eventDetailsLieu->addItem("Jardin");
    ui->eventDetailsLieu->addItem("Plage");
    ui->eventDetailsLieu->addItem("Restaurant");
    ui->eventDetailsLieu->addItem("Hôtel");
    ui->eventDetailsLieu->addItem("Salle de conférence");

    ui->eventDetailsType->clear();
    ui->eventDetailsType->addItem("Romantique");
    ui->eventDetailsType->addItem("Élégant");
    ui->eventDetailsType->addItem("Festif");
    ui->eventDetailsType->addItem("Soft/Doux");
    ui->eventDetailsType->addItem("Formel");
    ui->eventDetailsType->addItem("Informel");

    // Charger les événements actuels
    populateCalendarEvents();

    qDebug() << "Application initialisée - Onglet Ajouter affiché par défaut";
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("sarra");
    db.setPassword("sarrasarra");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur",
                              "Impossible de se connecter à la base de données: " + db.lastError().text());
        return;
    }

    qDebug() << "Connexion à la base de données réussie";
}

void MainWindow::populateComboBoxes()
{
    // Onglet Ajouter - Type
    ui->comboBoxtype->clear();
    ui->comboBoxtype->addItem("Romantique");
    ui->comboBoxtype->addItem("Élégant");
    ui->comboBoxtype->addItem("Festif");
    ui->comboBoxtype->addItem("Soft/Doux");
    ui->comboBoxtype->addItem("Formel");
    ui->comboBoxtype->addItem("Informel");

    // Onglet Ajouter - Lieu
    ui->comboBoxlieu->clear();
    ui->comboBoxlieu->addItem("Salle des fêtes");
    ui->comboBoxlieu->addItem("Jardin");
    ui->comboBoxlieu->addItem("Plage");
    ui->comboBoxlieu->addItem("Restaurant");
    ui->comboBoxlieu->addItem("Hôtel");
    ui->comboBoxlieu->addItem("Salle de conférence");

    // Onglet Modifier - Type
    ui->comboBox_6->clear();
    ui->comboBox_6->addItem("Romantique");
    ui->comboBox_6->addItem("Élégant");
    ui->comboBox_6->addItem("Festif");
    ui->comboBox_6->addItem("Soft/Doux");
    ui->comboBox_6->addItem("Formel");
    ui->comboBox_6->addItem("Informel");

    // Onglet Modifier - Lieu
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem("Salle des fêtes");
    ui->comboBox_7->addItem("Jardin");
    ui->comboBox_7->addItem("Plage");
    ui->comboBox_7->addItem("Restaurant");
    ui->comboBox_7->addItem("Hôtel");
    ui->comboBox_7->addItem("Salle de conférence");
}

// ==================== ONGLET AJOUTER ====================

void MainWindow::on_pushButtonvalider_clicked()
{
    // Validation des champs obligatoires
    if (ui->lineEditnom->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir le nom de l'événement");
        ui->lineEditnom->setFocus();
        return;
    }

    if (ui->lineEditid->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir l'ID de l'événement");
        ui->lineEditid->setFocus();
        return;
    }

    // Vérifier que l'ID est un nombre
    bool ok;
    int id = ui->lineEditid->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "ID invalide", "L'ID doit être un nombre entier");
        ui->lineEditid->setFocus();
        ui->lineEditid->selectAll();
        return;
    }

    // Vérifier si l'ID existe déjà
    if (eventExists(id)) {
        QMessageBox::warning(this, "ID existant",
                             "Un événement avec cet ID existe déjà. Veuillez utiliser un ID différent.");
        ui->lineEditid->setFocus();
        ui->lineEditid->selectAll();
        return;
    }

    // Validation du budget
    if (ui->spinBoxbudget->value() <= 0) {
        QMessageBox::warning(this, "Budget invalide", "Le budget doit être supérieur à 0");
        ui->spinBoxbudget->setFocus();
        return;
    }

    // Validation du nombre de participants
    if (ui->spinBoxnbrpartic->value() <= 0) {
        QMessageBox::warning(this, "Participants invalides",
                             "Le nombre de participants doit être supérieur à 0");
        ui->spinBoxnbrpartic->setFocus();
        return;
    }

    // Insertion dans la base de données
    QSqlQuery query;
    query.prepare("INSERT INTO EVENEMENTS (ID_EVENEMENTS, NOM, DATE_EVENEMENT, LIEU, TYPE, NB_PARTICIPANTS, BUDGET) "
                  "VALUES (:id, :nom, TO_DATE(:date_evenement, 'YYYY-MM-DD'), :lieu, :type, :nb_participants, :budget)");

    query.bindValue(":id", id);
    query.bindValue(":nom", ui->lineEditnom->text());
    query.bindValue(":date_evenement", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":lieu", ui->comboBoxlieu->currentText());
    query.bindValue(":type", ui->comboBoxtype->currentText());
    query.bindValue(":nb_participants", ui->spinBoxnbrpartic->value());
    query.bindValue(":budget", ui->spinBoxbudget->value());

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Événement ajouté avec succès!");
        clearAjouterFields();
        model->select(); // Rafraîchir la table d'affichage
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout: " + query.lastError().text());
    }
}

void MainWindow::on_pushButtonannuler_clicked()
{
    clearAjouterFields();
    QMessageBox::information(this, "Annulé", "Opération annulée. Tous les champs ont été vidés.");
}

void MainWindow::clearAjouterFields()
{
    ui->lineEditnom->clear();
    ui->lineEditid->clear();
    ui->comboBoxtype->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBoxlieu->setCurrentIndex(0);
    ui->spinBoxnbrpartic->setValue(0);
    ui->spinBoxbudget->setValue(0);
    ui->lineEditnom->setFocus();
}

// ==================== ONGLET AFFICHER ====================

void MainWindow::on_pushButtonafficher_clicked()
{
    QString searchText = ui->lineEditchercherid->text().trimmed();

    // Si le champ de recherche est vide, afficher tous les événements
    if (searchText.isEmpty()) {
        model->setFilter("");
        model->select();
        ui->tableView->resizeColumnsToContents();
        QMessageBox::information(this, "Affichage", "Tous les événements sont affichés");
        return;
    }

    // Vérifier que le texte contient seulement des chiffres
    bool isNumeric = true;
    for (int i = 0; i < searchText.length(); ++i) {
        if (!searchText[i].isDigit()) {
            isNumeric = false;
            break;
        }
    }

    if (!isNumeric) {
        QMessageBox::warning(this, "Recherche invalide",
                             "Veuillez saisir uniquement des chiffres pour la recherche par ID");
        ui->lineEditchercherid->setFocus();
        ui->lineEditchercherid->selectAll();
        return;
    }

    // Recherche par préfixe d'ID (commence par) - Syntaxe Oracle
    QString filter = QString("TO_CHAR(ID_EVENEMENTS) LIKE '%1%'").arg(searchText + "%");
    model->setFilter(filter);

    if (model->select()) {
        ui->tableView->resizeColumnsToContents();
        int rowCount = model->rowCount();

        if (rowCount > 0) {
            QMessageBox::information(this, "Recherche réussie",
                                     QString("%1 événement(s) trouvé(s) commençant par '%2'")
                                         .arg(rowCount)
                                         .arg(searchText));
        } else {
            QMessageBox::information(this, "Aucun résultat",
                                     QString("Aucun événement trouvé commençant par '%1'")
                                         .arg(searchText));
            // Réafficher tous les événements si aucun résultat
            model->setFilter("");
            model->select();
            ui->tableView->resizeColumnsToContents();
        }
    } else {
        QMessageBox::critical(this, "Erreur de recherche",
                              "Erreur lors de la recherche: " + model->lastError().text());
    }
}

void MainWindow::on_lineEditchercherid_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    // Recherche en temps réel si le texte n'est pas vide
    QString searchText = ui->lineEditchercherid->text().trimmed();

    if (!searchText.isEmpty()) {
        // Vérifier que le texte contient seulement des chiffres
        bool isNumeric = true;
        for (int i = 0; i < searchText.length(); ++i) {
            if (!searchText[i].isDigit()) {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric) {
            // Recherche par préfixe d'ID en temps réel - Syntaxe Oracle
            QString filter = QString("TO_CHAR(ID_EVENEMENTS) LIKE '%1%'").arg(searchText + "%");
            model->setFilter(filter);
            model->select();
            ui->tableView->resizeColumnsToContents();
        }
    } else {
        // Si le champ est vide, réafficher tous les événements
        model->setFilter("");
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}
// ==================== TRI DES ÉVÉNEMENTS ====================

void MainWindow::on_pushButtontri_clicked()
{
    static int currentSortColumn = 0; // 0=ID, 1=Nom, 4=Type
    static bool ascending = true;

    QString columnName;
    QString buttonText;

    switch (currentSortColumn) {
    case 0:
        columnName = "ID";
        model->setSort(0, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        buttonText = ascending ? "Tri ID ▲" : "Tri ID ▼";
        break;
    case 1:
        columnName = "Nom";
        model->setSort(1, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        buttonText = ascending ? "Tri Nom ▲" : "Tri Nom ▼";
        break;
    case 4:
        columnName = "Type";
        model->setSort(4, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        buttonText = ascending ? "Tri Type ▲" : "Tri Type ▼";
        break;
    }

    model->select();
    ui->tableView->resizeColumnsToContents();

    // Mettre à jour le texte du bouton
    ui->pushButtontri->setText(buttonText);

    QString sortOrder = ascending ? "croissant" : "décroissant";

    // Message court ou optionnel - vous pouvez le supprimer si vous voulez
    QMessageBox::information(this, "Tri effectué",
                             QString("Tri par %1 (%2)").arg(columnName).arg(sortOrder));

    // Passer à la colonne suivante pour le prochain clic
    currentSortColumn = (currentSortColumn + 1) % 3;

    // Réinitialiser l'ordre pour la nouvelle colonne
    ascending = true;
}
// ==================== ONGLET MODIFIER ====================

void MainWindow::on_pushButton_13_clicked()
{
    // Chercher l'événement à modifier
    if (ui->lineEdit_9->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir l'ID de l'événement à modifier");
        ui->lineEdit_9->setFocus();
        return;
    }

    bool ok;
    int id = ui->lineEdit_9->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "ID invalide", "Veuillez saisir un ID valide (nombre entier)");
        ui->lineEdit_9->setFocus();
        ui->lineEdit_9->selectAll();
        return;
    }

    // Afficher les détails de l'événement
    showEventDetails(id);
}

void MainWindow::on_pushButton_14_clicked()
{
    // Sauvegarder les modifications
    if (ui->lineEdit_8->text().isEmpty()) {
        QMessageBox::warning(this, "Aucun événement", "Veuillez d'abord chercher un événement à modifier");
        return;
    }

    // Validation des champs
    if (ui->lineEdit_7->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Le nom de l'événement ne peut pas être vide");
        ui->lineEdit_7->setFocus();
        return;
    }

    if (ui->spinBox_6->value() <= 0) {
        QMessageBox::warning(this, "Participants invalides",
                             "Le nombre de participants doit être supérieur à 0");
        ui->spinBox_6->setFocus();
        return;
    }

    if (ui->spinBox_5->value() <= 0) {
        QMessageBox::warning(this, "Budget invalide", "Le budget doit être supérieur à 0");
        ui->spinBox_5->setFocus();
        return;
    }

    bool ok;
    int id = ui->lineEdit_8->text().toInt(&ok);

    if (!ok) {
        QMessageBox::critical(this, "Erreur", "ID invalide");
        return;
    }

    // Confirmation de modification
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir modifier cet événement?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    // Mise à jour dans la base de données
    QSqlQuery query;
    query.prepare("UPDATE EVENEMENTS SET "
                  "NOM = :nom, "
                  "DATE_EVENEMENT = TO_DATE(:date_evenement, 'YYYY-MM-DD'), "
                  "LIEU = :lieu, "
                  "TYPE = :type, "
                  "NB_PARTICIPANTS = :nb_participants, "
                  "BUDGET = :budget "
                  "WHERE ID_EVENEMENTS = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", ui->lineEdit_7->text());
    query.bindValue(":date_evenement", ui->dateEdit_4->date().toString("yyyy-MM-dd"));
    query.bindValue(":lieu", ui->comboBox_7->currentText());
    query.bindValue(":type", ui->comboBox_6->currentText());
    query.bindValue(":nb_participants", ui->spinBox_6->value());
    query.bindValue(":budget", ui->spinBox_5->value());

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Succès", "Événement modifié avec succès!");
            clearModifierFields();
            model->select(); // Rafraîchir la table d'affichage
        } else {
            QMessageBox::warning(this, "Aucune modification",
                                 "Aucune modification effectuée. L'événement n'existe peut-être plus.");
        }
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la modification: " + query.lastError().text());
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    clearModifierFields();
    QMessageBox::information(this, "Annulé", "Modification annulée.");
}

void MainWindow::clearModifierFields()
{
    ui->lineEdit_9->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->comboBox_6->setCurrentIndex(0);
    ui->dateEdit_4->setDate(QDate::currentDate());
    ui->comboBox_7->setCurrentIndex(0);
    ui->spinBox_6->setValue(0);
    ui->spinBox_5->setValue(0);
    ui->lineEdit_9->setFocus();
}

// ==================== ONGLET SUPPRIMER ====================

void MainWindow::on_pushButtonsupprimer_clicked()
{
    if (ui->lineEditchercherid_2->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir l'ID de l'événement à supprimer");
        ui->lineEditchercherid_2->setFocus();
        return;
    }

    bool ok;
    int id = ui->lineEditchercherid_2->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "ID invalide", "Veuillez saisir un ID valide (nombre entier)");
        ui->lineEditchercherid_2->setFocus();
        ui->lineEditchercherid_2->selectAll();
        return;
    }

    // Vérifier si l'événement existe
    if (!eventExists(id)) {
        QMessageBox::warning(this, "Événement introuvable",
                             "Aucun événement trouvé avec cet ID");
        return;
    }

    // Récupérer les informations de l'événement pour la confirmation
    QSqlQuery infoQuery;
    infoQuery.prepare("SELECT NOM, DATE_EVENEMENT, LIEU FROM EVENEMENTS WHERE ID_EVENEMENTS = :id");
    infoQuery.bindValue(":id", id);

    QString nom, date, lieu;
    if (infoQuery.exec() && infoQuery.next()) {
        nom = infoQuery.value(0).toString();
        date = infoQuery.value(1).toDate().toString("dd/MM/yyyy");
        lieu = infoQuery.value(2).toString();
    }

    // Confirmation de suppression
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de suppression",
                                  QString("Êtes-vous sûr de vouloir supprimer cet événement ?\n\n"
                                          "ID: %1\n"
                                          "Nom: %2\n"
                                          "Date: %3\n"
                                          "Lieu: %4\n\n"
                                          "Cette action est irréversible !")
                                      .arg(id)
                                      .arg(nom)
                                      .arg(date)
                                      .arg(lieu),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if (reply != QMessageBox::Yes) {
        return;
    }

    // Suppression dans la base de données
    QSqlQuery query;
    query.prepare("DELETE FROM EVENEMENTS WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Succès",
                                     QString("Événement supprimé avec succès!\n\n"
                                             "ID: %1\n"
                                             "Nom: %2")
                                         .arg(id)
                                         .arg(nom));
            ui->lineEditchercherid_2->clear();
            model->select(); // Rafraîchir la table d'affichage
        } else {
            QMessageBox::warning(this, "Aucune suppression",
                                 "Aucun événement trouvé avec cet ID.");
        }
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de la suppression: " + query.lastError().text());
    }
}

void MainWindow::on_pushButtoannuler_clicked()
{
    ui->lineEditchercherid_2->clear();
    QMessageBox::information(this, "Annulé", "Suppression annulée.");
}

// ==================== MÉTHODES UTILITAIRES ====================

bool MainWindow::eventExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

void MainWindow::showEventDetails(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EVENEMENTS WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Remplir les champs avec les données de l'événement
        ui->lineEdit_7->setText(query.value("NOM").toString());
        ui->lineEdit_8->setText(query.value("ID_EVENEMENTS").toString());

        // Type
        QString type = query.value("TYPE").toString();
        int typeIndex = ui->comboBox_6->findText(type);
        if (typeIndex >= 0) {
            ui->comboBox_6->setCurrentIndex(typeIndex);
        }

        // Date
        QDate date = query.value("DATE_EVENEMENT").toDate();
        ui->dateEdit_4->setDate(date);

        // Lieu
        QString lieu = query.value("LIEU").toString();
        int lieuIndex = ui->comboBox_7->findText(lieu);
        if (lieuIndex >= 0) {
            ui->comboBox_7->setCurrentIndex(lieuIndex);
        }

        // Nombre de participants et budget
        ui->spinBox_6->setValue(query.value("NB_PARTICIPANTS").toInt());
        ui->spinBox_5->setValue(query.value("BUDGET").toDouble());

        QMessageBox::information(this, "Événement trouvé",
                                 "Les informations de l'événement ont été chargées. Vous pouvez maintenant les modifier.");
    } else {
        QMessageBox::warning(this, "Événement introuvable",
                             "Aucun événement trouvé avec cet ID");
        clearModifierFields();
    }
}
void MainWindow::on_pushButtonpdf_clicked()
{
    qDebug() << "PDF CLICKED";

    // Choisir où enregistrer le PDF
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer le PDF",
        "Evenements.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    // Création du PDF
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageMargins(QMargins(30, 30, 30, 30));
    pdf.setResolution(150); // Augmenter la résolution pour une meilleure qualité

    QPainter painter(&pdf);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Définir les polices
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);

    // Titre
    painter.setFont(titleFont);
    painter.drawText(pdf.width()/2 - 200, 50, "LISTE DES ÉVÉNEMENTS");

    // Date de génération
    painter.setFont(dataFont);
    painter.drawText(pdf.width() - 300, 80,
                     "Généré le: " + QDate::currentDate().toString("dd/MM/yyyy"));

    int y = 120;
    int lineHeight = 25;
    int columnSpacing = 120;

    // ---- EN-TÊTE DU TABLEAU ----
    painter.setFont(headerFont);

    // Dessiner le fond de l'en-tête
    painter.setBrush(QBrush(QColor(200, 200, 200)));
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(30, y, pdf.width() - 60, lineHeight);

    // Texte de l'en-tête
    painter.setPen(QPen(Qt::black));
    painter.drawText(40, y + 18, "ID");
    painter.drawText(40 + columnSpacing, y + 18, "Nom");
    painter.drawText(40 + columnSpacing * 2, y + 18, "Date");
    painter.drawText(40 + columnSpacing * 3, y + 18, "Lieu");
    painter.drawText(40 + columnSpacing * 4, y + 18, "Type");
    painter.drawText(40 + columnSpacing * 5, y + 18, "Participants");
    painter.drawText(40 + columnSpacing * 6, y + 18, "Budget");

    y += lineHeight;

    // ---- DONNÉES DES ÉVÉNEMENTS ----
    painter.setFont(dataFont);

    for (int i = 0; i < model->rowCount(); ++i) {
        // Alterner les couleurs de fond pour une meilleure lisibilité
        if (i % 2 == 0) {
            painter.setBrush(QBrush(QColor(240, 240, 240)));
        } else {
            painter.setBrush(QBrush(Qt::white));
        }

        painter.setPen(QPen(Qt::black, 1));
        painter.drawRect(30, y, pdf.width() - 60, lineHeight);

        // Dessiner les données
        painter.setPen(QPen(Qt::black));
        painter.drawText(40, y + 18, model->index(i, 0).data().toString());
        painter.drawText(40 + columnSpacing, y + 18,
                         model->index(i, 1).data().toString().left(20)); // Limiter la longueur du nom

        // Formater la date
        QDate date = model->index(i, 2).data().toDate();
        painter.drawText(40 + columnSpacing * 2, y + 18,
                         date.isValid() ? date.toString("dd/MM/yyyy") : "N/A");

        painter.drawText(40 + columnSpacing * 3, y + 18,
                         model->index(i, 3).data().toString().left(15)); // Limiter la longueur du lieu

        painter.drawText(40 + columnSpacing * 4, y + 18,
                         model->index(i, 4).data().toString());

        painter.drawText(40 + columnSpacing * 5, y + 18,
                         model->index(i, 5).data().toString());

        // Formater le budget
        double budget = model->index(i, 6).data().toDouble();
        painter.drawText(40 + columnSpacing * 6, y + 18,
                         QString::number(budget, 'f', 2) + " M");

        y += lineHeight;

        // Vérifier si on dépasse la page
        if (y > pdf.height() - 50) {
            pdf.newPage();
            y = 50;

            // Redessiner l'en-tête sur la nouvelle page
            painter.setFont(headerFont);
            painter.setBrush(QBrush(QColor(200, 200, 200)));
            painter.setPen(QPen(Qt::black, 1));
            painter.drawRect(30, y, pdf.width() - 60, lineHeight);

            painter.setPen(QPen(Qt::black));
            painter.drawText(40, y + 18, "ID");
            painter.drawText(40 + columnSpacing, y + 18, "Nom");
            painter.drawText(40 + columnSpacing * 2, y + 18, "Date");
            painter.drawText(40 + columnSpacing * 3, y + 18, "Lieu");
            painter.drawText(40 + columnSpacing * 4, y + 18, "Type");
            painter.drawText(40 + columnSpacing * 5, y + 18, "Participants");
            painter.drawText(40 + columnSpacing * 6, y + 18, "Budget");

            y += lineHeight;
            painter.setFont(dataFont);
        }
    }

    // Pied de page
    painter.setFont(dataFont);
    painter.drawText(30, pdf.height() - 20,
                     QString("Total: %1 événement(s)").arg(model->rowCount()));

    painter.end();

    QMessageBox::information(this, "PDF généré",
                             "Le PDF a été créé avec succès !\nFichier: " + fileName);
}

// ==================== FONCTIONS CALENDRIER ====================

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    loadEventsForDate(date);

    // Mettre à jour le statut dans la barre de status
    statusBar()->showMessage(QString("Événements du %1 - Cliquez sur un événement pour voir les détails")
                                 .arg(date.toString("dd/MM/yyyy")));

    // Mettre à jour la date dans le formulaire de planification
    ui->planDate->setDate(date);
}

void MainWindow::loadEventsForDate(const QDate &date)
{
    ui->listEventsToday->clear();

    QSqlQuery query;
    query.prepare("SELECT ID_EVENEMENTS, NOM, TYPE, LIEU FROM EVENEMENTS WHERE DATE_EVENEMENT = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString nom = query.value(1).toString();
            QString type = query.value(2).toString();
            QString lieu = query.value(3).toString();

            QString itemText = QString("%1 - %2 (%3)").arg(nom).arg(lieu).arg(type);
            QListWidgetItem *item = new QListWidgetItem(itemText, ui->listEventsToday);
            item->setData(Qt::UserRole, id); // Stocker l'ID dans l'item
        }
    }

    if (ui->listEventsToday->count() == 0) {
        ui->listEventsToday->addItem("Aucun événement cette date");
    }
}

void MainWindow::on_listEventsToday_itemClicked(QListWidgetItem *item)
{
    if (!item || item->text() == "Aucun événement cette date") {
        return;
    }

    int eventId = item->data(Qt::UserRole).toInt();

    QSqlQuery query;
    query.prepare("SELECT * FROM EVENEMENTS WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", eventId);

    if (query.exec() && query.next()) {
        ui->eventDetailsNom->setText(query.value("NOM").toString());
        ui->eventDetailsDate->setDate(query.value("DATE_EVENEMENT").toDate());

        // Type
        QString type = query.value("TYPE").toString();
        int typeIndex = ui->eventDetailsType->findText(type);
        if (typeIndex >= 0) ui->eventDetailsType->setCurrentIndex(typeIndex);

        // Lieu
        QString lieu = query.value("LIEU").toString();
        int lieuIndex = ui->eventDetailsLieu->findText(lieu);
        if (lieuIndex >= 0) ui->eventDetailsLieu->setCurrentIndex(lieuIndex);
    }
}

void MainWindow::on_pushButtonPlanifier_clicked()
{
    // Validation des champs
    if (ui->planNom->text().isEmpty()) {
        QMessageBox::warning(this, "Champ manquant", "Veuillez saisir le nom de l'événement");
        ui->planNom->setFocus();
        return;
    }

    // Vérifier les conflits
    if (checkEventConflict(ui->planDate->date(), ui->planLieu->currentText())) {
        QMessageBox::warning(this, "Conflit détecté",
                             QString("Le lieu '%1' est déjà réservé pour cette date. Choisissez un autre lieu ou une autre date.")
                                 .arg(ui->planLieu->currentText()));
        return;
    }

    // Générer un ID unique
    int newId = QRandomGenerator::global()->bounded(1000, 9999);
    while (eventExists(newId)) {
        newId = QRandomGenerator::global()->bounded(1000, 9999);
    }

    // Insérer dans la base
    QSqlQuery query;
    query.prepare("INSERT INTO EVENEMENTS (ID_EVENEMENTS, NOM, DATE_EVENEMENT, LIEU, TYPE, NB_PARTICIPANTS, BUDGET) "
                  "VALUES (:id, :nom, TO_DATE(:date_evenement, 'YYYY-MM-DD'), :lieu, :type, :nb_participants, :budget)");

    query.bindValue(":id", newId);
    query.bindValue(":nom", ui->planNom->text());
    query.bindValue(":date_evenement", ui->planDate->date().toString("yyyy-MM-dd"));
    query.bindValue(":lieu", ui->planLieu->currentText());
    query.bindValue(":type", ui->planType->currentText());
    query.bindValue(":nb_participants", 0); // Valeur par défaut
    query.bindValue(":budget", 0); // Valeur par défaut

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Événement planifié avec succès!");

        // Recharger les données
        loadEventsForDate(ui->planDate->date());
        populateCalendarEvents();
        model->select();

        // Vider le formulaire
        ui->planNom->clear();
        ui->planNom->setFocus();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la planification: " + query.lastError().text());
    }
}

void MainWindow::on_pushButtonEditEvent_clicked()
{
    if (ui->eventDetailsNom->text().isEmpty()) {
        QMessageBox::warning(this, "Aucun événement", "Veuillez d'abord sélectionner un événement");
        return;
    }

    // Récupérer l'ID de l'événement sélectionné
    QListWidgetItem *currentItem = ui->listEventsToday->currentItem();
    if (!currentItem || currentItem->text() == "Aucun événement cette date") {
        return;
    }

    int eventId = currentItem->data(Qt::UserRole).toInt();

    // Mise à jour dans la base
    QSqlQuery query;
    query.prepare("UPDATE EVENEMENTS SET NOM = :nom, DATE_EVENEMENT = TO_DATE(:date, 'YYYY-MM-DD'), LIEU = :lieu, TYPE = :type WHERE ID_EVENEMENTS = :id");

    query.bindValue(":id", eventId);
    query.bindValue(":nom", ui->eventDetailsNom->text());
    query.bindValue(":date", ui->eventDetailsDate->date().toString("yyyy-MM-dd"));
    query.bindValue(":lieu", ui->eventDetailsLieu->currentText());
    query.bindValue(":type", ui->eventDetailsType->currentText());

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Événement modifié avec succès!");

        // Recharger les données
        loadEventsForDate(ui->eventDetailsDate->date());
        populateCalendarEvents();
        model->select();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification: " + query.lastError().text());
    }
}

bool MainWindow::checkEventConflict(const QDate &date, const QString &lieu)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE DATE_EVENEMENT = TO_DATE(:date, 'YYYY-MM-DD') AND LIEU = :lieu");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":lieu", lieu);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

void MainWindow::populateCalendarEvents()
{
    // Cette fonction peut être étendue pour colorer les dates avec événements
    QSqlQuery query;
    query.prepare("SELECT DISTINCT DATE_EVENEMENT FROM EVENEMENTS");

    if (query.exec()) {
        while (query.next()) {
            QDate eventDate = query.value(0).toDate();
            // Ici vous pouvez ajouter un formatage spécial pour les dates avec événements
            qDebug() << "Événement trouvé le:" << eventDate.toString("dd/MM/yyyy");
        }
    }
}

