#include "connexion.h"
#include <QDebug>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_projet2A"); // Nom de la source ODBC (DSN)
    db.setUserName("hajer");
    db.setPassword("esprit18");

    qDebug() << "Connexion à la base de données en cours...";

    if (db.open()) {
        test = true;
        qDebug() << "Connexion réussie.";
    } else {
        qDebug() << "Erreur : " << db.lastError().text();
    }

    return test;
}
