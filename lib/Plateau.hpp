/** *
 * @file Plateau.hpp
 * @brief Définition de la classe Plateau
 * @author Aurelien, Philippe, Quentin, Sophia
 * @date Janvier 2026
 */
#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "Case.hpp"
#include <iostream>

class Plateau {
private:
    //tableau  3x3 statique
    /** @brief Grille de cases du plateau de jeu */
    Case grille[3][3];

public:
/** @brief Constructeur par défaut de Plateau */
    Plateau();
    
    // Méthode pour l'affichage ASCII
    /** @brief Affiche le plateau de jeu dans la console */
    void afficher();

    // Retourne true si la case peut accepter le cercle
    /** @brief Place un cercle sur le plateau aux coordonnées (x, y) si possible
     * @param x Coordonnée x (0 à 2)
     * @param y Coordonnée y (0 à 2)
     * @param c Le cercle à placer
     * @return true si le cercle a été placé avec succès, false sinon
     */
    bool placerCercle(int x, int y, Cercle c);

    // Nécessaire pour que Jeu puisse tester la victoire
    // On retourne une référence constante (lecture seule) pour ne pas copier l'objet
    /** @brief Retourne une référence constante sur la case aux coordonnées (x, y)
     * @param x Coordonnée x (0 à 2)
     * @param y Coordonnée y (0 à 2)
     * @return Référence constante sur la case demandée
     */
    const Case& getCase(int x, int y) const;

    /** @brief Retourne une référence constante sur la grille de cases
     * @return Référence constante sur la grille 3x3 de cases
     */
    const Case (&getGrille() const)[3][3] {return grille;};
};

#endif