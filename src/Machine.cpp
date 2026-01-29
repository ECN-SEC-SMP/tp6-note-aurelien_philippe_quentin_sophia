#include "../lib/Machine.hpp"
#include "../lib/Plateau.hpp"
#include "../lib/Case.hpp"
#include <iostream>
#include <vector>

using namespace std;

Machine::Machine() : Joueur("Machine", Couleur::Rouge) {}

std::pair<std::pair<int, int>, Cercle> Machine::deciderAction(Plateau& plateau) {
    // Implémentation de l'action de la machine
}

std::pair<Cercle, int> tester_taille(Case a, Case b, int deltaDeTaille) {
    int deltaObserve = -1;
    for (Cercle courant_a : a.getCercles()) {
        for (Cercle courant_b : b.getCercles()) {
            deltaObserve = static_cast<int>(courant_a.getTaille()) - static_cast<int>(courant_b.getTaille());
            if (deltaObserve == deltaDeTaille) {
                return {courant_a, deltaObserve};
            }
        }
    }
    return {Cercle(), -1};
}


Cercle tester_couleur_identique(Case a, Case b) {
    for (Cercle courant_a : a.getCercles()) {
        for (Cercle courant_b : b.getCercles()) {
            if (courant_a.getCouleur() == courant_b.getCouleur()) {
                return courant_a;
            }
        }
    }
    return Cercle();
}

std::pair<std::pair<int, int>, Cercle> Machine::testerMenaceImminente(const Plateau &plateau,
                               const std::vector<Joueur> &joueurs) {
    Cercle petit;
    Cercle moyen;
    Cercle grand;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Case courante = plateau.getCase(x,y);

            if (courante.getCercles().size() > 1) {
                Cercle petit = courante.getCercles()[0];
                Cercle moyen = courante.getCercles()[1];
                Cercle grand = courante.getCercles()[2];

                //Cas 1 : Empilement
                if (petit.getCouleur() == Couleur::Rouge || 
                    moyen.getCouleur() == Couleur::Rouge || 
                    grand.getCouleur() == Couleur::Rouge) {
                        break; // il y a un cercle de la machine
                }
                if (petit.getCouleur() == moyen.getCouleur()) {
                    return {{x, y}, grand};
                }   
                 if (moyen.getCouleur() == grand.getCouleur()) {
                    return {{x, y}, petit};
                }   
                if (petit.getCouleur() == grand.getCouleur()) {
                    return {{x, y}, moyen};
                }   

                //Cas 2 : Alignement de même taille
                if (x > 1) break;
                else {
                    for (int taille = 0; taille < 3; taille++) {
                        for (Cercle courant : courante.getCercles()) {
                            for (Cercle suivant_x_1 : plateau.getCase(x + 1, y).getCercles()) { // suivant en X + 1
                                if (courant == suivant_x_1) return {{x + 2, y}, courant};
                            }
                            for (Cercle suivant_x_2 : plateau.getCase(x + 2, y).getCercles()) { // suivant en X + 2
                                if (courant == suivant_x_2) return {{x + 1, y}, courant};
                            }
                            for (Cercle suivant_y_1 : plateau.getCase(x, y + 1).getCercles()) { // suivant en Y + 1
                                if (courant == suivant_y_1) return {{x, y + 2}, courant};
                            }
                            for (Cercle suivant_y_2 : plateau.getCase(x, y + 2).getCercles()) { // suivant en Y + 2
                                if (courant == suivant_y_2) return {{x, y + 1}, courant};
                            }
                            for (Cercle suivant_diagonal_1_D : plateau.getCase(x + 1, y + 1).getCercles()) { // suivant en diagonale droite + 1
                                if (courant == suivant_diagonal_1_D) return {{x + 2, y + 2}, courant};
                            }
                            for (Cercle suivant_diagonal_2_D : plateau.getCase(x + 2, y + 2).getCercles()) { // suivant en diagonale droite + 2
                                if (courant == suivant_diagonal_2_D) return {{x + 1, y + 1}, courant};
                            }
                            for (Cercle suivant_diagonal_1_G : plateau.getCase(x - 1, y - 1).getCercles()) { // suivant en diagonale gauche + 1
                                if (courant == suivant_diagonal_1_G) return {{x - 2, y - 2}, courant};
                            }
                            for (Cercle suivant_diagonal_2_G : plateau.getCase(x - 2, y - 2).getCercles()) { // suivant en diagonale gauche + 2
                                if (courant == suivant_diagonal_2_G) return {{x - 1, y - 1}, courant};
                            }
                        }
                    }
                }
            }
        }       
    }
    return {{-1, -1}, Cercle()};
}
