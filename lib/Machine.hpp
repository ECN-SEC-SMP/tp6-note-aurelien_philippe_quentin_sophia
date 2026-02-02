/** *
 * @file Machine.hpp
 * @brief Définition de la classe Machine
 * @author Aurelien, Philippe, Quentin, Sophia
 * @date Janvier 2026
 */
#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Case.hpp"
#include "Joueur.hpp"
#include "Plateau.hpp"

/** *@brief Classe représentant un joueur machine 
  */
class Machine : public Joueur {
public:
/** *@brief Constructeur de la classe Machine 
  *  @param nom Le nom du joueur 
  *  @param couleur La couleur du joueur 
  */
  Machine(const std::string& nom, Couleur couleur);

  // Méthode principale
  /** *@brief Décide de l'action de la machine 
    *  @param plateau Le plateau de jeu 
    *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer 
    */
  std::pair<std::pair<int, int>, Cercle> deciderAction(Plateau &plateau) override;

  // Méthode de défense
  /** *@brief Teste si un adversaire est sur le point de gagner 
    *  @param plateau Le plateau de jeu 
    *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer pour bloquer l'adversaire 
    */
  std::pair<std::pair<int, int>, Cercle> testerMenaceImminente(const Plateau &plateau);

  // Méthodes de Pattern Matching 
  /** *@brief Teste un alignement de cercles de tailles croissantes 
    *  @param c1 Première case 
    *  @param c2 Deuxième case 
    *  @param c3 Troisième case 
    *  @param x1 Coordonnée x de la première case 
    *  @param y1 Coordonnée y de la première case 
    *  @param x2 Coordonnée x de la deuxième case 
    *  @param y2 Coordonnée y de la deuxième case 
    *  @param x3 Coordonnée x de la troisième case 
    *  @param y3 Coordonnée y de la troisième case 
    *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer pour bloquer l'adversaire 
    */
  std::pair<std::pair<int, int>, Cercle> testerAlignementTailleCroissante(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);
    
  /** *@brief Teste un alignement de cercles de même taille 
    *  @param c1 Première case 
    *  @param c2 Deuxième case 
    *  @param c3 Troisième case 
    *  @param x1 Coordonnée x de la première case 
    *  @param y1 Coordonnée y de la première case 
    *  @param x2 Coordonnée x de la deuxième case 
    *  @param y2 Coordonnée y de la deuxième case 
    *  @param x3 Coordonnée x de la troisième case 
    *  @param y3 Coordonnée y de la troisième case 
    *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer pour bloquer l'adversaire 
    */  
  std::pair<std::pair<int, int>, Cercle> testerAlignementMemeTaille(
        const Case& c1, const Case& c2, const Case& c3,
        int x1, int y1, int x2, int y2, int x3, int y3);

  /** *@brief Analyse une ligne de trois cases pour détecter une menace 
    *  @param c1 Première case 
    *  @param c2 Deuxième case 
    *  @param cible Case cible où placer le cercle 
    *  @return La taille du cercle à placer pour bloquer l'adversaire, ou Taille::Aucun si pas de menace 
    */  
  Taille analyserLigne(const Case& c1, const Case& c2, const Case& cible);

private:
  // Aide pour l'attaque en simulation
  /** *@brief Vérifie si la couleur donnée a gagné sur le plateau 
    *  @param p Le plateau de jeu 
    *  @param c La couleur du joueur 
    *  @return true si le joueur a gagné, false sinon 
    */
  bool estGagnant(const Plateau& p, Couleur c);
};