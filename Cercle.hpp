#pragma once

#include "Enums.h"

class Cercle {
public:
    Cercle() = default;
    Cercle(Couleur c, Taille t) : couleur(c), taille(t) {}

    Couleur getCouleur() const { return couleur; }
    Taille getTaille() const { return taille; }

private:
    Couleur couleur{Couleur::Rouge};
    Taille taille{Taille::Moyen};
};
