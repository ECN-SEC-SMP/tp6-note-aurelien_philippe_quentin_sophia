#pragma once

#include "Cercle.hpp"
#include <vector>

/**
 * @file Case.hpp
 * @brief Déclaration de la classe Case qui contient des cercles.
 */

/**
 * @class Case
 * @brief Représente une case pouvant contenir plusieurs objets `Cercle`.
 *
 * La classe gère une collection de `Cercle` et permet d'ajouter
 * et de tester la présence d'un cercle.
 */
class Case {
private:
  std::vector<Cercle> cercles; /**< Conteneur des cercles dans la case */
public:
  /**
   * @brief Constructeur par défaut de `Case`.
   */
  Case();

  /**
   * @brief Teste si un `Cercle` est déjà présent dans la case.
   *
   * @param[in] cercle Le cercle à rechercher.
   * @return `true` si le cercle n'est pas présent (peut être ajouté),
   *         `false` s'il est déjà présent.
   */
  bool testerCercles(const Cercle &cercle);

  /**
   * @brief Ajoute un `Cercle` à la case si possible.
   *
   * @param[in] cercle Le cercle à ajouter.
   * @return `true` si l'ajout a réussi, `false` sinon.
   */
  bool ajouterCercle(const Cercle &cercle);

  std::vector<Cercle> getCercles() const { return this->cercles; };
};
