/* #pragma once

#include <vector>
#include "Enums.h"
#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Humain.hpp" 

class Jeu {
    private :
        int version;
        std::vector<Joueur> joueurs;
        Plateau plateau;
        int joueurCourant;
    public :
        // Constructeur
        Jeu();

        // Accesseurs
        int getVersion();

        // Mutateurs

        // Méthodes
        void ajouterJoueurHumain(const std::string& nom, Couleur couleur);
        void ajouterJoueurMachine(const std::string& nom, Couleur couleur);
        void choisirVersion();
        int entrerNombreJoueurs();
        void entrerJoueurs();
        void initialiser(); 
        void lancerPartie();
        void lancerTourSuivant();
        bool testerVictoire();
        bool verifierFinDePartie();
}; */