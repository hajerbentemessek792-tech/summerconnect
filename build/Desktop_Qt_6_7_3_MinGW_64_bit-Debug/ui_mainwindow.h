/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextEdit *textEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *pushButton_ajouter;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_prenom;
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_email;
    QLineEdit *lineEdit_telephone;
    QLabel *label_17;
    QLabel *label_45;
    QDateEdit *dateEdit_naissance;
    QLabel *label_6;
    QLabel *label_4;
    QWidget *tab_3;
    QTextEdit *textEdit_2;
    QLabel *label_7;
    QLineEdit *lineEdit_id_afficher;
    QPushButton *pushButton_afficher;
    QTableView *tableView_client;
    QLabel *label_18;
    QLabel *label_46;
    QPushButton *pushButtonpdf;
    QPushButton *pushButton_trier;
    QWidget *tab_4;
    QTextEdit *textEdit_3;
    QLabel *label_8;
    QLineEdit *lineEdit_id_recherche;
    QLabel *label_9;
    QLineEdit *lineEdit_nom_modif;
    QLineEdit *lineEdit_id_modif;
    QLineEdit *lineEdit_email_modif;
    QLineEdit *lineEdit_telephone_modif;
    QLineEdit *lineEdit_prenom_modif;
    QLabel *label_11;
    QLabel *label_13;
    QPushButton *pushButton_sauvegarder;
    QLabel *label_19;
    QLabel *label_14;
    QDateEdit *dateEdit_naissance_modif;
    QLabel *label_12;
    QLabel *label_10;
    QPushButton *pushButton_chercher;
    QWidget *tab_2;
    QPushButton *pushButton_supprimer;
    QTextEdit *textEdit_4;
    QLabel *label_15;
    QLineEdit *lineEdit_id_supprimer;
    QLabel *label_20;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnClient_2;
    QPushButton *btnEvenement_2;
    QLabel *label_48;
    QWidget *tab_5;
    QLineEdit *lineEdit_rechercheNom;
    QTextEdit *textEdit_5;
    QLabel *label_16;
    QPushButton *pushButton_rechercheNom;
    QTableView *tableView_recherche;
    QWidget *tab_6;
    QTextEdit *textEdit_6;
    QLineEdit *lineEdit_id_client;
    QLineEdit *lineEdit_id_evenement;
    QDateTimeEdit *dateTimeEdit_inscription;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_26;
    QPushButton *pushButton_inscrire;
    QPushButton *btn_localisation;
    QWidget *widget_map;
    QWidget *tab_7;
    QLabel *label_21;
    QTextEdit *textEdit_8;
    QLineEdit *lineEdit_id_client_reco;
    QPushButton *pushButton_verifier;
    QLabel *label_reco;
    QWidget *tr;
    QTextEdit *textEdit_7;
    QTextEdit *textEdit_stat;
    QGraphicsView *graphicsView_2;
    QPushButton *ActualiserStats;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1273, 775);
        QFont font;
        font.setPointSize(1);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(270, 10, 821, 731));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setBold(false);
        tabWidget->setFont(font1);
        tabWidget->setStyleSheet(QString::fromUtf8("/* Th\303\250me Rose/Saumon cr\303\251atif pour l'interface de gestion clients */\n"
"\n"
"/* Style g\303\251n\303\251ral de la fen\303\252tre */\n"
"QWidget {\n"
"    background-color: #fff0f5; /* Rose lavande tr\303\250s clair */\n"
"    color: #8b475d; /* Rose fonc\303\251 */\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* ===== STYLE DES ONGLETS (TAB WIDGET) ===== */\n"
"QTabWidget::pane {\n"
"    border: 3px solid #ffb6c1;\n"
"    border-radius: 12px;\n"
"    background: rgba(255, 255, 255, 0.9);\n"
"    margin: 5px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    alignment: center;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffe4e9, stop: 0.4 #ffd1dc, stop: 1 #ffb6c1);\n"
"    border: 2px solid #ff91a4;\n"
"    border-bottom: none;\n"
"    border-top-left-radius: 8px;\n"
"    border-top-right-radius: 8px;\n"
"    min-width: 90px;\n"
"    padding: 10px 15px;\n"
"    ma"
                        "rgin-right: 2px;\n"
"    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffffff, stop: 1 #ffd1dc);\n"
"    border: 2px solid #ff6b8b;\n"
"    font-weight: bolder;\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffffff, stop: 1 #ff91a4);\n"
"}\n"
"\n"
"/* Style des boutons principaux */\n"
"QPushButton {\n"
"    background-color: #ffd1dc; /* Rose pastel */\n"
"    color: #8b475d;\n"
"    border: 2px solid #ffb6c1;\n"
"    border-radius: 15px;\n"
"    padding: 10px 20px;\n"
"    font-weight: bold;\n"
"    margin: 3px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ffb6c1;\n"
"    border: 2px solid #ff91a4;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
""
                        "    background-color: #ff91a4;\n"
"}\n"
"\n"
"/* Style sp\303\251cifique pour chaque bouton avec des couleurs diff\303\251rentes */\n"
"QPushButton[text=\"Ajouter\"] {\n"
"    background-color: #ffd1dc; /* Rose clair */\n"
"    border: 2px solid #ffb6c1;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"QPushButton[text=\"Afficher\"] {\n"
"    background-color: #ffcccb; /* Saumon clair */\n"
"    border: 2px solid #ffa07a;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"QPushButton[text=\"Modifier\"] {\n"
"    background-color: #f8c8dc; /* Rose poudr\303\251 */\n"
"    border: 2px solid #f4acb6;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"QPushButton[text=\"Supprimer\"] {\n"
"    background-color: #ffb7c5; /* Rose corail */\n"
"    border: 2px solid #ff91a4;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"/* Style pour les boutons d'action sp\303\251cifiques */\n"
"QPushButton[text=\"ajouter\"] {\n"
"    background-color: #ffb6c1; /* Rose moyen */\n"
"    border: 2px solid #ff91a4;\n"
"    color: #8b475d;\n"
"    border-radius: 20px;\n"
"    p"
                        "adding: 12px 25px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"ajouter\"]:hover {\n"
"    background-color: #ff91a4;\n"
"}\n"
"\n"
"QPushButton[text=\"sauvegarder\"] {\n"
"    background-color: #98fb98; /* Vert pastel pour sauvegarder */\n"
"    border: 2px solid #90ee90;\n"
"    color: #2e8b57;\n"
"    border-radius: 20px;\n"
"    padding: 12px 25px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"sauvegarder\"]:hover {\n"
"    background-color: #90ee90;\n"
"}\n"
"\n"
"QPushButton[text=\"supprimer\"] {\n"
"    background-color: #ffb7c5; /* Rose corail */\n"
"    border: 2px solid #ff91a4;\n"
"    color: #8b475d;\n"
"    border-radius: 20px;\n"
"    padding: 12px 25px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"supprimer\"]:hover {\n"
"    background-color: #ff91a4;\n"
"}\n"
"\n"
"QPushButton[text=\"afficher les informations\"] {\n"
"    background-color: #ffcccb; /* Saumon clair */\n"
"  "
                        "  border: 2px solid #ffa07a;\n"
"    color: #8b475d;\n"
"    border-radius: 20px;\n"
"    padding: 12px 25px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"afficher les informations\"]:hover {\n"
"    background-color: #ffa07a;\n"
"}\n"
"\n"
"QPushButton[text=\"chercher\"] {\n"
"    background-color: #f8c8dc; /* Rose poudr\303\251 */\n"
"    border: 2px solid #f4acb6;\n"
"    color: #8b475d;\n"
"    border-radius: 15px;\n"
"    padding: 8px 15px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"chercher\"]:hover {\n"
"    background-color: #f4acb6;\n"
"}\n"
"\n"
"/* Style des champs de saisie */\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #ffd1dc;\n"
"    border-radius: 10px;\n"
"    padding: 8px 12px;\n"
"    color: #8b475d;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #ff91a4;\n"
"    background-color: #fffafafa;\n"
"}\n"
"\n"
"/* Style des labels */\n"
"QLabel "
                        "{\n"
"    color: #8b475d;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    background-color: rgba(255, 240, 245, 0.7); /* Fond rose tr\303\250s l\303\251ger */\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Style des titres principaux */\n"
"QLabel[text=\"ajouter un client\"],\n"
"QLabel[text=\"afficher un client\"], \n"
"QLabel[text=\"modifier un client\"],\n"
"QLabel[text=\"supprimer un client\"] {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #8b475d;\n"
"    background-color: rgba(255, 209, 220, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"/* Style des sous-titres */\n"
"QLabel[text=\"chercher l'ID:\"] {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    color: #8b475d;\n"
"    background-color: rgba(255, 240, 245, 0.9);\n"
"    padding: 8px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"/* Style pour les s\303\251parateurs horizontaux */\n"
"QFrame[frameShape=\"4\"] { /* HLine */\n"
"    bac"
                        "kground-color: #ffb6c1;\n"
"    border: none;\n"
"    height: 2px;\n"
"    margin: 10px 0px;\n"
"}\n"
"\n"
"/* Style pour les champs date */\n"
"QLineEdit[text=\"01/01/2000\"] {\n"
"    background-color: #fff0f5;\n"
"    border: 2px solid #ffd1dc;\n"
"    font-style: italic;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"/* Style pour les QTextEdit */\n"
"QTextEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #ffd1dc;\n"
"    border-radius: 8px;\n"
"    padding: 6px 10px;\n"
"    color: #8b475d;\n"
"    font-size: 14px;\n"
"    selection-background-color: #ffb6c1;\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border: 2px solid #ff91a4;\n"
"    background-color: #fffafafa;\n"
"}\n"
"\n"
"/* Style pour les QTableWidget */\n"
"QTableWidget {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #ffd1dc;\n"
"    border-radius: 8px;\n"
"    gridline-color: #ffd1dc;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 6px;\n"
"    border-bottom: 1px solid #ffe4e9;\n"
"    color: "
                        "#8b475d;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #ffb6c1;\n"
"    color: #8b475d;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #ffd1dc;\n"
"    color: #8b475d;\n"
"    padding: 8px;\n"
"    border: 1px solid #ffb6c1;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Style pour les cases \303\240 cocher */\n"
"QCheckBox {\n"
"    color: #8b475d;\n"
"    font-size: 14px;\n"
"    spacing: 6px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"    border: 2px solid #ffb6c1;\n"
"    border-radius: 4px;\n"
"    background: white;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background: #ff91a4;\n"
"    border: 2px solid #ff6b8b;\n"
"}\n"
"\n"
"/* Effets d'ombre l\303\251gers pour la profondeur */\n"
"QPushButton, QLineEdit, QLabel, QTextEdit, QTableWidget {\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"/* Style pour le layout g\303\251n\303\251ral */\n"
"QWidget#centralWidget {\n"
"    background: qlinearg"
                        "radient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #fff0f5, stop: 1 #ffe4e9);\n"
"    border-radius: 15px;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 30, 701, 51));
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 140, 71, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setBold(true);
        font2.setItalic(true);
        label->setFont(font2);
        label->setTextFormat(Qt::TextFormat::RichText);
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 310, 81, 31));
        label_2->setFont(font2);
        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 260, 63, 31));
        label_3->setFont(font2);
        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 370, 101, 41));
        label_5->setFont(font2);
        pushButton_ajouter = new QPushButton(tab);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(90, 500, 641, 61));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setBold(true);
        pushButton_ajouter->setFont(font3);
        lineEdit_nom = new QLineEdit(tab);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(140, 130, 481, 41));
        lineEdit_prenom = new QLineEdit(tab);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(140, 190, 481, 41));
        lineEdit_id = new QLineEdit(tab);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(140, 250, 481, 41));
        lineEdit_email = new QLineEdit(tab);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(140, 310, 481, 41));
        lineEdit_telephone = new QLineEdit(tab);
        lineEdit_telephone->setObjectName("lineEdit_telephone");
        lineEdit_telephone->setGeometry(QRect(140, 370, 481, 41));
        label_17 = new QLabel(tab);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(870, 650, 101, 91));
        label_17->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        label_45 = new QLabel(tab);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(700, 560, 101, 81));
        label_45->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        dateEdit_naissance = new QDateEdit(tab);
        dateEdit_naissance->setObjectName("dateEdit_naissance");
        dateEdit_naissance->setGeometry(QRect(140, 430, 481, 41));
        dateEdit_naissance->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 430, 141, 41));
        label_6->setFont(font2);
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 200, 121, 31));
        label_4->setFont(font2);
        label_4->setTextFormat(Qt::TextFormat::RichText);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        tabWidget->addTab(tab, icon, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        textEdit_2 = new QTextEdit(tab_3);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(20, 20, 731, 51));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 90, 131, 31));
        label_7->setFont(font2);
        lineEdit_id_afficher = new QLineEdit(tab_3);
        lineEdit_id_afficher->setObjectName("lineEdit_id_afficher");
        lineEdit_id_afficher->setGeometry(QRect(190, 90, 571, 41));
        pushButton_afficher = new QPushButton(tab_3);
        pushButton_afficher->setObjectName("pushButton_afficher");
        pushButton_afficher->setGeometry(QRect(30, 150, 751, 61));
        pushButton_afficher->setFont(font3);
        tableView_client = new QTableView(tab_3);
        tableView_client->setObjectName("tableView_client");
        tableView_client->setGeometry(QRect(100, 220, 621, 271));
        tableView_client->setStyleSheet(QString::fromUtf8("border: 2px solid #FFB6C1 !important;\n"
"\n"
"padding: 5px;\n"
"border-radius: 3px;\n"
""));
        label_18 = new QLabel(tab_3);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(870, 650, 101, 91));
        label_18->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        label_46 = new QLabel(tab_3);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(700, 570, 101, 81));
        label_46->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        pushButtonpdf = new QPushButton(tab_3);
        pushButtonpdf->setObjectName("pushButtonpdf");
        pushButtonpdf->setGeometry(QRect(130, 500, 581, 61));
        pushButtonpdf->setFont(font3);
        pushButton_trier = new QPushButton(tab_3);
        pushButton_trier->setObjectName("pushButton_trier");
        pushButton_trier->setGeometry(QRect(130, 570, 581, 61));
        pushButton_trier->setFont(font3);
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("address-book-new")));
        tabWidget->addTab(tab_3, icon1, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        textEdit_3 = new QTextEdit(tab_4);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setGeometry(QRect(40, 30, 741, 51));
        label_8 = new QLabel(tab_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(50, 120, 141, 31));
        label_8->setFont(font2);
        lineEdit_id_recherche = new QLineEdit(tab_4);
        lineEdit_id_recherche->setObjectName("lineEdit_id_recherche");
        lineEdit_id_recherche->setGeometry(QRect(190, 110, 571, 51));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 250, 63, 31));
        label_9->setFont(font2);
        lineEdit_nom_modif = new QLineEdit(tab_4);
        lineEdit_nom_modif->setObjectName("lineEdit_nom_modif");
        lineEdit_nom_modif->setGeometry(QRect(150, 240, 601, 41));
        lineEdit_id_modif = new QLineEdit(tab_4);
        lineEdit_id_modif->setObjectName("lineEdit_id_modif");
        lineEdit_id_modif->setGeometry(QRect(150, 350, 601, 41));
        lineEdit_email_modif = new QLineEdit(tab_4);
        lineEdit_email_modif->setObjectName("lineEdit_email_modif");
        lineEdit_email_modif->setGeometry(QRect(150, 400, 601, 41));
        lineEdit_telephone_modif = new QLineEdit(tab_4);
        lineEdit_telephone_modif->setObjectName("lineEdit_telephone_modif");
        lineEdit_telephone_modif->setGeometry(QRect(150, 460, 601, 41));
        lineEdit_prenom_modif = new QLineEdit(tab_4);
        lineEdit_prenom_modif->setObjectName("lineEdit_prenom_modif");
        lineEdit_prenom_modif->setGeometry(QRect(150, 290, 601, 51));
        label_11 = new QLabel(tab_4);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(50, 360, 63, 31));
        label_11->setFont(font2);
        label_13 = new QLabel(tab_4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 470, 101, 31));
        label_13->setFont(font2);
        pushButton_sauvegarder = new QPushButton(tab_4);
        pushButton_sauvegarder->setObjectName("pushButton_sauvegarder");
        pushButton_sauvegarder->setGeometry(QRect(30, 570, 751, 51));
        pushButton_sauvegarder->setFont(font3);
        label_19 = new QLabel(tab_4);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(860, 650, 101, 91));
        label_19->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        label_14 = new QLabel(tab_4);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(40, 410, 63, 41));
        label_14->setFont(font2);
        dateEdit_naissance_modif = new QDateEdit(tab_4);
        dateEdit_naissance_modif->setObjectName("dateEdit_naissance_modif");
        dateEdit_naissance_modif->setGeometry(QRect(150, 520, 601, 41));
        dateEdit_naissance_modif->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_12 = new QLabel(tab_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 520, 141, 41));
        label_12->setFont(font2);
        label_10 = new QLabel(tab_4);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 300, 91, 41));
        label_10->setFont(font2);
        pushButton_chercher = new QPushButton(tab_4);
        pushButton_chercher->setObjectName("pushButton_chercher");
        pushButton_chercher->setGeometry(QRect(90, 170, 671, 61));
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("edit-redo")));
        tabWidget->addTab(tab_4, icon2, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        pushButton_supprimer = new QPushButton(tab_2);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(70, 290, 691, 71));
        pushButton_supprimer->setFont(font3);
        textEdit_4 = new QTextEdit(tab_2);
        textEdit_4->setObjectName("textEdit_4");
        textEdit_4->setGeometry(QRect(10, 30, 751, 51));
        label_15 = new QLabel(tab_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(72, 180, 141, 41));
        label_15->setFont(font2);
        lineEdit_id_supprimer = new QLineEdit(tab_2);
        lineEdit_id_supprimer->setObjectName("lineEdit_id_supprimer");
        lineEdit_id_supprimer->setGeometry(QRect(210, 170, 531, 51));
        label_20 = new QLabel(tab_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(860, 650, 111, 91));
        label_20->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        verticalLayoutWidget_2 = new QWidget(tab_2);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(-170, 0, 171, 731));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnClient_2 = new QPushButton(verticalLayoutWidget_2);
        btnClient_2->setObjectName("btnClient_2");

        verticalLayout_2->addWidget(btnClient_2);

        btnEvenement_2 = new QPushButton(verticalLayoutWidget_2);
        btnEvenement_2->setObjectName("btnEvenement_2");

        verticalLayout_2->addWidget(btnEvenement_2);

        label_48 = new QLabel(tab_2);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(700, 540, 101, 81));
        label_48->setPixmap(QPixmap(QString::fromUtf8("../../../../ll.png")));
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("edit-delete")));
        tabWidget->addTab(tab_2, icon3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        lineEdit_rechercheNom = new QLineEdit(tab_5);
        lineEdit_rechercheNom->setObjectName("lineEdit_rechercheNom");
        lineEdit_rechercheNom->setGeometry(QRect(190, 130, 571, 51));
        textEdit_5 = new QTextEdit(tab_5);
        textEdit_5->setObjectName("textEdit_5");
        textEdit_5->setGeometry(QRect(30, 40, 751, 51));
        label_16 = new QLabel(tab_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(50, 140, 131, 41));
        label_16->setFont(font3);
        pushButton_rechercheNom = new QPushButton(tab_5);
        pushButton_rechercheNom->setObjectName("pushButton_rechercheNom");
        pushButton_rechercheNom->setGeometry(QRect(40, 210, 751, 61));
        pushButton_rechercheNom->setFont(font3);
        tableView_recherche = new QTableView(tab_5);
        tableView_recherche->setObjectName("tableView_recherche");
        tableView_recherche->setGeometry(QRect(90, 290, 621, 341));
        tableView_recherche->setStyleSheet(QString::fromUtf8("border: 2px solid #FFB6C1 !important;\n"
"\n"
"padding: 5px;\n"
"border-radius: 3px;\n"
""));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        textEdit_6 = new QTextEdit(tab_6);
        textEdit_6->setObjectName("textEdit_6");
        textEdit_6->setGeometry(QRect(30, 30, 751, 51));
        lineEdit_id_client = new QLineEdit(tab_6);
        lineEdit_id_client->setObjectName("lineEdit_id_client");
        lineEdit_id_client->setGeometry(QRect(200, 90, 481, 41));
        lineEdit_id_evenement = new QLineEdit(tab_6);
        lineEdit_id_evenement->setObjectName("lineEdit_id_evenement");
        lineEdit_id_evenement->setGeometry(QRect(200, 150, 481, 41));
        dateTimeEdit_inscription = new QDateTimeEdit(tab_6);
        dateTimeEdit_inscription->setObjectName("dateTimeEdit_inscription");
        dateTimeEdit_inscription->setGeometry(QRect(200, 210, 481, 41));
        label_23 = new QLabel(tab_6);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(90, 90, 81, 41));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setBold(true);
        font4.setItalic(false);
        label_23->setFont(font4);
        label_24 = new QLabel(tab_6);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(70, 150, 121, 31));
        label_24->setFont(font4);
        label_26 = new QLabel(tab_6);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(60, 210, 131, 41));
        pushButton_inscrire = new QPushButton(tab_6);
        pushButton_inscrire->setObjectName("pushButton_inscrire");
        pushButton_inscrire->setGeometry(QRect(70, 260, 641, 61));
        pushButton_inscrire->setFont(font3);
        btn_localisation = new QPushButton(tab_6);
        btn_localisation->setObjectName("btn_localisation");
        btn_localisation->setGeometry(QRect(70, 330, 641, 61));
        btn_localisation->setFont(font3);
        widget_map = new QWidget(tab_6);
        widget_map->setObjectName("widget_map");
        widget_map->setGeometry(QRect(100, 410, 591, 231));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        label_21 = new QLabel(tab_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(50, 130, 141, 41));
        label_21->setFont(font2);
        textEdit_8 = new QTextEdit(tab_7);
        textEdit_8->setObjectName("textEdit_8");
        textEdit_8->setGeometry(QRect(30, 30, 751, 51));
        lineEdit_id_client_reco = new QLineEdit(tab_7);
        lineEdit_id_client_reco->setObjectName("lineEdit_id_client_reco");
        lineEdit_id_client_reco->setGeometry(QRect(210, 120, 531, 51));
        pushButton_verifier = new QPushButton(tab_7);
        pushButton_verifier->setObjectName("pushButton_verifier");
        pushButton_verifier->setGeometry(QRect(70, 200, 671, 61));
        label_reco = new QLabel(tab_7);
        label_reco->setObjectName("label_reco");
        label_reco->setGeometry(QRect(110, 300, 601, 131));
        tabWidget->addTab(tab_7, QString());
        tr = new QWidget();
        tr->setObjectName("tr");
        textEdit_7 = new QTextEdit(tr);
        textEdit_7->setObjectName("textEdit_7");
        textEdit_7->setGeometry(QRect(40, 30, 741, 51));
        textEdit_stat = new QTextEdit(tr);
        textEdit_stat->setObjectName("textEdit_stat");
        textEdit_stat->setGeometry(QRect(440, 130, 321, 301));
        graphicsView_2 = new QGraphicsView(tr);
        graphicsView_2->setObjectName("graphicsView_2");
        graphicsView_2->setGeometry(QRect(60, 130, 351, 311));
        ActualiserStats = new QPushButton(tr);
        ActualiserStats->setObjectName("ActualiserStats");
        ActualiserStats->setGeometry(QRect(70, 460, 691, 71));
        ActualiserStats->setFont(font3);
        tabWidget->addTab(tr, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1273, 9));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Ajouter un client</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "t\303\251l\303\251phone:", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_17->setText(QString());
        label_45->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Date de naissance:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "pr\303\251nom:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Afficher un client</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "chercher l'ID:", nullptr));
        pushButton_afficher->setText(QCoreApplication::translate("MainWindow", "afficher les informations", nullptr));
        label_18->setText(QString());
        label_46->setText(QString());
        pushButtonpdf->setText(QCoreApplication::translate("MainWindow", "t\303\251l\303\251charger PDF", nullptr));
        pushButton_trier->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        textEdit_3->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Modifier un client</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "chercher l'ID:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "nom:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "t\303\251l\303\251phone:", nullptr));
        pushButton_sauvegarder->setText(QCoreApplication::translate("MainWindow", "sauvegarder", nullptr));
        label_19->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date de naissance:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom:", nullptr));
        pushButton_chercher->setText(QCoreApplication::translate("MainWindow", "chercher", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        textEdit_4->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Supprimer un client</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "chercher l'ID:", nullptr));
        label_20->setText(QString());
        btnClient_2->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        btnEvenement_2->setText(QCoreApplication::translate("MainWindow", "Ev\303\251nement", nullptr));
        label_48->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        textEdit_5->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">chercher un client</span></p></body></html>", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "chercher un nom:", nullptr));
        pushButton_rechercheNom->setText(QCoreApplication::translate("MainWindow", "afficher les informations", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "chercher", nullptr));
        textEdit_6->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">inscrire un client a un evenement</span></p></body></html>", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "ID client:", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "ID evenement:", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "date_inscription:", nullptr));
        pushButton_inscrire->setText(QCoreApplication::translate("MainWindow", "INSCRIRE", nullptr));
        btn_localisation->setText(QCoreApplication::translate("MainWindow", "envoyer la localisation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "inscription", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "chercher l'ID:", nullptr));
        textEdit_8->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">recommander un client</span></p></body></html>", nullptr));
        pushButton_verifier->setText(QCoreApplication::translate("MainWindow", "chercher", nullptr));
        label_reco->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("MainWindow", "recommander", nullptr));
        textEdit_7->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">statistique des clients</span></p></body></html>", nullptr));
        ActualiserStats->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tr), QCoreApplication::translate("MainWindow", "statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
