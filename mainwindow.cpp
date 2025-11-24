#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QtCharts>
#include <QDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(nullptr)
    , chartView(nullptr)
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




    // === CONFIGURATION CALENDRIER ===
    // Connexions des signaux
    connect(ui->calendarWidget, &QCalendarWidget::clicked,
            this, &MainWindow::on_calendarWidget_clicked);
    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, // AJOUTEZ CETTE LIGNE
            this, &MainWindow::on_calendarWidget_selectionChanged);
    connect(ui->listEventsToday, &QListWidget::itemClicked,
            this, &MainWindow::on_listEventsToday_itemClicked);
    connect(ui->calendarWidget_2, &QCalendarWidget::clicked,
            this, &MainWindow::on_calendarWidget_2_clicked);
    connect(ui->calendarWidget_2, &QCalendarWidget::selectionChanged,
            this, &MainWindow::on_calendarWidget_2_selectionChanged);

    // Configuration initiale
    ui->eventDetailsDate->setDate(QDate::currentDate());

    // Afficher la date initiale
    updateCalendarDisplay(QDate::currentDate());

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
    afficherConseilsSaisonniers(QDate::currentDate());
    calculerStatistiquesPourDate(QDate::currentDate());
    qDebug() << "Application initialisée - Onglet Ajouter affiché par défaut";
}

