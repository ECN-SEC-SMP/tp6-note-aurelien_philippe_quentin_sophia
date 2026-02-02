#pragma once

#include "Enums.h"

/**
 * @file Cercle.hpp
 * @brief Définition de la classe `Cercle` utilisée dans le projet.
 */

/**
 * @class Cercle
 * @brief Caractérisé par une couleur et une taille.
 */
class Cercle {
    private:
        Couleur couleur{Couleur::Rouge}; /**< Couleur par défaut */
        Taille taille{Taille::Moyen};    /**< Taille par défaut */
        
    public:
        /**
         * @brief Constructeur par défaut.
         */
        Cercle() = default;

        /**
         * @brief Constructeur avec paramètres.
         *
         * @param[in] c Couleur du cercle.
         * @param[in] t Taille du cercle.
         */
        Cercle(Couleur c, Taille t) : couleur(c), taille(t) {}

        /**
         * @brief Obtient la couleur du cercle.
         * @return La `Couleur` du cercle.
         */
        Couleur getCouleur() const { return couleur; }

        /**
         * @brief Obtient la taille du cercle.
         * @return La `Taille` du cercle.
         */
        Taille getTaille() const { return taille; }

        /**
         * @brief Opérateur d'égalité.
         * @param other Le cercle à comparer.
         * @return `true` si les deux cercles ont la même couleur et taille.
         */
        bool operator==(const Cercle& other) const {
            return couleur == other.couleur && taille == other.taille;
        }

        /**
         * @brief Affiche les caractéristiques du cercle.
         */
        void afficher() const;

};
