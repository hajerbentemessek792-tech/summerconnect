#include "Evenement.h"

Evenement::Evenement() {}

Evenement::Evenement(int id, QString nom, QDate date, QString lieu, QString type, int nbParticipants, double budget)
    : id(id), nom(nom), date(date), lieu(lieu), type(type), nbParticipants(nbParticipants), budget(budget) {}

// CREATE - Ajouter
bool Evenement::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO EVENEMENT (ID_EVENEMENTS, NOM, DATE_EVENEMENT, LIEU, TYPE, NB_PARTICIPANTS, BUDGET) "
                  "VALUES (:id, :nom, :date_evenement, :lieu, :type, :nb_participants, :budget)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":date_evenement", date);
    query.bindValue(":lieu", lieu);
    query.bindValue(":type", type);
    query.bindValue(":nb_participants", nbParticipants);
    query.bindValue(":budget", budget);

    return query.exec();
}

// READ - Afficher
QSqlQueryModel* Evenement::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENEMENTS, NOM, DATE_EVENEMENT, LIEU, TYPE, NB_PARTICIPANTS, BUDGET FROM EVENEMENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Participants"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Budget"));

    return model;
}

// UPDATE - Modifier
bool Evenement::modifier(int id)
{
    QSqlQuery query;

    query.prepare("UPDATE EVENEMENT SET "
                  "NOM = :nom, "
                  "DATE_EVENEMENT = :date_evenement, "
                  "LIEU = :lieu, "
                  "TYPE = :type, "
                  "NB_PARTICIPANTS = :nb_participants, "
                  "BUDGET = :budget "
                  "WHERE ID_EVENEMENTS = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":date_evenement", date);
    query.bindValue(":lieu", lieu);
    query.bindValue(":type", type);
    query.bindValue(":nb_participants", nbParticipants);
    query.bindValue(":budget", budget);

    return query.exec();
}

// DELETE - Supprimer
bool Evenement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EVENEMENT WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", id);
    return query.exec();
}

// Rechercher par ID
Evenement Evenement::rechercherParId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EVENEMENT WHERE ID_EVENEMENTS = :id");
    query.bindValue(":id", id);

    Evenement e;

    if (query.exec() && query.next()) {
        e.setId(query.value(0).toInt());
        e.setNom(query.value(1).toString());
        e.setDate(query.value(2).toDate());
        e.setLieu(query.value(3).toString());
        e.setType(query.value(4).toString());
        e.setNbParticipants(query.value(5).toInt());
        e.setBudget(query.value(6).toDouble());
    }

    return e;
}
