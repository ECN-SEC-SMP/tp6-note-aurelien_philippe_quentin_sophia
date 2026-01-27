/**
 * @file Cercle.cpp
 * @brief Implémentation de la classe Cercle.
 */

#include "Cercle.hpp"
#include <iostream>
#include <string>

/**
 * @brief Convertit une couleur en chaîne de caractères.
 * @param couleur La couleur à convertir.
 * @return La chaîne de caractères représentant la couleur.
 */
static std::string couleurToString(Couleur couleur) {
    switch (couleur) {
        case Couleur::Rouge:
            return "Rouge";
        case Couleur::Vert:
            return "Vert";
        case Couleur::Bleu:
            return "Bleu";
        case Couleur::Jaune:
            return "Jaune";
        default:
            return "Inconnue";
    }
}

/**
 * @brief Convertit une taille en chaîne de caractères.
 * @param taille La taille à convertir.
 * @return La chaîne de caractères représentant la taille.
 */
static std::string tailleToString(Taille taille) {
    switch (taille) {
        case Taille::Petit:
            return "Petit";
        case Taille::Moyen:
            return "Moyen";
        case Taille::Grand:
            return "Grand";
        default:
            return "Inconnue";
    }
}

/**
 * @brief Affiche les caractéristiques du cercle.
 */
void Cercle::afficher() const {
    std::cout << "Cercle: " << couleurToString(couleur) << " "
              << tailleToString(taille) << std::endl;
}
