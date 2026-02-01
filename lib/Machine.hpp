#pragma once

#include <utility>
#include <vector>

#include "Case.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"

class Machine : public Joueur {
public:
  Machine(const std::string& nom, Couleur couleur);

  std::pair<std::pair<int, int>, Cercle> testerMenaceImminente(const Plateau &plateau);

  std::pair<std::pair<int, int>, Cercle>  deciderAction(Plateau &plateau);

  std::pair<std::pair<int, int>, Cercle> testerAlignementTailleCroissante(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);
    
  std::pair<std::pair<int, int>, Cercle> testerAlignementMemeTaille(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);

  Taille analyserLigne(const Case& c1, const Case& c2, const Case& cible);
};
