#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qchartview.h"
#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Ajouter
    void on_pushButtonvalider_clicked();
    void on_pushButtonannuler_clicked();

    // Afficher
    void on_pushButtonafficher_clicked();
    void on_lineEditchercherid_textChanged(const QString &arg1);

    // Modifier
    void on_pushButton_13_clicked(); // Chercher
    void on_pushButton_14_clicked(); // Sauvegarder
    void on_pushButton_16_clicked(); // Annuler

    // Supprimer
    void on_pushButtonsupprimer_clicked();
    void on_pushButtoannuler_clicked();

    // Statistique
    void on_tabWidget_currentChanged(int index);


    void on_statButton_clicked(); // Ajouter cette ligne




private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QChartView *chartView; // Ajouter cette ligne

    void setupDatabase();
    void populateComboBoxes();
    void clearAjouterFields();
    void clearModifierFields();
    bool eventExists(int id);
    void showEventDetails(int id);
    // Pour les statistiques
    void setupStatistiquesUI();
    void calculerStatistiques();
    void updateStatistiques();
    void setupPieChart();
    void updatePieChart(); // Nouvelle méthode
    void showPieChart(); // Nouvelle méthode pour afficher le graphique





};

#endif // MAINWINDOW_H
