#include "../lib/Humain.hpp"
#include <iostream>

Humain::Humain(const std::string& nom, Couleur couleur)
    : Joueur(nom, couleur) { }

std::pair<std::pair<int, int>, Cercle> Humain::deciderAction(Plateau& p) {
    std::cout   << "Action de " << getNom() << " (Humain).\n "
                << "Format : xy<taille> avec taille [1..3].\n"
                << "Ex : 111 -> petit cercle du milieu.Entrez votre action : "
                << std::endl;

    std::string saisieJoueur;
    std::getline(std::cin, saisieJoueur);
    
    std::pair<std::pair<int, int>, Cercle> action;
    if (saisieJoueur.length() != 3) {
        std::cout << "Format invalide. \n"
        << "Veuillez entrer une action au format xy<taille>." << std::endl;
        return deciderAction(p); // redemander l'action
    }

    if(saisieJoueur[0] < '0' || saisieJoueur[0] > '2' ||
       saisieJoueur[1] < '0' || saisieJoueur[1] > '2') {
        std::cout << "Coordonnées invalides. \n"
        << "Veuillez entrer des coordonnées valides (0, 1 ou 2)." << std::endl;
        return deciderAction(p); // redemander l'action
    }

    action.first.first = saisieJoueur[0] - '0';
    action.first.second = saisieJoueur[1] - '0';
    
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
        case '3' :// grand
        {
            action.second = Cercle(getCouleur(), Taille::Grand);
            break;
        }
        default :  // invalide
        {
            std::cout << "Taille invalide. \n"
            << "Veuillez entrer une taille valide (1, 2 ou 3)." << std::endl;
            return deciderAction(p); // redemander l'action
        }

    }

    return action;
}