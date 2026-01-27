#include "Plateau.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Plateau::Plateau() {
}

bool Plateau::placerCercle(int x, int y, Cercle c) {
    // Sécurité : Vérification des bornes
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Erreur : Coordonnées (" << x << "," << y << ") hors du plateau !" << endl;
        return false;
    }
    const vector<Cercle>& contenu = grille[x][y].getCercles();
    for (const auto& existant : contenu) {
        // Utilisation du getter car 'taille' est privé dans Cercle.hpp
        if (existant.getTaille() == c.getTaille()) {
            cout << "Mouvement impossible : Un cercle de cette taille est déjà présent." << endl;
            return false;
        }
    }

    // Si la taille est libre, on délègue l'ajout à la Case
    // Cette méthode fera le push_back.
    return grille[x][y].ajouterCercle(c);
}

const Case& Plateau::getCase(int x, int y) const {
    // Retourne la case en lecture seule pour que Jeu puisse tester la victoire
    return grille[x][y];
}

void Plateau::afficher() {
    cout << "\n     0             1             2" << endl;
    cout << "  +-------------+-------------+-------------+" << endl;

    for (int y = 0; y < 3; y++) {
        cout << y << " | ";
        
        for (int x = 0; x < 3; x++) {
            
            // Représentation visuelle par défaut
            char petit = '.';
            char moyen = '.';
            char grand = '.';

            // Récupération des cercles pour l'affichage
            const vector<Cercle>& contenu = grille[x][y].getCercles();

            for (const auto& c : contenu) {
                char l = '?';
                
                // Utilisation du getter getCouleur()
                switch (c.getCouleur()) {
                    case Couleur::Rouge: l = 'R'; break;
                    case Couleur::Vert:  l = 'V'; break;
                    case Couleur::Bleu:  l = 'B'; break;
                    case Couleur::Jaune: l = 'J'; break;
                    default: l = '?';
                }

                // Utilisation du getter getTaille()
                if (c.getTaille() == Taille::Petit) petit = l;
                else if (c.getTaille() == Taille::Moyen) moyen = l;
                else if (c.getTaille() == Taille::Grand) grand = l;
            }
            cout << "[" << petit << " " << moyen << " " << grand << "] | ";
        }
        cout << endl;
        cout << "  +-------------+-------------+-------------+" << endl;
    }
}