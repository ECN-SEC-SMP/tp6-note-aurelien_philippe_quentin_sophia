#include "../lib/Joueur.hpp"

Joueur::Joueur(const std::string& nom, Couleur couleur)
    : nom(nom), couleur(couleur), petitCercle(3), moyenCercle(3), grandCercle(3) { }

void Joueur::retirerCercle(Taille taille) {
    switch (taille) {
        case Taille::Petit:
            if (petitCercle > 0) {      
                petitCercle--;
                return;
            }
            break;
        case Taille::Moyen:
            if (moyenCercle > 0) {
                moyenCercle--;
                return;
            }
            break;
        case Taille::Grand:
            if (grandCercle > 0) {
                grandCercle--;
                return ;
            }
            break;
    }
    std::cout<<"Aucun cercle de cette taille à retirer pour le joueur " << nom << "." << std::endl;
    return;
}

bool Joueur::aDesCercles() const {
    return (petitCercle > 0 || moyenCercle > 0 || grandCercle > 0);
}

std::pair<std::pair<int, int>, Cercle> Joueur::deciderAction(Plateau& plateau) {
    return {{-1, -1}, Cercle()};
}