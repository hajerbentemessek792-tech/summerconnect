#include "connection.h"
#include <QMessageBox>
#include <QDebug>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;


    qDebug() << "Drivers disponibles:" << QSqlDatabase::drivers();


    if (!QSqlDatabase::isDriverAvailable("QODBC")) {
        QMessageBox::critical(nullptr, "Erreur Driver",
                              "Driver QODBC non disponible.\n"
                              "Assurez-vous que les drivers ODBC sont installés.");
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet");
    db.setUserName("sarra");
    db.setPassword("sarrasarra");

    if (db.open()) {
        test = true;
        qDebug() << "Connexion réussie à la base de données";
    } else {
        qDebug() << "Erreur de connexion:" << db.lastError().text();
    }

    return test;
}
//
