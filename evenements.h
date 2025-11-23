#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include <string>
using namespace std;

class Evenement {
private:
    int id_evenement;
    string nom;
    string date;
    string lieu;
    string type;
    int nb_participants;
    double budget;

public:
    // Constructeurs
    Evenement();
    Evenement(int id, string n, string d, string l, string t, int nb, double b);

    // Getters
    int getId() const;
    string getNom() const;
    string getDate() const;
    string getLieu() const;
    string getType() const;
    int getNbParticipants() const;
    double getBudget() const;

    // Setters
    void setId(int id);
    void setNom(string n);
    void setDate(string d);
    void setLieu(string l);
    void setType(string t);
    void setNbParticipants(int nb);
    void setBudget(double b);

    // Méthode d'affichage
    void afficher() const;
};

#endif // EVENEMENTS_H
