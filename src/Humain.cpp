#include "../lib/Humain.hpp"
#include <iostream>

Humain::Humain(const std::string& nom, Couleur couleur)
    : Joueur(nom, couleur) { }

std::pair<std::pair<int, int>, Cercle> Humain::deciderAction(Plateau& p) {
    std::cout << "Action de " << getNom() << " (Humain). Format : .Entrez votre action : ";
    std::string saisieJoueur;
    std::getline(std::cin, saisieJoueur);
    
    std::pair<std::pair<int, int>, Cercle> action;
    action.first.first = saisieJoueur[0];
    action.first.second = saisieJoueur[1];
    
    switch (saisieJoueur[2]) {
        case '1' :// petit
        {
            action.second = Cercle(getCouleur(), Taille::Petit);
            break;
        }
        case '2' :// moyen
        {
            action.second = Cercle(getCouleur(), Taille::Moyen);
            break;
        }
        default :  // Grand
            action.second = Cercle(getCouleur(), Taille::Grand);
    }

    return action;
}