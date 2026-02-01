#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Case.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"

class Machine : public Joueur {
public:
  Machine(const std::string& nom, Couleur couleur);

  // Méthode principale
  std::pair<std::pair<int, int>, Cercle> deciderAction(Plateau &plateau) override;

  // Méthode de défense
  std::pair<std::pair<int, int>, Cercle> testerMenaceImminente(const Plateau &plateau);

  // Méthodes de Pattern Matching 
  std::pair<std::pair<int, int>, Cercle> testerAlignementTailleCroissante(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);
    
  std::pair<std::pair<int, int>, Cercle> testerAlignementMemeTaille(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);

  Taille analyserLigne(const Case& c1, const Case& c2, const Case& cible);

private:
  // Aide pour l'attaque en simulatioj
  bool estGagnant(const Plateau& p, Couleur c);
};