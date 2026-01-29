#ifndef HUMAIN_HPP
#define HUMAIN_HPP

#include "Joueur.hpp"

class Humain : public Joueur {
public:
    Humain(const std::string& nom, Couleur couleur);

    std::pair<std::pair<int, int>, Cercle> deciderAction(Plateau& p) override;
};

#endif // HUMAIN_HPP