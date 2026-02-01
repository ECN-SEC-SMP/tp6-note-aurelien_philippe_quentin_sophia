#include "../lib/Machine.hpp"
#include "../lib/Plateau.hpp"
#include "../lib/Case.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour time()

using namespace std;

// [AJOUT] 1. FONCTION DE VISION
// But : Permettre à la machine de vérifier si un plateau est gagnant pour elle
// Elle ne pouvait pas utiliser Jeu::verifierFinDePartie car elle n'a pas accès à Jeu
bool machineEstGagnante(const Plateau& p, Couleur c) {
    // 1. Otrio Concentrique
    for(int x=0; x<3; x++) {
        for(int y=0; y<3; y++) {
            const auto& contenu = p.getCase(x,y).getCercles();
            int compteur = 0;
            for(const auto& pion : contenu) {
                if(pion.getCouleur() == c) compteur++;
            }
            if(compteur == 3) return true;
        } 
    }

    // 2. Alignements
    int lignes[8][3][2] = {
        {{0,0}, {1,0}, {2,0}}, {{0,1}, {1,1}, {2,1}}, {{0,2}, {1,2}, {2,2}}, // Lignes
        {{0,0}, {0,1}, {0,2}}, {{1,0}, {1,1}, {1,2}}, {{2,0}, {2,1}, {2,2}}, // Cols
        {{0,0}, {1,1}, {2,2}}, {{2,0}, {1,1}, {0,2}}  // Diags
    };

    for(int i=0; i<8; i++) {
        const Case& c1 = p.getCase(lignes[i][0][0], lignes[i][0][1]);
        const Case& c2 = p.getCase(lignes[i][1][0], lignes[i][1][1]);
        const Case& c3 = p.getCase(lignes[i][2][0], lignes[i][2][1]);

        // Même Taille
        for(int t=0; t<3; t++) {
            Taille tail = static_cast<Taille>(t);
            bool b1=false, b2=false, b3=false;
            for(auto& k : c1.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b1=true;
            for(auto& k : c2.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b2=true;
            for(auto& k : c3.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b3=true;
            if(b1 && b2 && b3) return true;
        }

        // Croissant
        bool p1=false, m2=false, g3=false;
        for(auto& k : c1.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Petit) p1=true;
        for(auto& k : c2.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Moyen) m2=true;
        for(auto& k : c3.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Grand) g3=true;
        if(p1 && m2 && g3) return true;

        // Décroissant
        bool g1=false, m2b=false, p3=false;
        for(auto& k : c1.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Grand) g1=true;
        for(auto& k : c2.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Moyen) m2b=true;
        for(auto& k : c3.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Petit) p3=true;
        if(g1 && m2b && p3) return true;
    }
    return false;
}

Machine::Machine(const std::string& nom, Couleur couleur) 
    : Joueur(nom, couleur) {
    srand(time(NULL)); // Init random pour éviter de toujours faire la même partie
}

// [MODIFICATION MAJEURE] 2. DECIDER ACTION
// But : Intégrer l'Attaque avant la Défense
std::pair<std::pair<int, int>, Cercle> Machine::deciderAction(Plateau& plateau) {
    cout << "Machine " << getNom() << " reflechit..." << endl;

    // PRIORITÉ 1 : ATTAQUE (Simulation) 
    // On teste tous les coups. Si un coup gagne, on le joue
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int t = 0; t < 3; t++) {
                Taille taille = static_cast<Taille>(t);
                Cercle c(getCouleur(), taille);

                // Si le coup est possible physiquement
                if (plateau.getCase(x, y).testerCercles(c)) {
                    // Simulation : On copie le plateau
                    Plateau simu = plateau; 
                    simu.placerCercle(x, y, c);
                    
                    // Si ce coup me fait gagner
                    if (machineEstGagnante(simu, getCouleur())) {
                        cout << "-> Victoire calculee !" << endl;
                        return {{x, y}, c};
                    }
                }
            }
        }
    }

    // PRIORITÉ 2 : DÉFENSE 
    std::pair<std::pair<int, int>, Cercle> action = testerMenaceImminente(plateau);

    // Si une menace est détectée (coordonnées != -1)
    if (action.first.first != -1) {
        cout << "-> Menace detectee, blocage !" << endl;
        // IMPORTANT : On s'assure de jouer NOTRE couleur (pas Rouge par défaut)
        action.second = Cercle(getCouleur(), action.second.getTaille());
        return action;
    }

    // PRIORITÉ 3 : STRATEGIE (Centre)
    // [AJOUT] Essayer de prendre le centre (position forte) si rien d'autre à faire
    Cercle cGrand(getCouleur(), Taille::Grand);
    if (plateau.getCase(1, 1).testerCercles(cGrand)) {
         return {{1, 1}, cGrand};
    }

    // PRIORITÉ 4 : HASARD 
    // Sécurité anti-boucle infinie ajoutée (i < 100)
    for(int i=0; i<100; i++) {
        action.first.first = rand() % 3;
        action.first.second = rand() % 3;
        action.second = Cercle(getCouleur(), static_cast<Taille>(rand() % 3));
        
        // On vérifie que le coup hasard est valide avant de le renvoyer
        if (plateau.getCase(action.first.first, action.first.second).testerCercles(action.second)) {
            return action;
        }
    }
    return {{-1, -1}, Cercle()};
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

/* // V1 Abandonnée suite au refacroring 

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
} */

std::pair<std::pair<int, int>, Cercle> Machine::testerMenaceImminente(const Plateau &plateau) {
    
    // CAS 1 : Concentrique
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Case courante = plateau.getCase(x, y);
            const vector<Cercle>& cercles = courante.getCercles();
            
            if (cercles.size() == 2) {
                Cercle c1 = cercles[0];
                Cercle c2 = cercles[1];
                
                // [PETITE CORRECTION] : On vérifie que c'est pas NOUS (getCouleur()) au lieu de juste Rouge
                if (c1.getCouleur() == c2.getCouleur() && c1.getCouleur() != getCouleur()) {
                    bool aPetit = (c1.getTaille() == Taille::Petit || c2.getTaille() == Taille::Petit);
                    bool aMoyen = (c1.getTaille() == Taille::Moyen || c2.getTaille() == Taille::Moyen);
                    
                    Taille tailleManquante;
                    if (!aPetit) tailleManquante = Taille::Petit;
                    else if (!aMoyen) tailleManquante = Taille::Moyen;
                    else tailleManquante = Taille::Grand;
                    
                    return {{x, y}, Cercle(Couleur::Rouge, tailleManquante)};
                }
            }
        }
    }
    
    // CAS 2 et 3 : Alignements
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (auto& dir : directions) {
                int dx = dir[0];
                int dy = dir[1];
                
                int x2 = x + dx;
                int y2 = y + dy;
                int x3 = x + 2*dx;
                int y3 = y + 2*dy;
                
                if (x3 < 0 || x3 > 2 || y3 < 0 || y3 > 2) continue;
                
                Case c1 = plateau.getCase(x, y);
                Case c2 = plateau.getCase(x2, y2);
                Case c3 = plateau.getCase(x3, y3);
                
                std::pair<std::pair<int, int>, Cercle> menace;

                menace = testerAlignementTailleCroissante(c1, c2, c3, x, y, x2, y2, x3, y3);
                if (menace.first.first != -1) return menace;
                menace = testerAlignementMemeTaille(c1, c2, c3, x, y, x2, y2, x3, y3);
                if (menace.first.first != -1) return menace;

                menace = testerAlignementTailleCroissante(c1, c3, c2, x, y, x3, y3, x2, y2);
                if (menace.first.first != -1) return menace;
                menace = testerAlignementMemeTaille(c1, c3, c2, x, y, x3, y3, x2, y2);
                if (menace.first.first != -1) return menace;

                menace = testerAlignementTailleCroissante(c2, c3, c1, x2, y2, x3, y3, x, y);
                if (menace.first.first != -1) return menace;
                menace = testerAlignementMemeTaille(c2, c3, c1, x2, y2, x3, y3, x, y);
                if (menace.first.first != -1) return menace;
            }
        }
    }
    
    return {{-1, -1}, Cercle()};
}

