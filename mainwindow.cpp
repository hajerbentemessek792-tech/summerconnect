#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(nullptr)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->tabajouter);

    setupDatabase();

    populateComboBoxes();
    setupStatistiquesUI();

    model = new QSqlTableModel(this);
    model->setTable("EVENEMENTS");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

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
        updateStatistiques();
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
    // Si le champ de recherche est vide, afficher tous les événements
    if (ui->lineEditchercherid->text().isEmpty()) {
        model->setFilter("");
        model->select();
        QMessageBox::information(this, "Affichage", "Tous les événements sont affichés");
        return;
    }

    // Recherche par ID
    bool ok;
    int id = ui->lineEditchercherid->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "ID invalide", "Veuillez saisir un ID valide (nombre entier)");
        ui->lineEditchercherid->setFocus();
        ui->lineEditchercherid->selectAll();
        return;
    }

    // Appliquer le filtre
    model->setFilter(QString("ID_EVENEMENTS = %1").arg(id));

    if (!model->select()) {
        QMessageBox::warning(this, "Recherche", "Aucun événement trouvé avec cet ID");
        model->setFilter(""); // Réafficher tous les événements
        model->select();
    } else {
        QMessageBox::information(this, "Recherche",
                                 QString("%1 événement(s) trouvé(s)").arg(model->rowCount()));
    }
}

void MainWindow::on_lineEditchercherid_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    // Si le champ de recherche est vidé, réafficher tous les événements
    if (ui->lineEditchercherid->text().isEmpty()) {
        model->setFilter("");
        model->select();
    }
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
            updateStatistiques();
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
            updateStatistiques();
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

// Ajoutez cette méthode
void MainWindow::setupStatistiquesUI()
{
    // Initialiser le tableau des types
    ui->tableWidget_types->setColumnCount(2);
    ui->tableWidget_types->setRowCount(4);

    QStringList headers;
    headers << "Type" << "Nombre";
    ui->tableWidget_types->setHorizontalHeaderLabels(headers);

    // Types d'événements
    QStringList types;
    types << "Romantique" << "Élégant" << "Festif" << "Soft/Doux";

    for (int i = 0; i < types.size(); ++i) {
        QTableWidgetItem *typeItem = new QTableWidgetItem(types[i]);
        QTableWidgetItem *countItem = new QTableWidgetItem("0");

        ui->tableWidget_types->setItem(i, 0, typeItem);
        ui->tableWidget_types->setItem(i, 1, countItem);
    }

    ui->tableWidget_types->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_types->resizeColumnsToContents();
}

// Méthode pour calculer les statistiques
void MainWindow::calculerStatistiques()
{
    QSqlQuery query;

    // Total des événements
    int total = 0;
    if (query.exec("SELECT COUNT(*) FROM EVENEMENTS")) {
        if (query.next()) {
            total = query.value(0).toInt();
        }
    }

    // Événements ce mois
    int ceMois = 0;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE EXTRACT(MONTH FROM DATE_EVENEMENT) = EXTRACT(MONTH FROM SYSDATE) AND EXTRACT(YEAR FROM DATE_EVENEMENT) = EXTRACT(YEAR FROM SYSDATE)");
    if (query.exec() && query.next()) {
        ceMois = query.value(0).toInt();
    }

    // Événements cette année
    int cetteAnnee = 0;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE EXTRACT(YEAR FROM DATE_EVENEMENT) = EXTRACT(YEAR FROM SYSDATE)");
    if (query.exec() && query.next()) {
        cetteAnnee = query.value(0).toInt();
    }

    // Mettre à jour les labels
    ui->label_total->setText(QString("Total événements: %1").arg(total));
    ui->label_mois->setText(QString("- Ce mois: %1").arg(ceMois));
    ui->label_annee->setText(QString("- Cette année: %1").arg(cetteAnnee));

    // Statistiques par type
    QStringList types = {"Romantique", "Élégant", "Festif", "Soft/Doux"};

    for (int i = 0; i < types.size(); ++i) {
        query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE TYPE = :type");
        query.bindValue(":type", types[i]);

        int count = 0;
        if (query.exec() && query.next()) {
            count = query.value(0).toInt();
        }

        // Mettre à jour le tableau
        QTableWidgetItem *countItem = new QTableWidgetItem(QString::number(count));
        ui->tableWidget_types->setItem(i, 1, countItem);
    }
}

// Slot pour détecter le changement d'onglet
void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);

    // Si l'onglet actif est "Statistique", mettre à jour les stats
    if (ui->tabWidget->currentWidget() == ui->tabstatistique) {
        calculerStatistiques();
    }
}

// Méthode pour mettre à jour manuellement les statistiques
void MainWindow::updateStatistiques()
{
    calculerStatistiques();
}
