#include "../lib/Humain.hpp"

Humain::Humain(const std::string& nom, Couleur couleur)
    : Joueur(nom, couleur) { }

std::string Humain::deciderAction(Plateau& p) {
    std::string action;
    std::cout << "Action de " << getNom() << " (Humain). Format : .Entrez votre action : ";
    std::getline(std::cin, action);
    return action;
}