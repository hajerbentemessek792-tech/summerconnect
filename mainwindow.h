#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlEngine>

#include <QMessageBox>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQuickItem>

#include <QMap>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // CRUD
    void on_pushButton_ajouter_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_sauvegarder_clicked();
    void on_pushButton_chercher_clicked();
    void on_pushButton_rechercheNom_clicked();
    void on_pushButton_inscrire_clicked();
    void on_pushButtonpdf_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_verifier_clicked();

    // Statistiques
    void onActualiserStatsClicked();

    // Localisation
    void on_btn_localisation_clicked();

private:
    Ui::MainWindow *ui;

    // Gestion client
    Client tmpClient;
    QList<Client> clients;

    // Méthodes principales
    void checkAnniversaire();
    void chargerClientsDepuisSQL();

    // Statistiques
    QMap<QString, int> calculerStatsParAge();
    QMap<QString, int> calculerStatsOperations();
    void genererStatistiquesCRUD();

    // Export PDF
    void exportPDF(QSqlQueryModel *model);

    // Carte
    QQuickWidget *m_mapWidget;
    QNetworkAccessManager *networkManager;
};

#endif // MAINWINDOW_H
