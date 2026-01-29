#include "../lib/Machine.hpp"

Machine::Machine(const std::string& nom, Couleur couleur)
    : Joueur(nom, couleur) { }

std::string Machine::deciderAction(Plateau& p) {
    // TODO: Implémenter une stratégie IA avancée (recherche de coups gagnants, blocage, etc.)
    std::string action = "0 0 P"; // Action par défaut pour le moment
    std::cout << "Action de " << getNom() << " (Machine): " << action << std::endl;
    return action;
}