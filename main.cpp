#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();

    if (!test) {
        QMessageBox::critical(nullptr, "Échec de connexion",
                              "Impossible de se connecter à la base de données.");
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
