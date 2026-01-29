#include "../lib/Machine.hpp"

Machine::Machine(const std::string& nom, Couleur couleur)
    : Joueur(nom, couleur) { }

std::string Machine::deciderAction(Plateau& p) {
    // TODO: Implémenter l'IA
    std::string action = "0 0 P"; // Action par défaut
    std::cout << "Action de " << getNom() << " (Machine): " << action << std::endl;
    return action;
}