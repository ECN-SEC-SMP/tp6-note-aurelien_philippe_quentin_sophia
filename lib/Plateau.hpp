#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "Case.hpp"
#include <iostream>

class Plateau {
private:
    //tableau  3x3 statique
    Case grille[3][3];

public:
    Plateau();
    
    // Méthode pour l'affichage ASCII
    void afficher();

    // Retourne true si la case peut accepter le cercle
    bool placerCercle(int x, int y, Cercle c);

    // Nécessaire pour que Jeu puisse tester la victoire
    // On retourne une référence constante (lecture seule) pour ne pas copier l'objet
    const Case& getCase(int x, int y) const;

    const Case (&getGrille() const)[3][3] {return grille;};
};

#endif