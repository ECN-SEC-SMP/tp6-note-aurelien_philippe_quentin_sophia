#pragma once

#include <list>
#include "Enums.h"
#include "Joueur.hpp"
#include "Plateau.hpp"

class Jeu {
    private :
        int version;
        std::list<Joueur> joueurs;
        Plateau plateau;
    public :
        // Constructeur
        Jeu();

        // Accesseurs
        void getVersion();

        // Mutateurs
        void setVersion(int version);

        // Méthodes
        void initialiser(); 
        void lancerPartie();
        void lancerTourSuivant();
        void demanderAction(Joueur joueur);
        bool testerVictoire(Couleur couleur);
        bool verifierFinDePartie();
};