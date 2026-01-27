#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include "Cercle.hpp"

enum class Couleur {
    ROUGE,
    VERT,
    BLEU,
    VIOLET
};

class Joueur {
protected:
    Couleur couleur;
    std::string nom;
    int petitCercle;
    int moyenCercle;
    int grandCercle;

public:
    Joueur(const std::string& nom, Couleur couleur);

    Cercle retirerCercle(Taille taille);
    bool aDesCercles() const;
    virtual void deciderAction() = 0;


    // Getters
    Couleur getCouleur() const;
    std::string getNom() const;
    int getPetitCercle() const;
    int getMoyenCercle() const;
    int getGrandCercle() const;

    // Setters
    void setCouleur(Couleur couleur);
    void setNom(const std::string& nom);     
    void setPetitCercle(int nombre);
    void setMoyenCercle(int nombre);
    void setGrandCercle(int nombre);   
};

#endif // JOUEUR_HPP