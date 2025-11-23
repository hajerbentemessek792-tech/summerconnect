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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabajouter;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLineEdit *lineEditnom;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBoxtype;
    QLabel *label_5;
    QDateEdit *dateEdit;
    QLabel *label_6;
    QLabel *label_8;
    QSpinBox *spinBoxbudget;
    QLabel *label_7;
    QSpinBox *spinBoxnbrpartic;
    QLineEdit *lineEditid;
    QComboBox *comboBoxlieu;
    QPushButton *pushButtonvalider;
    QPushButton *pushButtonannuler;
    QLabel *label_13;
    QWidget *tabafficher;
    QTableView *tableView;
    QTextEdit *textEdit_2;
    QLabel *label_9;
    QLineEdit *lineEditchercherid;
    QPushButton *pushButtonafficher;
    QLabel *label_10;
    QPushButton *pushButtonpdf;
    QPushButton *pushButtontri;
    QWidget *tabmodifier;
    QTextEdit *textEdit_6;
    QLabel *label_25;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_13;
    QLabel *label_18;
    QLineEdit *lineEdit_7;
    QLabel *label_19;
    QLineEdit *lineEdit_8;
    QLabel *label_20;
    QComboBox *comboBox_6;
    QLabel *label_21;
    QDateEdit *dateEdit_4;
    QLabel *label_22;
    QComboBox *comboBox_7;
    QLabel *label_24;
    QLabel *label_23;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QPushButton *pushButton_14;
    QLabel *label_11;
    QPushButton *pushButton_16;
    QWidget *tabsupprimer;
    QPushButton *pushButtonsupprimer;
    QTextEdit *textEdit_5;
    QLineEdit *lineEditchercherid_2;
    QLabel *label_26;
    QLabel *label_12;
    QPushButton *pushButtoannuler;
    QWidget *tabcalendrier;
    QCalendarWidget *calendarWidget;
    QListWidget *listEventsToday;
    QGroupBox *groupBoxEventDetails;
    QLabel *label_44;
    QLineEdit *eventDetailsNom;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label_71;
    QDateEdit *eventDetailsDate;
    QComboBox *eventDetailsLieu;
    QComboBox *eventDetailsType;
    QPushButton *pushButtonEditEvent;
    QGroupBox *groupBoxPlanning;
    QLabel *label_72;
    QLineEdit *planNom;
    QLabel *label_73;
    QLabel *label_74;
    QLabel *label_75;
    QComboBox *planLieu;
    QComboBox *planType;
    QDateTimeEdit *planDate;
    QPushButton *pushButtonvalider_5;
    QWidget *tabstatistique;
    QGroupBox *groupBox;
    QLabel *label_total;
    QLabel *label_mois;
    QLabel *label_annee;
    QLabel *labeltype;
    QTableWidget *tableWidget_types;
    QWidget *chartWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1196, 829);
        QFont font;
        font.setPointSize(11);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(70, 40, 821, 691));
        tabWidget->setStyleSheet(QString::fromUtf8("/* Th\303\250me Rose/Saumon cr\303\251atif pour l'interface d'\303\251v\303\251nements */\n"
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
""
                        "    margin-right: 2px;\n"
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
"QPushButton:press"
                        "ed {\n"
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
"/* Style des champs de saisie */\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #ffd1dc;\n"
"    border-radius: 10px;\n"
"    padding: 8px 12px;\n"
"    color: #8b475d;\n"
"    font-size: 14px;\n"
"}\n"
""
                        "\n"
"QLineEdit:focus {\n"
"    border: 2px solid #ff91a4;\n"
"    background-color: #fffafafa;\n"
"}\n"
"\n"
"/* Style des labels */\n"
"QLabel {\n"
"    color: #8b475d;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    background-color: rgba(255, 240, 245, 0.7); /* Fond rose tr\303\250s l\303\251ger */\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Style du titre \"Ajouter un evenement\" */\n"
"QLabel[text=\"Ajouter un evenement\"] {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #8b475d;\n"
"    background-color: rgba(255, 209, 220, 0.8);\n"
"    padding: 10px;\n"
"    border-radius: 12px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"/* Style du bouton \"ajouter\" en bas */\n"
"QPushButton[text=\"ajouter\"] {\n"
"    background-color: #ffb6c1; /* Rose moyen */\n"
"    border: 2px solid #ff91a4;\n"
"    color: #8b475d;\n"
"    border-radius: 20px;\n"
"    padding: 12px 25px;\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton[text=\"a"
                        "jouter\"]:hover {\n"
"    background-color: #ff91a4;\n"
"}\n"
"\n"
"/* Style pour les champs num\303\251riques */\n"
"QLineEdit[placeholderText=\"0\"] {\n"
"    background-color: #fffaf0;\n"
"    border: 2px solid #ffebcd;\n"
"}\n"
"\n"
"/* Style pour le champ date */\n"
"QLineEdit[text=\"1/1/2000\"] {\n"
"    background-color: #fff0f5;\n"
"    border: 2px solid #ffd1dc;\n"
"}\n"
"\n"
"/* Style pour les QTextEdit dans les table widgets */\n"
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
"QTa"
                        "bleWidget::item {\n"
"    padding: 6px;\n"
"    border-bottom: 1px solid #ffe4e9;\n"
"    color: #8b475d;\n"
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
"/* Effets d'ombre l\303\251gers pour la profondeur */\n"
"QPushButton, QLineEdit, QLabel, QTextEdit, QTableWidget {\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"/* Style pour le layout g\303\251n\303\251ral */\n"
"QWidget#centralWidget {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #fff0f5, stop: 1 #ffe4e9);\n"
"    border-radius: 15px;\n"
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
"    wi"
                        "dth: 16px;\n"
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
""));
        tabWidget->setTabBarAutoHide(false);
        tabajouter = new QWidget();
        tabajouter->setObjectName("tabajouter");
        textEdit = new QTextEdit(tabajouter);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(60, 10, 681, 51));
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CursorShape::PointingHandCursor)));
        textEdit->setFrameShape(QFrame::Shape::StyledPanel);
        label_2 = new QLabel(tabajouter);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 100, 61, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setBold(true);
        font1.setItalic(true);
        label_2->setFont(font1);
        label_2->setTextFormat(Qt::TextFormat::AutoText);
        lineEditnom = new QLineEdit(tabajouter);
        lineEditnom->setObjectName("lineEditnom");
        lineEditnom->setGeometry(QRect(80, 90, 511, 41));
        label_3 = new QLabel(tabajouter);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 150, 61, 31));
        label_3->setFont(font1);
        label_4 = new QLabel(tabajouter);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 200, 81, 31));
        label_4->setFont(font1);
        comboBoxtype = new QComboBox(tabajouter);
        comboBoxtype->setObjectName("comboBoxtype");
        comboBoxtype->setGeometry(QRect(80, 200, 511, 31));
        comboBoxtype->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_5 = new QLabel(tabajouter);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 240, 61, 31));
        label_5->setFont(font1);
        dateEdit = new QDateEdit(tabajouter);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(80, 240, 511, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_6 = new QLabel(tabajouter);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 280, 61, 31));
        label_6->setFont(font1);
        label_8 = new QLabel(tabajouter);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 370, 71, 31));
        label_8->setFont(font1);
        spinBoxbudget = new QSpinBox(tabajouter);
        spinBoxbudget->setObjectName("spinBoxbudget");
        spinBoxbudget->setGeometry(QRect(90, 370, 501, 31));
        spinBoxbudget->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_7 = new QLabel(tabajouter);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 320, 181, 41));
        label_7->setFont(font1);
        spinBoxnbrpartic = new QSpinBox(tabajouter);
        spinBoxnbrpartic->setObjectName("spinBoxnbrpartic");
        spinBoxnbrpartic->setGeometry(QRect(210, 320, 381, 31));
        spinBoxnbrpartic->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        lineEditid = new QLineEdit(tabajouter);
        lineEditid->setObjectName("lineEditid");
        lineEditid->setGeometry(QRect(80, 140, 511, 41));
        comboBoxlieu = new QComboBox(tabajouter);
        comboBoxlieu->setObjectName("comboBoxlieu");
        comboBoxlieu->setGeometry(QRect(80, 280, 511, 31));
        comboBoxlieu->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        pushButtonvalider = new QPushButton(tabajouter);
        pushButtonvalider->setObjectName("pushButtonvalider");
        pushButtonvalider->setGeometry(QRect(440, 430, 221, 51));
        pushButtonvalider->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        pushButtonannuler = new QPushButton(tabajouter);
        pushButtonannuler->setObjectName("pushButtonannuler");
        pushButtonannuler->setGeometry(QRect(440, 500, 221, 51));
        pushButtonannuler->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        label_13 = new QLabel(tabajouter);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(700, 540, 101, 91));
        label_13->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/logo app1.png")));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        tabWidget->addTab(tabajouter, icon, QString());
        tabafficher = new QWidget();
        tabafficher->setObjectName("tabafficher");
        tableView = new QTableView(tabafficher);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(0, 210, 801, 291));
        tableView->setStyleSheet(QString::fromUtf8("\n"
"border: 2px solid #FFB6C1 !important;\n"
"\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        textEdit_2 = new QTextEdit(tabafficher);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(60, 10, 681, 51));
        label_9 = new QLabel(tabafficher);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 90, 111, 31));
        label_9->setFont(font1);
        lineEditchercherid = new QLineEdit(tabafficher);
        lineEditchercherid->setObjectName("lineEditchercherid");
        lineEditchercherid->setGeometry(QRect(130, 90, 521, 41));
        pushButtonafficher = new QPushButton(tabafficher);
        pushButtonafficher->setObjectName("pushButtonafficher");
        pushButtonafficher->setGeometry(QRect(80, 140, 651, 51));
        pushButtonafficher->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        label_10 = new QLabel(tabafficher);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(700, 540, 101, 91));
        label_10->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/logo app1.png")));
        pushButtonpdf = new QPushButton(tabafficher);
        pushButtonpdf->setObjectName("pushButtonpdf");
        pushButtonpdf->setGeometry(QRect(170, 510, 461, 51));
        pushButtonpdf->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        pushButtontri = new QPushButton(tabafficher);
        pushButtontri->setObjectName("pushButtontri");
        pushButtontri->setGeometry(QRect(170, 570, 461, 51));
        pushButtontri->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("emblem-system")));
        tabWidget->addTab(tabafficher, icon1, QString());
        tabmodifier = new QWidget();
        tabmodifier->setObjectName("tabmodifier");
        textEdit_6 = new QTextEdit(tabmodifier);
        textEdit_6->setObjectName("textEdit_6");
        textEdit_6->setGeometry(QRect(60, 10, 681, 51));
        label_25 = new QLabel(tabmodifier);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(20, 90, 111, 31));
        label_25->setFont(font1);
        lineEdit_9 = new QLineEdit(tabmodifier);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(130, 90, 521, 41));
        pushButton_13 = new QPushButton(tabmodifier);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(80, 140, 651, 51));
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        label_18 = new QLabel(tabmodifier);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(60, 200, 61, 31));
        label_18->setFont(font1);
        lineEdit_7 = new QLineEdit(tabmodifier);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(130, 200, 511, 41));
        label_19 = new QLabel(tabmodifier);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(60, 250, 61, 31));
        label_19->setFont(font1);
        lineEdit_8 = new QLineEdit(tabmodifier);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(130, 250, 511, 41));
        label_20 = new QLabel(tabmodifier);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(60, 300, 61, 31));
        label_20->setFont(font1);
        comboBox_6 = new QComboBox(tabmodifier);
        comboBox_6->addItem(QString());
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("\360\237\216\273")));
        comboBox_6->addItem(icon2, QString());
        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("\360\237\216\211")));
        comboBox_6->addItem(icon3, QString());
        QIcon icon4(QIcon::fromTheme(QString::fromUtf8("\360\237\214\270")));
        comboBox_6->addItem(icon4, QString());
        comboBox_6->setObjectName("comboBox_6");
        comboBox_6->setGeometry(QRect(130, 300, 511, 31));
        comboBox_6->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_21 = new QLabel(tabmodifier);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(60, 340, 61, 31));
        label_21->setFont(font1);
        dateEdit_4 = new QDateEdit(tabmodifier);
        dateEdit_4->setObjectName("dateEdit_4");
        dateEdit_4->setGeometry(QRect(130, 340, 511, 31));
        dateEdit_4->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_22 = new QLabel(tabmodifier);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(60, 380, 61, 31));
        label_22->setFont(font1);
        comboBox_7 = new QComboBox(tabmodifier);
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName("comboBox_7");
        comboBox_7->setGeometry(QRect(130, 380, 511, 31));
        comboBox_7->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        label_24 = new QLabel(tabmodifier);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(60, 420, 181, 31));
        label_24->setFont(font1);
        label_23 = new QLabel(tabmodifier);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(60, 460, 71, 31));
        label_23->setFont(font1);
        spinBox_5 = new QSpinBox(tabmodifier);
        spinBox_5->setObjectName("spinBox_5");
        spinBox_5->setGeometry(QRect(140, 460, 501, 31));
        spinBox_5->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        spinBox_6 = new QSpinBox(tabmodifier);
        spinBox_6->setObjectName("spinBox_6");
        spinBox_6->setGeometry(QRect(260, 420, 381, 31));
        spinBox_6->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        pushButton_14 = new QPushButton(tabmodifier);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(90, 500, 311, 51));
        pushButton_14->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        label_11 = new QLabel(tabmodifier);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(700, 550, 101, 71));
        label_11->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/logo app1.png")));
        pushButton_16 = new QPushButton(tabmodifier);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(410, 500, 311, 51));
        pushButton_16->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo));
        tabWidget->addTab(tabmodifier, icon5, QString());
        tabsupprimer = new QWidget();
        tabsupprimer->setObjectName("tabsupprimer");
        pushButtonsupprimer = new QPushButton(tabsupprimer);
        pushButtonsupprimer->setObjectName("pushButtonsupprimer");
        pushButtonsupprimer->setGeometry(QRect(80, 140, 651, 51));
        pushButtonsupprimer->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        textEdit_5 = new QTextEdit(tabsupprimer);
        textEdit_5->setObjectName("textEdit_5");
        textEdit_5->setGeometry(QRect(60, 10, 681, 51));
        lineEditchercherid_2 = new QLineEdit(tabsupprimer);
        lineEditchercherid_2->setObjectName("lineEditchercherid_2");
        lineEditchercherid_2->setGeometry(QRect(130, 90, 521, 41));
        label_26 = new QLabel(tabsupprimer);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(20, 90, 111, 31));
        label_26->setFont(font1);
        label_12 = new QLabel(tabsupprimer);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(700, 540, 101, 91));
        label_12->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/logo app1.png")));
        pushButtoannuler = new QPushButton(tabsupprimer);
        pushButtoannuler->setObjectName("pushButtoannuler");
        pushButtoannuler->setGeometry(QRect(80, 210, 651, 51));
        pushButtoannuler->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        tabWidget->addTab(tabsupprimer, icon6, QString());
        tabcalendrier = new QWidget();
        tabcalendrier->setObjectName("tabcalendrier");
        calendarWidget = new QCalendarWidget(tabcalendrier);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(10, 10, 341, 331));
        listEventsToday = new QListWidget(tabcalendrier);
        listEventsToday->setObjectName("listEventsToday");
        listEventsToday->setGeometry(QRect(390, 30, 381, 291));
        groupBoxEventDetails = new QGroupBox(tabcalendrier);
        groupBoxEventDetails->setObjectName("groupBoxEventDetails");
        groupBoxEventDetails->setGeometry(QRect(380, 340, 421, 271));
        label_44 = new QLabel(groupBoxEventDetails);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(10, 40, 61, 31));
        label_44->setFont(font1);
        label_44->setTextFormat(Qt::TextFormat::AutoText);
        eventDetailsNom = new QLineEdit(groupBoxEventDetails);
        eventDetailsNom->setObjectName("eventDetailsNom");
        eventDetailsNom->setGeometry(QRect(60, 40, 341, 31));
        label_45 = new QLabel(groupBoxEventDetails);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(10, 80, 61, 31));
        label_45->setFont(font1);
        label_46 = new QLabel(groupBoxEventDetails);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(10, 120, 61, 31));
        label_46->setFont(font1);
        label_71 = new QLabel(groupBoxEventDetails);
        label_71->setObjectName("label_71");
        label_71->setGeometry(QRect(10, 160, 51, 31));
        label_71->setFont(font1);
        eventDetailsDate = new QDateEdit(groupBoxEventDetails);
        eventDetailsDate->setObjectName("eventDetailsDate");
        eventDetailsDate->setGeometry(QRect(60, 80, 351, 31));
        eventDetailsDate->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        eventDetailsLieu = new QComboBox(groupBoxEventDetails);
        eventDetailsLieu->setObjectName("eventDetailsLieu");
        eventDetailsLieu->setGeometry(QRect(60, 120, 351, 31));
        eventDetailsLieu->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        eventDetailsType = new QComboBox(groupBoxEventDetails);
        eventDetailsType->setObjectName("eventDetailsType");
        eventDetailsType->setGeometry(QRect(60, 160, 351, 31));
        eventDetailsType->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        pushButtonEditEvent = new QPushButton(groupBoxEventDetails);
        pushButtonEditEvent->setObjectName("pushButtonEditEvent");
        pushButtonEditEvent->setGeometry(QRect(160, 210, 121, 41));
        pushButtonEditEvent->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        groupBoxPlanning = new QGroupBox(tabcalendrier);
        groupBoxPlanning->setObjectName("groupBoxPlanning");
        groupBoxPlanning->setGeometry(QRect(0, 340, 371, 281));
        label_72 = new QLabel(groupBoxPlanning);
        label_72->setObjectName("label_72");
        label_72->setGeometry(QRect(0, 20, 61, 31));
        label_72->setFont(font1);
        label_72->setTextFormat(Qt::TextFormat::AutoText);
        planNom = new QLineEdit(groupBoxPlanning);
        planNom->setObjectName("planNom");
        planNom->setGeometry(QRect(50, 20, 311, 31));
        label_73 = new QLabel(groupBoxPlanning);
        label_73->setObjectName("label_73");
        label_73->setGeometry(QRect(0, 60, 61, 31));
        label_73->setFont(font1);
        label_74 = new QLabel(groupBoxPlanning);
        label_74->setObjectName("label_74");
        label_74->setGeometry(QRect(0, 110, 61, 31));
        label_74->setFont(font1);
        label_75 = new QLabel(groupBoxPlanning);
        label_75->setObjectName("label_75");
        label_75->setGeometry(QRect(0, 160, 51, 31));
        label_75->setFont(font1);
        planLieu = new QComboBox(groupBoxPlanning);
        planLieu->setObjectName("planLieu");
        planLieu->setGeometry(QRect(50, 110, 311, 31));
        planLieu->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        planType = new QComboBox(groupBoxPlanning);
        planType->setObjectName("planType");
        planType->setGeometry(QRect(50, 160, 311, 31));
        planType->setStyleSheet(QString::fromUtf8("background-color: white !important;\n"
"border: 2px solid #FFB6C1 !important;\n"
"color: black;\n"
"padding: 5px;\n"
"border-radius: 3px;"));
        planDate = new QDateTimeEdit(groupBoxPlanning);
        planDate->setObjectName("planDate");
        planDate->setGeometry(QRect(50, 60, 311, 26));
        pushButtonvalider_5 = new QPushButton(groupBoxPlanning);
        pushButtonvalider_5->setObjectName("pushButtonvalider_5");
        pushButtonvalider_5->setGeometry(QRect(130, 210, 121, 41));
        pushButtonvalider_5->setStyleSheet(QString::fromUtf8("background-color: #f4c2c2;  /* Light pink */\n"
"color: white;               /* White text */\n"
"font-weight: bold;\n"
"border-radius: 5px;\n"
"padding: 5px 10px;\n"
"\n"
""));
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpenRecent));
        tabWidget->addTab(tabcalendrier, icon7, QString());
        tabstatistique = new QWidget();
        tabstatistique->setObjectName("tabstatistique");
        groupBox = new QGroupBox(tabstatistique);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 411, 591));
        label_total = new QLabel(groupBox);
        label_total->setObjectName("label_total");
        label_total->setGeometry(QRect(10, 50, 211, 31));
        label_mois = new QLabel(groupBox);
        label_mois->setObjectName("label_mois");
        label_mois->setGeometry(QRect(20, 110, 91, 31));
        label_annee = new QLabel(groupBox);
        label_annee->setObjectName("label_annee");
        label_annee->setGeometry(QRect(20, 170, 121, 31));
        labeltype = new QLabel(groupBox);
        labeltype->setObjectName("labeltype");
        labeltype->setGeometry(QRect(10, 230, 171, 31));
        tableWidget_types = new QTableWidget(groupBox);
        if (tableWidget_types->rowCount() < 4)
            tableWidget_types->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_types->setVerticalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_types->setVerticalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_types->setVerticalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_types->setVerticalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_types->setObjectName("tableWidget_types");
        tableWidget_types->setGeometry(QRect(20, 280, 381, 201));
        chartWidget = new QWidget(tabstatistique);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setGeometry(QRect(450, 70, 331, 421));
        QIcon icon8(QIcon::fromTheme(QIcon::ThemeIcon::FormatJustifyLeft));
        tabWidget->addTab(tabstatistique, icon8, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1196, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(5);


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
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Ajouter un evenement \342\200\253</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Lieu:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Budget:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Nombre de participants:", nullptr));
        pushButtonvalider->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        pushButtonannuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_13->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabajouter), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Afficher un evenement</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Chercher L'ID", nullptr));
        lineEditchercherid->setText(QString());
        pushButtonafficher->setText(QCoreApplication::translate("MainWindow", "afficher les informations", nullptr));
        label_10->setText(QString());
        pushButtonpdf->setText(QCoreApplication::translate("MainWindow", "export PDF", nullptr));
        pushButtontri->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabafficher), QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        textEdit_6->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Modifier les informations</span></p></body></html>", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Chercher L'ID", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        lineEdit_7->setText(QString());
        label_19->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "Romantique", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("MainWindow", "\303\211l\303\251gant", nullptr));
        comboBox_6->setItemText(2, QCoreApplication::translate("MainWindow", "Festif", nullptr));
        comboBox_6->setItemText(3, QCoreApplication::translate("MainWindow", "Soft/Doux", nullptr));

        label_21->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Lieu:", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("MainWindow", "New Item", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("MainWindow", "New Item", nullptr));
        comboBox_7->setItemText(2, QCoreApplication::translate("MainWindow", "New Item", nullptr));
        comboBox_7->setItemText(3, QCoreApplication::translate("MainWindow", "New Item", nullptr));
        comboBox_7->setItemText(4, QCoreApplication::translate("MainWindow", "New Item", nullptr));

        label_24->setText(QCoreApplication::translate("MainWindow", "Nombre de participants:", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Budget:", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Sauvegarder les changements", nullptr));
        label_11->setText(QString());
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Anuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabmodifier), QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButtonsupprimer->setText(QCoreApplication::translate("MainWindow", "supprimer ", nullptr));
        textEdit_5->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI','Arial','sans-serif'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI'; font-size:12pt; font-weight:700; color:#ff007f;\">Supprimer un evenement</span></p></body></html>", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Chercher L'ID", nullptr));
        label_12->setText(QString());
        pushButtoannuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabsupprimer), QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBoxEventDetails->setTitle(QCoreApplication::translate("MainWindow", "D\303\251tails de l'\303\251v\303\251nement", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "Lieu:", nullptr));
        label_71->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        pushButtonEditEvent->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        groupBoxPlanning->setTitle(QCoreApplication::translate("MainWindow", "Nouvel \303\251v\303\251nement", nullptr));
        label_72->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        label_73->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        label_74->setText(QCoreApplication::translate("MainWindow", "Lieu:", nullptr));
        label_75->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        pushButtonvalider_5->setText(QCoreApplication::translate("MainWindow", "planifier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabcalendrier), QCoreApplication::translate("MainWindow", "Calendrier", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "STAT", nullptr));
        label_total->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Total evenements:</span></p></body></html>", nullptr));
        label_mois->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; color:#c55d85;\">Ce mois:</span><span style=\" color:#c55d85;\"><br/></span></p></body></html>", nullptr));
        label_annee->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; color:#c55d85;\">Cette ann\303\251e:</span></p></body></html>", nullptr));
        labeltype->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Par type:</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_types->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Romantique", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_types->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\303\211l\303\251gant", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_types->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Festif", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_types->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Soft/Doux", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabstatistique), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
