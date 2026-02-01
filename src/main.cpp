#include "Jeu.hpp"
#include <iostream>

int main() {
    std::cout << "=== BIENVENUE DANS OTRIO ===" << std::endl;

    // 1. Création de l'instance du jeu
    Jeu partie;

    // 2. Initialisation (Création des joueurs, du plateau...) et lancement de la partie
    partie.initialiser();

    std::cout << "Merci d'avoir joue !" << std::endl;
    return 0;
}