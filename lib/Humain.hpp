#ifndef HUMAIN_HPP
#define HUMAIN_HPP

#include "Joueur.hpp"

class Humain : public Joueur {
public:
    Humain(const std::string& nom, Couleur couleur);

    void deciderAction() override;
};

#endif // HUMAIN_HPP