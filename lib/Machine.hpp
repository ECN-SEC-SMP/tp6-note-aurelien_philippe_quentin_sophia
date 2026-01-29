#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "Joueur.hpp"

class Machine : public Joueur {
public:
    Machine(const std::string& nom, Couleur couleur);

    std::string deciderAction(Plateau& p) override;
};

#endif // MACHINE_HPP