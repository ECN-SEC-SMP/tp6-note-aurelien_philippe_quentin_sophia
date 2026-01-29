#include "Machine.hpp"

Machine::Machine(const std::string& nom, Couleur couleur) : Joueur(nom, couleur) {
}

std::string Machine::deciderAction(Plateau& p) {
    (void)p; // Suppress unused parameter warning
    // TODO: Implement AI logic
    return "";
}