#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qchartview.h"
#include "qlistwidget.h"
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
    void on_statButton_clicked();

    // Calendrier
    void on_calendarWidget_clicked(const QDate &date);
    void on_listEventsToday_itemClicked(QListWidgetItem *item);
    void on_pushButtonEditEvent_clicked();
    void on_calendarWidget_selectionChanged();
    void on_calendarWidget_2_clicked(const QDate &date);
    void on_calendarWidget_2_selectionChanged();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QChartView *chartView;

    void setupDatabase();
    void populateComboBoxes();
    void clearAjouterFields();
    void clearModifierFields();
    bool eventExists(int id);
    void showEventDetails(int id);

    void loadEventsForDate(const QDate &date);
    bool checkEventConflict(const QDate &date, const QString &lieu);
    void populateCalendarEvents();
    void updateCalendarDisplay(const QDate &date);
    void calculerStatistiquesPourDate(const QDate &date); // UNE SEULE DÉCLARATION
    void afficherConseilsSaisonniers(const QDate &date);

    // Pour les statistiques
    void setupStatistiquesUI();
    void calculerStatistiques();
    void updateStatistiques();
    void updatePieChart();
};

#endif // MAINWINDOW_H