MainWindow::~MainWindow()
{
    delete chartView;
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

// ==================== ONGLET AFFICHER - RECHERCHE AMÉLIORÉE ====================

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

    // Vérifier que le texte contient seulement des chiffres pour la recherche par ID
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

    QString searchText = ui->lineEditchercherid->text().trimmed();

    if (searchText.isEmpty()) {
        // Si le champ est vide, réafficher tous les événements
        model->setFilter("");
        model->select();
        ui->tableView->resizeColumnsToContents();
        statusBar()->showMessage("Tous les événements sont affichés");
        return;
    }

    // Vérifier que le texte contient seulement des chiffres pour la recherche par ID
    bool isNumeric = true;
    for (int i = 0; i < searchText.length(); ++i) {
        if (!searchText[i].isDigit()) {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        // RECHERCHE PAR ID (commence par) - Syntaxe Oracle
        QString filter = QString("TO_CHAR(ID_EVENEMENTS) LIKE '%1%'").arg(searchText + "%");
        model->setFilter(filter);
    } else {
        // RECHERCHE PAR NOM (contient) - Syntaxe Oracle
        QString filter = QString("UPPER(NOM) LIKE UPPER('%%1%')").arg(searchText);
        model->setFilter(filter);
    }

    model->select();
    ui->tableView->resizeColumnsToContents();

    // Mettre à jour le statut
    if (!searchText.isEmpty()) {
        int resultCount = model->rowCount();
        statusBar()->showMessage(QString("%1 événement(s) trouvé(s) pour \"%2\"")
                                     .arg(resultCount)
                                     .arg(searchText));
    } else {
        statusBar()->showMessage("Tous les événements sont affichés");
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


// ==================== FONCTIONS CALENDRIER ====================

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    loadEventsForDate(date);

    // Mettre à jour le statut dans la barre de status
    statusBar()->showMessage(QString("Événements du %1 - Cliquez sur un événement pour voir les détails")
                                 .arg(date.toString("dd/MM/yyyy")));

    // Mettre à jour la date dans le formulaire de planification
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

    // SUPPRIMEZ cet appel : calculerStatistiques();
    // Les statistiques seront calculées par calculerStatistiquesPourDate()
}

void MainWindow::updatePieChart()
{
    if (!chartView) return;

    QChart *chart = chartView->chart();

    // Supprimer l'ancienne série si elle existe
    QList<QAbstractSeries*> seriesList = chart->series();
    if (!seriesList.isEmpty()) {
        chart->removeSeries(seriesList.first());
    }

    // Créer une nouvelle série avec les données actuelles
    QPieSeries *pieSeries = new QPieSeries();

    // Récupérer les données depuis la base de données
    QSqlQuery query;
    QStringList types = {"Romantique", "Élégant", "Festif", "Soft/Doux", "Formel", "Informel"};

    for (const QString &type : types) {
        query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE TYPE = :type");
        query.bindValue(":type", type);

        int count = 0;
        if (query.exec() && query.next()) {
            count = query.value(0).toInt();
        }

        if (count > 0) {
            QPieSlice *slice = pieSeries->append(type, count);
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1: %2 événements").arg(type).arg(count));

            // Personnaliser les couleurs pour correspondre au thème rose
            static int colorIndex = 0;
            QColor colors[] = {
                QColor("#ffb6c1"), // Rose clair
                QColor("#ff91a4"), // Rose moyen
                QColor("#ff6b8b"), // Rose foncé
                QColor("#ffd1dc"), // Rose pastel
                QColor("#f4c2c2"), // Rose saumon
                QColor("#f8c8dc")  // Rose poudré
            };
            slice->setColor(colors[colorIndex % 6]);
            colorIndex++;
        }
    }

    // Ajouter la nouvelle série au chart
    chart->addSeries(pieSeries);
}

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

    // Statistiques par type pour le tableau
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

    // Mettre à jour le graphique circulaire (sans le recréer)
    updatePieChart();

    qDebug() << "Statistiques mises à jour - Total:" << total;
}

// Slot pour le bouton statButton
void MainWindow::on_statButton_clicked()
{
    // Afficher le graphique circulaire dans une fenêtre modale
    QDialog *chartDialog = new QDialog(this);
    chartDialog->setWindowTitle("Graphique des Événements par Type");
    chartDialog->setMinimumSize(600, 500);
    chartDialog->setStyleSheet("background-color: #fff0f5;");

    QVBoxLayout *layout = new QVBoxLayout(chartDialog);

    // Créer le graphique circulaire
    QPieSeries *pieSeries = new QPieSeries();

    // Récupérer les données depuis la base de données
    QSqlQuery query;
    QStringList types = {"Romantique", "Élégant", "Festif", "Soft/Doux", "Formel", "Informel"};

    for (const QString &type : types) {
        query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE TYPE = :type");
        query.bindValue(":type", type);

        int count = 0;
        if (query.exec() && query.next()) {
            count = query.value(0).toInt();
        }

        if (count > 0) {
            QPieSlice *slice = pieSeries->append(type, count);
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1: %2 événements\n(%3%)")
                                .arg(type)
                                .arg(count)
                                .arg(QString::number(slice->percentage() * 100, 'f', 1)));

            // Personnaliser les couleurs pour correspondre au thème rose
            static int colorIndex = 0;
            QColor colors[] = {
                QColor("#ffb6c1"), // Rose clair
                QColor("#ff91a4"), // Rose moyen
                QColor("#ff6b8b"), // Rose foncé
                QColor("#ffd1dc"), // Rose pastel
                QColor("#f4c2c2"), // Rose saumon
                QColor("#f8c8dc")  // Rose poudré
            };
            slice->setColor(colors[colorIndex % 6]);
            colorIndex++;

            // Effet hover sur les tranches
            connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
                if (hovered) {
                    slice->setExploded(true);
                } else {
                    slice->setExploded(false);
                }
            });
        }
    }

    // Créer le chart
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Répartition des Événements par Type");
    chart->setTitleBrush(QBrush(QColor("#8b475d")));
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor("#8b475d"));
    chart->setBackgroundBrush(QBrush(QColor("#fff0f5")));

    // Créer la vue du chart
    QChartView *dialogChartView = new QChartView(chart);
    dialogChartView->setRenderHint(QPainter::Antialiasing);
    dialogChartView->setStyleSheet("background-color: #fff0f5; border: 2px solid #ffb6c1; border-radius: 10px;");

    // Ajouter un bouton de fermeture
    QPushButton *closeButton = new QPushButton("Fermer", this);
    closeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #f4c2c2;"
        "    color: white;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    border: 2px solid #ff91a4;"
        "}"
        "QPushButton:hover {"
        "    background-color: #ff91a4;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #ff6b8b;"
        "}"
        );

    connect(closeButton, &QPushButton::clicked, chartDialog, &QDialog::accept);

    // Ajouter les widgets au layout
    layout->addWidget(dialogChartView);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    // Afficher la fenêtre modale
    chartDialog->exec();

    // Nettoyer la mémoire
    delete chartDialog;
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
void MainWindow::updateCalendarDisplay(const QDate &date)
{
    // Afficher le mois et l'année dans la barre de status
    QString monthYear = date.toString("MMMM yyyy");
    statusBar()->showMessage(QString("Calendrier: %1 - Événements du %2")
                                 .arg(monthYear)
                                 .arg(date.toString("dd/MM/yyyy")));

    qDebug() << "Date sélectionnée:" << date.toString("dd/MM/yyyy");
    qDebug() << "Mois et année:" << monthYear;

    // Charger les événements pour cette date (SEULEMENT pour le calendrier principal)
    loadEventsForDate(date);

    // NE PAS appeler calculerStatistiquesPourDate ici !
    // Les statistiques sont gérées par calendarWidget_2
}
void MainWindow::on_calendarWidget_selectionChanged()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    updateCalendarDisplay(selectedDate);
}
void MainWindow::calculerStatistiquesPourDate(const QDate &date)
{
    QSqlQuery query;

    // Total des événements (reste le même)
    int total = 0;
    if (query.exec("SELECT COUNT(*) FROM EVENEMENTS")) {
        if (query.next()) {
            total = query.value(0).toInt();
        }
    }

    // Événements du MOIS sélectionné
    int ceMois = 0;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE EXTRACT(MONTH FROM DATE_EVENEMENT) = :month AND EXTRACT(YEAR FROM DATE_EVENEMENT) = :year");
    query.bindValue(":month", date.month());
    query.bindValue(":year", date.year());
    if (query.exec() && query.next()) {
        ceMois = query.value(0).toInt();
    }

    // Événements de l'ANNÉE sélectionnée
    int cetteAnnee = 0;
    query.prepare("SELECT COUNT(*) FROM EVENEMENTS WHERE EXTRACT(YEAR FROM DATE_EVENEMENT) = :year");
    query.bindValue(":year", date.year());
    if (query.exec() && query.next()) {
        cetteAnnee = query.value(0).toInt();
    }

    // Mettre à jour les labels
    ui->label_total->setText(QString("Total événements: %1").arg(total));
    ui->label_mois->setText(QString("- Ce mois: %1").arg(ceMois));
    ui->label_annee->setText(QString("- Cette année: %1").arg(cetteAnnee));

    qDebug() << "Statistiques pour" << date.toString("MMMM yyyy") << "- Mois:" << ceMois << "Année:" << cetteAnnee;
}
// ==================== CALENDRIER STATISTIQUES (calendarWidget_2) ====================

