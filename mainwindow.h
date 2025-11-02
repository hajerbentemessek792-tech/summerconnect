#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;

    void setupDatabase();
    void populateComboBoxes();
    void clearAjouterFields();
    void clearModifierFields();
    bool eventExists(int id);
    void showEventDetails(int id);
};

#endif // MAINWINDOW_H
