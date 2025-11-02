#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class Evenement
{
private:
    int id;
    QString nom;
    QDate date;
    QString lieu;
    QString type;
    int nbParticipants;
    double budget;

public:
    Evenement();
    Evenement(int, QString, QDate, QString, QString, int, double);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QDate getDate() const { return date; }
    QString getLieu() const { return lieu; }
    QString getType() const { return type; }
    int getNbParticipants() const { return nbParticipants; }
    double getBudget() const { return budget; }

    // Setters
    void setId(int i) { id = i; }
    void setNom(QString n) { nom = n; }
    void setDate(QDate d) { date = d; }
    void setLieu(QString l) { lieu = l; }
    void setType(QString t) { type = t; }
    void setNbParticipants(int n) { nbParticipants = n; }
    void setBudget(double b) { budget = b; }

    // CRUD COMPLET
    bool ajouter();
    static QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);

    // Méthode pour rechercher par ID
    static Evenement rechercherParId(int id);
};

#endif // EVENEMENT_H
