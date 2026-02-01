/** *@file Joueur.hpp
  *  @brief Définition de la classe Joueur
  *  @author Philippe
  *  @date Janvier 2026
  */

#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <iostream> 
#include "Cercle.hpp"
#include "Enums.h"
#include "Plateau.hpp"

/** *@brief Classe représentant un joueur dans le jeu 
  */
class Joueur {
protected:
    // Attributs
    Couleur couleur;
    std::string nom;
    int petitCercle;
    int moyenCercle;
    int grandCercle;

public:
    /** *@brief Constructeur de la classe Joueur 
      *  @param nom Le nom du joueur 
      *  @param couleur La couleur du joueur 
      */
    Joueur(const std::string& nom, Couleur couleur);
    virtual ~Joueur() = default;

    /** *@brief Retire un cercle du joueur en fonction de la taille 
      *  @param taille La taille du cercle à retirer 
      */
    void retirerCercle(Taille taille);

    /** *@brief Vérifie si le joueur a des cercles restants 
      *  @return true si le joueur a au moins un cercle restant, false sinon 
      */
    bool aDesCercles() const;

    /** *@brief Décide de l'action du joueur 
      *  @param p Le plateau de jeu 
      *  @return Une paire contenant les coordonnées (x, y) et le cercle à placer 
      */
    virtual std::pair<std::pair<int, int>, Cercle> deciderAction(Plateau& p);

    // Getters
    Couleur getCouleur() const { return couleur; }
    std::string getNom() const { return nom; }
    int getPetitCercle() const { return petitCercle; }
    int getMoyenCercle() const { return moyenCercle; }
    int getGrandCercle() const { return grandCercle; }

    // Setters
    void setCouleur(Couleur nouvelleCouleur) { couleur = nouvelleCouleur; }
    void setNom(const std::string& nouveauNom) { nom = nouveauNom; }
    void setPetitCercle(int nombre) { if (nombre >= 0) petitCercle = nombre; }
    void setMoyenCercle(int nombre) { if (nombre >= 0) moyenCercle = nombre; }
    void setGrandCercle(int nombre) { if (nombre >= 0) grandCercle = nombre; }
};

#endif // JOUEUR_HPP