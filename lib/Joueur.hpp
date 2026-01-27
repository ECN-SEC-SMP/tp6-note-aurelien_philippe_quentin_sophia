#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <iostream> 
#include "Cercle.hpp"
#include "Enums.h"
#include "Plateau.hpp"

class Joueur {
private:
    Couleur couleur;
    std::string nom;
    int petitCercle;
    int moyenCercle;
    int grandCercle;

public:
    Joueur(const std::string& nom, Couleur couleur);

    void retirerCercle(Taille taille);
    bool aDesCercles() const;
    virtual std::string deciderAction(Plateau& p) = 0;


    // Getters
    Couleur getCouleur() const {
        return couleur;
    }
    
    std::string getNom() const {
        return nom;
    }
    
    int getPetitCercle() const {
        return petitCercle;
    }
    
    int getMoyenCercle() const {
        return moyenCercle;
    }
    
    int getGrandCercle() const {
        return grandCercle;
    }

    // Setters
    void setCouleur(Couleur nouvelleCouleur) {
        couleur = nouvelleCouleur;
    }
    
    void setNom(const std::string& nouveauNom) {
        nom = nouveauNom;
    }
    
    void setPetitCercle(int nombre) {
        if (nombre >= 0) petitCercle = nombre;
    }
    
    void setMoyenCercle(int nombre) {
        if (nombre >= 0) moyenCercle = nombre;
    }
    
    void setGrandCercle(int nombre) {
        if (nombre >= 0) grandCercle = nombre;
    }
};

#endif // JOUEUR_HPP