/**
 * @file Case.cpp
 * @brief Implantation des méthodes de `Case`.
 */

#include "Case.hpp"
#include "Cercle.hpp"
#include <iostream>
#include <algorithm>

Case::Case() = default;

/**
 * @brief Vérifie qu'un cercle n'est pas déjà présent dans la case.
 *
 * @param[in] cercle Le `Cercle` recherché.
 * @return `true` si le cercle n'est pas présent (donc ajoutable),
 *         `false` si le cercle est déjà présent.
 */
bool Case::testerCercles(const Cercle& cercle){
    return (std::find(cercles.begin(), cercles.end(), cercle) == cercles.end());
}

/**
 * @brief Ajoute un cercle si celui-ci n'est pas déjà présent.
 *
 * @param[in] cercle Le cercle à ajouter.
 * @return `true` si l'ajout a réussi, `false` sinon.
 */
bool Case::ajouterCercle(const Cercle& cercle) {
    if (testerCercles(cercle)) {
        cercles.push_back(cercle);
        return true;
    }
    return false;
}
