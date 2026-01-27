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
 * @brief Tester si on peut poser un cercle.
 *
 * @param[in] cercle Le cercle à ajouter.
 * @return `true` si l'ajout est permis, `false` sinon.
 */
bool Case::testerCercles(const Cercle& cercle){
    for (Cercle currentCercle : getCercles()) {
        if (cercle.getTaille() == currentCercle.getTaille()) return false;
    }
    return true;
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
