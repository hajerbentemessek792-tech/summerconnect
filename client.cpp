#include "client.h"
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

Client::Client() {}

Client::Client(int id, QString nom, QString prenom, QString email, QString telephone, QDate date_naissance)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->date_naissance = date_naissance;
}

// Getters
int Client::getId() const { return id; }
QString Client::getNom() const { return nom; }
QString Client::getPrenom() const { return prenom; }
QString Client::getEmail() const { return email; }
QString Client::getTelephone() const { return telephone; }
QDate Client::getDateNaissance() const { return date_naissance; }

// Setters
void Client::setNom(const QString &n) { nom = n; }
void Client::setPrenom(const QString &p) { prenom = p; }
void Client::setEmail(const QString &e) { email = e; }
void Client::setTelephone(const QString &t) { telephone = t; }
void Client::setDateNaissance(const QDate &d) { date_naissance = d; }

// Ajouter
bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (ID_CLIENTS, NOM, PRENOM, MAIL, NUM, DATE_NAISSANCE) "
                  "VALUES (:id, :nom, :prenom, :mail, :num, :date_naissance)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", email);
    query.bindValue(":num", telephone);
    query.bindValue(":date_naissance", date_naissance);

    bool res = query.exec();
    if (!res)
        qDebug() << "Erreur insertion client:" << query.lastError().text();
    return res;
}

// Afficher
QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    return model;
}

QSqlQueryModel* Client::afficherTri()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS ORDER BY DATE_NAISSANCE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    return model;
}

// Supprimer
bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE ID_CLIENTS = :id");
    query.bindValue(":id", id);
    bool res = query.exec();
    if (!res)
        qDebug() << "Erreur suppression:" << query.lastError().text();
    return res;
}

// Modifier
bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET NOM=:nom, PRENOM=:prenom, MAIL=:mail, "
                  "NUM=:num, DATE_NAISSANCE=:date_naissance WHERE ID_CLIENTS=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", email);
    query.bindValue(":num", telephone);
    query.bindValue(":date_naissance", date_naissance);

    bool res = query.exec();
    if (!res)
        qDebug() << "Erreur modification:" << query.lastError().text();
    return res;
}

// Rechercher par nom
QSqlQueryModel* Client::rechercherParNom(const QString &nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS WHERE NOM LIKE '" + nom + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    return model;
}

// Anniversaires
QSqlQuery Client::getAnniversairesDuJour()
{
    QSqlQuery query;
    query.prepare("SELECT ID_CLIENTS, NOM, PRENOM FROM CLIENTS "
                  "WHERE TO_CHAR(DATE_NAISSANCE, 'MM-DD') = TO_CHAR(SYSDATE, 'MM-DD')");
    query.exec();
    return query;
}

// Recommandation atelier
QString Client::recommanderAtelier(int id)
{
    QSqlQuery query;
    query.prepare("SELECT DATE_NAISSANCE, NOM, PRENOM FROM CLIENTS WHERE ID_CLIENTS = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        return "Erreur SQL : " + query.lastError().text();
    if (!query.next())
        return "Client inexistant !";

    QDate dateN = query.value(0).toDate();
    QString nom = query.value(1).toString();
    QString prenom = query.value(2).toString();

    if (!dateN.isValid())
        return "Date de naissance invalide !";

    int age = dateN.daysTo(QDate::currentDate()) / -365; // alternative plus simple : voir ci-dessous
    // meilleure approche :
    // int age = QDate::currentDate().year() - dateN.year();
    // if (QDate::currentDate() < QDate(QDate::currentDate().year(), dateN.month(), dateN.day()))
    //     age--;

    QString reco;
    if (age < 12)
        reco = "🎨 Ateliers créatifs enfants";
    else if (age <= 18)
        reco = "⚽ Événements sportifs jeunes";
    else if (age <= 30)
        reco = "🎧 Soirées DJ & Beach party";
    else if (age <= 50)
        reco = "🍳 Ateliers cuisine & bien-être";
    else
        reco = "🧘 Ateliers relaxants : art, méditation";

    return nom + " " + prenom + " (" + QString::number(age) + " ans)\n→ " + reco;
}

// Statistiques par âge
QMap<QString,int> Client::statistiquesAge()
{
    QMap<QString,int> stats;
    stats["Mineurs"] = 0;
    stats["Adultes"] = 0;
    stats["Seniors"] = 0;

    QSqlQuery q("SELECT DATE_NAISSANCE FROM CLIENTS");
    while (q.next()) {
        QDate d = q.value(0).toDate();
        if (!d.isValid()) continue;

        int age = QDate::currentDate().year() - d.year();
        if (QDate::currentDate() < QDate(QDate::currentDate().year(), d.month(), d.day()))
            age--;

        if (age < 18)
            stats["Mineurs"]++;
        else if (age <= 40)
            stats["Adultes"]++;
        else
            stats["Seniors"]++;
    }

    return stats;
}
