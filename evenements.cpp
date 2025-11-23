#include "evenements.h"
#include <iostream>
using namespace std;

// Constructeurs
Evenement::Evenement()
    : id_evenement(0), nom(""), date(""), lieu(""), type(""), nb_participants(0), budget(0.0) {}

Evenement::Evenement(int id, string n, string d, string l, string t, int nb, double b)
    : id_evenement(id), nom(n), date(d), lieu(l), type(t), nb_participants(nb), budget(b) {}

// Getters
int Evenement::getId() const { return id_evenement; }
string Evenement::getNom() const { return nom; }
string Evenement::getDate() const { return date; }
string Evenement::getLieu() const { return lieu; }
string Evenement::getType() const { return type; }
int Evenement::getNbParticipants() const { return nb_participants; }
double Evenement::getBudget() const { return budget; }

// Setters
void Evenement::setId(int id) { id_evenement = id; }
void Evenement::setNom(string n) { nom = n; }
void Evenement::setDate(string d) { date = d; }
void Evenement::setLieu(string l) { lieu = l; }
void Evenement::setType(string t) { type = t; }
void Evenement::setNbParticipants(int nb) { nb_participants = nb; }
void Evenement::setBudget(double b) { budget = b; }

// Méthode d'affichage
void Evenement::afficher() const {
    cout << "ID: " << id_evenement << endl;
    cout << "Nom: " << nom << endl;
    cout << "Date: " << date << endl;
    cout << "Lieu: " << lieu << endl;
    cout << "Type: " << type << endl;
    cout << "Participants: " << nb_participants << endl;
    cout << "Budget: " << budget << " €" << endl;
}
