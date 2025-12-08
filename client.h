#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QMap>

class Client
{
private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QDate date_naissance; // date de naissance pour calculer l'âge

public:
    // Constructeurs
    Client();
    Client(int id, QString nom, QString prenom, QString email, QString telephone, QDate date_naissance);

    // Méthodes statistiques
    QMap<QString, int> statistiquesAge(); // calcule les stats par tranche d'âge

    // Getters
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getEmail() const;
    QString getTelephone() const;
    QDate getDateNaissance() const;

    // Setters
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setEmail(const QString &email);
    void setTelephone(const QString &telephone);
    void setDateNaissance(const QDate &date_naissance);

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel* afficherTri();
    QSqlQuery getAnniversairesDuJour();
    QString recommanderAtelier(int id);
    QSqlQueryModel* rechercherParNom(const QString &nom);
};

#endif // CLIENT_H