std::pair<std::pair<int, int>, Cercle> Machine::testerAlignementTailleCroissante(
    const Case& c1, const Case& c2, const Case& c3,
    int x1, int y1, int x2, int y2, int x3, int y3) {
    
    for (const Cercle& cercle1 : c1.getCercles()) {
        for (const Cercle& cercle2 : c2.getCercles()) {
            if (cercle1.getCouleur() == cercle2.getCouleur() && 
                cercle1.getCouleur() != getCouleur()) { // [CORRECTION] Vs Machine
                
                int t1 = static_cast<int>(cercle1.getTaille());
                int t2 = static_cast<int>(cercle2.getTaille());
                
                if (t1 != t2) {
                    int t3 = 3 - (t1 + t2);
                    if (t3 >= 0 && t3 <= 2) {
                        Taille tailleManquante = static_cast<Taille>(t3);
                        bool occupe = false;
                        for (const Cercle& c : c3.getCercles()) {
                            if (c.getTaille() == tailleManquante) { occupe = true; break; }
                        }
                        if (!occupe) {
                            return {{x3, y3}, Cercle(Couleur::Rouge, tailleManquante)};
                        }
                    }
                }
            }
        }
    }
    return {{-1, -1}, Cercle()};
}

std::pair<std::pair<int, int>, Cercle> Machine::testerAlignementMemeTaille(
    const Case& c1, const Case& c2, const Case& c3,
    int x1, int y1, int x2, int y2, int x3, int y3) {
    
    for (const Cercle& cercle1 : c1.getCercles()) {
        for (const Cercle& cercle2 : c2.getCercles()) {
            if (cercle1.getCouleur() == cercle2.getCouleur() &&
                cercle1.getTaille() == cercle2.getTaille() &&
                cercle1.getCouleur() != getCouleur()) { // [CORRECTION] Vs Machine
                
                bool presente = false;
                for (const Cercle& c : c3.getCercles()) {
                    if (c.getTaille() == cercle1.getTaille()) {
                        presente = true;
                        break;
                    }
                }
                if (!presente) {
                    return {{x3, y3}, Cercle(Couleur::Rouge, cercle1.getTaille())};
                }
            }
        }
    }
    return {{-1, -1}, Cercle()};
}