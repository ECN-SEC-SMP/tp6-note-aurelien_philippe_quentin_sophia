#pragma once

#include <utility>
#include <vector>

#include "Case.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"

class Machine : public Joueur {
public:
  Machine();

  std::pair<std::pair<int, int>, Cercle> testerMenaceImminente(const Plateau &plateau, const std::vector<Joueur> &joueurs);

  std::pair<std::pair<int, int>, Cercle>  deciderAction(Plateau &plateau);
};