void MainWindow::on_calendarWidget_2_clicked(const QDate &date)
{
    // Mettre à jour les statistiques pour la date sélectionnée
    calculerStatistiquesPourDate(date);

    // Afficher le mois/année dans la barre de status
    QString monthYear = date.toString("MMMM yyyy");
    statusBar()->showMessage(QString("Statistiques pour %1").arg(monthYear));
}

void MainWindow::on_calendarWidget_2_selectionChanged()
{
    QDate selectedDate = ui->calendarWidget_2->selectedDate();
    calculerStatistiquesPourDate(selectedDate);
}
void MainWindow::afficherConseilsSaisonniers(const QDate &date)
{
    int mois = date.month();

    QString saison, message;

    // Détection de la saison selon la date sélectionnée
    if (mois >= 3 && mois <= 5) {
        saison = "🌸 PRINTEMPS";
        message = "• Période : Mars à Mai\n• Lieux : Jardin, Salle des fêtes\n• Types : Romantique, Élégant";
    } else if (mois >= 6 && mois <= 8) {
        saison = "🌞 ÉTÉ";
        message = "• Période : Juin à Août\n• Lieux : Plage, Jardin\n• Types : Festif, Romantique";
    } else if (mois >= 9 && mois <= 11) {
        saison = "🍂 AUTOMNE";
        message = "• Période : Septembre à Novembre\n• Lieux : Salle des fêtes, Restaurant\n• Types : Élégant, Formel";
    } else {
        saison = "❄️ HIVER";
        message = "• Période : Décembre à Février\n• Lieux : Hôtel, Salle de conférence\n• Types : Festif, Élégant";
    }

    // Mettre à jour les 2 labels dans l'onglet Calendrier
    ui->labelAlerteSaison->setText(saison);
    ui->labelMessageSaison->setText(message);

    qDebug() << "Conseils saisonniers pour" << date.toString("MMMM yyyy") << ":" << saison;
}
// ==================== TRI AMÉLIORÉ MULTI-COLONNES ====================

