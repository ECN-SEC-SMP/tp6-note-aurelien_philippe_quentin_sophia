/** 
 * @file Humain.hpp
 * @brief Définition de la classe Humain
 * @author Philippe
 * @date Janvier 2026
 */
#ifndef HUMAIN_HPP
#define HUMAIN_HPP

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Cercle.hpp"
#include "Enums.h"
#include <string>
#include <utility>

/** *@brief Classe représentant un joueur humain 
  */
class Humain : public Joueur {
public:
    /** *@brief Constructeur de la classe Humain 
      *  @param nom Le nom du joueur 
      *  @param couleur La couleur du joueur 
      */
    Humain(const std::string& nom, Couleur couleur);

    /** *@brief Décide de l'action du joueur humain 
      *  @param p Le plateau de jeu 
      *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer 
      */
    std::pair<std::pair<int, int>, Cercle> deciderAction(Plateau& p) override;
};

#endif // HUMAIN_HPP