void MainWindow::on_pushButtontri_clicked()
{
    // Boîte de dialogue pour choisir le critère de tri
    QStringList criteres;
    criteres << "ID" << "Nom" << "Date" << "Lieu" << "Type" << "Participants" << "Budget";

    bool ok;
    QString critere = QInputDialog::getItem(this, "Trier les événements",
                                            "Choisissez le critère de tri:",
                                            criteres, 0, false, &ok);

    if (!ok) {
        return;
    }

    // Demander l'ordre de tri
    QStringList ordres;
    ordres << "Croissant (A-Z, 0-9)" << "Décroissant (Z-A, 9-0)";

    QString ordre = QInputDialog::getItem(this, "Ordre de tri",
                                          "Choisissez l'ordre de tri:",
                                          ordres, 0, false, &ok);

    if (!ok) {
        return;
    }

    bool ascending = (ordre == "Croissant (A-Z, 0-9)");
    int columnIndex = -1;

    // Déterminer la colonne et appliquer le tri
    if (critere == "ID") {
        columnIndex = 0;
        model->setSort(0, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Nom") {
        columnIndex = 1;
        model->setSort(1, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Date") {
        columnIndex = 2;
        model->setSort(2, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Lieu") {
        columnIndex = 3;
        model->setSort(3, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Type") {
        columnIndex = 4;
        model->setSort(4, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Participants") {
        columnIndex = 5;
        model->setSort(5, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    } else if (critere == "Budget") {
        columnIndex = 6;
        model->setSort(6, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    }

    if (columnIndex != -1) {
        model->select();
        ui->tableView->resizeColumnsToContents();

        // Mettre en surbrillance la colonne triée
        ui->tableView->sortByColumn(columnIndex, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);

        QString ordreTexte = ascending ? "croissant" : "décroissant";
        QMessageBox::information(this, "Tri effectué",
                                 QString("Tri par %1 (%2) appliqué avec succès!")
                                     .arg(critere)
                                     .arg(ordreTexte));
    }
}

// ==================== GÉNÉRATION PDF - VERSION SIMPLIFIÉE ET CORRECTE ====================
// ==================== GÉNÉRATION PDF AMÉLIORÉE ====================

// ==================== GÉNÉRATION PDF AMÉLIORÉE ====================

void MainWindow::on_pushButtonpdf_clicked()
{
    qDebug() << "Génération PDF démarrée";

    // Vérifier s'il y a des données à exporter
    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "Aucune donnée",
                             "Aucun événement à exporter en PDF.");
        return;
    }

    // Choisir où enregistrer le PDF
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer le PDF",
        QString("Evenements_%1.pdf").arg(QDate::currentDate().toString("ddMMyyyy")),
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    // Création du PDF
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageMargins(QMargins(30, 30, 30, 30));
    pdf.setResolution(150);

    QPainter painter(&pdf);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // ===== EN-TÊTE =====
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont subtitleFont("Arial", 12);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);
    QFont footerFont("Arial", 8);

    // Titre principal
    painter.setFont(titleFont);
    painter.setPen(QColor(139, 0, 139)); // Violet foncé
    painter.drawText(pdf.width()/2 - 250, 50, "RAPPORT DES ÉVÉNEMENTS");

    // Sous-titre
    painter.setFont(subtitleFont);
    painter.setPen(Qt::black);
    painter.drawText(pdf.width()/2 - 150, 80,
                     "Liste complète des événements planifiés");

    // Informations de génération
    painter.drawText(50, 110,
                     QString("Généré le: %1 à %2")
                         .arg(QDate::currentDate().toString("dd/MM/yyyy"))
                         .arg(QTime::currentTime().toString("hh:mm")));

    painter.drawText(pdf.width() - 250, 110,
                     QString("Total: %1 événement(s)").arg(model->rowCount()));

    // Ligne de séparation
    painter.setPen(QPen(QColor(139, 0, 139), 2));
    painter.drawLine(50, 125, pdf.width() - 50, 125);

    int y = 150;
    int lineHeight = 25;
    int pageHeight = pdf.height() - 50;

    // ===== EN-TÊTE DU TABLEAU =====
    painter.setFont(headerFont);
    painter.setBrush(QBrush(QColor(255, 182, 193))); // Rose clair
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(30, y, pdf.width() - 60, lineHeight);

    // Texte de l'en-tête avec ESPACEMENT MAXIMAL
    painter.setPen(Qt::black);
    int x = 35;
    painter.drawText(x, y + 18, "ID"); x += 60;
    painter.drawText(x + 10, y + 18, "Nom"); x += 150;
    painter.drawText(x + 15, y + 18, "Date"); x += 100;
    painter.drawText(x + 20, y + 18, "Lieu"); x += 130;
    painter.drawText(x + 25, y + 18, "Type"); x += 120;
    painter.drawText(x + 20, y + 18, "Part."); x += 80;
    painter.drawText(x + 15, y + 18, "Budget"); x += 90;

    y += lineHeight;

    // ===== DONNÉES DES ÉVÉNEMENTS =====
    painter.setFont(dataFont);
    int eventCount = 0;
    double totalBudget = 0;

    for (int i = 0; i < model->rowCount(); ++i) {
        // Vérifier si on doit créer une nouvelle page
        if (y > pageHeight) {
            pdf.newPage();
            y = 50;

            // Redessiner l'en-tête sur la nouvelle page
            painter.setFont(headerFont);
            painter.setBrush(QBrush(QColor(255, 182, 193)));
            painter.setPen(QPen(Qt::black, 1));
            painter.drawRect(30, y, pdf.width() - 60, lineHeight);

            painter.setPen(Qt::black);
            x = 35;
            painter.drawText(x, y + 18, "ID"); x += 60;
            painter.drawText(x + 10, y + 18, "Nom"); x += 150;
            painter.drawText(x + 15, y + 18, "Date"); x += 100;
            painter.drawText(x + 20, y + 18, "Lieu"); x += 130;
            painter.drawText(x + 25, y + 18, "Type"); x += 120;
            painter.drawText(x + 20, y + 18, "Part."); x += 80;
            painter.drawText(x + 15, y + 18, "Budget"); x += 90;

            y += lineHeight;
            painter.setFont(dataFont);
        }

        // Alterner les couleurs de fond pour une meilleure lisibilité
        if (i % 2 == 0) {
            painter.setBrush(QBrush(QColor(255, 250, 250))); // Rose très clair
        } else {
            painter.setBrush(QBrush(Qt::white));
        }

        painter.setPen(QPen(Qt::black, 1));
        painter.drawRect(30, y, pdf.width() - 60, lineHeight);

        // Dessiner les données avec ESPACEMENT MAXIMAL
        painter.setPen(QPen(Qt::black));
        x = 35;

        // ID
        QString id = model->index(i, 0).data().toString();
        painter.drawText(x, y + 18, id); x += 60;

        // Nom (tronqué si trop long)
        QString nom = model->index(i, 1).data().toString();
        painter.drawText(x + 10, y + 18, nom.left(20)); x += 150;

        // Date
        QDate date = model->index(i, 2).data().toDate();
        painter.drawText(x + 15, y + 18, date.toString("dd/MM/yyyy")); x += 100;

        // Lieu (tronqué si trop long)
        QString lieu = model->index(i, 3).data().toString();
        painter.drawText(x + 20, y + 18, lieu.left(15)); x += 130;

        // Type
        QString type = model->index(i, 4).data().toString();
        painter.drawText(x + 25, y + 18, type); x += 120;

        // Participants
        QString participants = model->index(i, 5).data().toString();
        painter.drawText(x + 20, y + 18, participants); x += 80;

        // Budget
        double budget = model->index(i, 6).data().toDouble();
        totalBudget += budget;
        painter.drawText(x + 15, y + 18, QString::number(budget, 'f', 2) + " M"); x += 90;

        y += lineHeight;
        eventCount++;
    }

    // ===== PIED DE PAGE =====
    painter.setPen(QPen(QColor(139, 0, 139), 2));
    painter.drawLine(50, y + 10, pdf.width() - 50, y + 10);

    painter.setFont(footerFont);
    painter.setPen(Qt::black);
    painter.drawText(50, y + 30,
                     QString("Rapport généré par l'Application de Gestion d'Événements"));

    // Résumé
    painter.setFont(dataFont);
    painter.drawText(pdf.width() - 300, y + 30,
                     QString("Budget total: %1 M").arg(QString::number(totalBudget, 'f', 2)));

    painter.end();

    // Message de confirmation
    QMessageBox::information(this, "PDF généré avec succès",
                             QString("Le rapport PDF a été créé avec succès!\n\n"
                                     "Fichier: %1\n"
                                     "Événements exportés: %2\n"
                                     "Budget total: %3 M")
                                 .arg(fileName)
                                 .arg(eventCount)
                                 .arg(QString::number(totalBudget, 'f', 2)));

    qDebug() << "PDF généré avec succès:" << fileName;
}
