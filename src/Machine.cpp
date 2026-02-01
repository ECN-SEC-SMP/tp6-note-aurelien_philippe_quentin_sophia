#include "../lib/Machine.hpp"
#include "../lib/Plateau.hpp"
#include "../lib/Case.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour time()

using namespace std;

// [AJOUT] FONCTION DE VISION (Simulation)
// Permet à la machine de vérifier si elle gagne sur une copie du plateau
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
        {{0,0}, {0,1}, {0,2}}, {{1,0}, {1,1}, {1,2}}, {{2,0}, {2,1}, {2,2}}, // Colonnes
        {{0,0}, {1,1}, {2,2}}, {{2,0}, {1,1}, {0,2}}  // Diagonales
    };

    for(int i=0; i<8; i++) {
        const Case& c1 = p.getCase(lignes[i][0][0], lignes[i][0][1]);
        const Case& c2 = p.getCase(lignes[i][1][0], lignes[i][1][1]);
        const Case& c3 = p.getCase(lignes[i][2][0], lignes[i][2][1]);

        // A. Même Taille
        for(int t=0; t<3; t++) {
            Taille tail = static_cast<Taille>(t);
            bool b1=false, b2=false, b3=false;
            for(auto& k : c1.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b1=true;
            for(auto& k : c2.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b2=true;
            for(auto& k : c3.getCercles()) if(k.getCouleur()==c && k.getTaille()==tail) b3=true;
            if(b1 && b2 && b3) return true;
        }

        // B. Croissant
        bool p1=false, m2=false, g3=false;
        for(auto& k : c1.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Petit) p1=true;
        for(auto& k : c2.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Moyen) m2=true;
        for(auto& k : c3.getCercles()) if(k.getCouleur()==c && k.getTaille()==Taille::Grand) g3=true;
        if(p1 && m2 && g3) return true;

        // C. Décroissant
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
    srand(time(NULL));
}

// CERVEAU DE LA MACHINE
std::pair<std::pair<int, int>, Cercle> Machine::deciderAction(Plateau& plateau) {

    // --- PRIORITÉ 1 : ATTAQUE ---
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int t = 0; t < 3; t++) {
                Taille taille = static_cast<Taille>(t);

                bool stockDispo = false;
                if (taille == Taille::Petit && petitCercle > 0) stockDispo = true;
                else if (taille == Taille::Moyen && moyenCercle > 0) stockDispo = true;
                else if (taille == Taille::Grand && grandCercle > 0) stockDispo = true;

                if (!stockDispo) continue;

                Cercle c(getCouleur(), taille);

                if (plateau.getCase(x, y).testerCercles(c)) {
                    // Simulation
                    Plateau simu = plateau; 
                    simu.placerCercle(x, y, c);
                    
                    if (machineEstGagnante(simu, getCouleur())) {
                        cout << "-> Victoire calculee !" << endl;
                        return {{x, y}, c};
                    }
                }
            }
        }
    }

    // --- PRIORITÉ 2 : DÉFENSE ---
    std::pair<std::pair<int, int>, Cercle> actionDefense = testerMenaceImminente(plateau);

    if (actionDefense.first.first != -1) {
        // [CRUCIAL] Vérifier qu'on a la pièce pour bloquer
        Taille tBlocage = actionDefense.second.getTaille();
        bool stockDispo = false;
        if (tBlocage == Taille::Petit && petitCercle > 0) stockDispo = true;
        else if (tBlocage == Taille::Moyen && moyenCercle > 0) stockDispo = true;
        else if (tBlocage == Taille::Grand && grandCercle > 0) stockDispo = true;

        if (stockDispo) {
            cout << "-> Menace detectee, blocage !" << endl;
            actionDefense.second = Cercle(getCouleur(), tBlocage);
            return actionDefense;
        }
        // Si pas de stock pour bloquer, on continue vers la stratégie
    }

    // --- PRIORITÉ 3 : STRATÉGIE (Centre) ---
    if (grandCercle > 0) { // On vérifie qu'on a un grand cercle !
    Cercle cGrand(getCouleur(), Taille::Grand);
    if (plateau.getCase(1, 1).testerCercles(cGrand)) {
        return {{1, 1}, cGrand};
    }
    }

    // --- PRIORITÉ 4 : HASARD SÉCURISÉ ---
    for(int i=0; i<500; i++) {
        int rx = rand() % 3;
        int ry = rand() % 3;
        int rt_int = rand() % 3;
        Taille rt = static_cast<Taille>(rt_int);
        
        // [CRUCIAL] Vérif Stock
        if (rt == Taille::Petit && petitCercle <= 0) continue;
        if (rt == Taille::Moyen && moyenCercle <= 0) continue;
        if (rt == Taille::Grand && grandCercle <= 0) continue;
        Cercle rc(getCouleur(), rt);
        
        if (plateau.getCase(rx, ry).testerCercles(rc)) {
            return {{rx, ry}, rc};
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

// LOGIQUE DE DÉFENSE 
std::pair<std::pair<int, int>, Cercle> Machine::testerMenaceImminente(const Plateau &plateau) {
    
    // CAS 1 : Concentrique 
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            Case courante = plateau.getCase(x, y);
            const vector<Cercle>& cercles = courante.getCercles();
            
            if (cercles.size() == 2) {
                Cercle c1 = cercles[0];
                Cercle c2 = cercles[1];
                
                // Correction: on utilise getCouleur() pour comparer dynamiquement
                if (c1.getCouleur() == c2.getCouleur() && c1.getCouleur() != getCouleur()) {
                    bool aPetit = (c1.getTaille() == Taille::Petit || c2.getTaille() == Taille::Petit);
                    bool aMoyen = (c1.getTaille() == Taille::Moyen || c2.getTaille() == Taille::Moyen);
                    // bool aGrand n'est pas nécessaire par déduction
                    
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

                // COMBINAISON 1 : On regarde c1 et c2 -> menace sur c3
                menace = testerAlignementTailleCroissante(c1, c2, c3, x, y, x2, y2, x3, y3);
                if (menace.first.first != -1) return menace;
                menace = testerAlignementMemeTaille(c1, c2, c3, x, y, x2, y2, x3, y3);
                if (menace.first.first != -1) return menace;

                // COMBINAISON 2 : On regarde c1 et c3 -> menace sur c2 (LE TROU AU MILIEU)
                // Note: on passe (x2, y2) en dernière position car c'est la cible
                menace = testerAlignementTailleCroissante(c1, c3, c2, x, y, x3, y3, x2, y2);
                if (menace.first.first != -1) return menace;
                menace = testerAlignementMemeTaille(c1, c3, c2, x, y, x3, y3, x2, y2);
                if (menace.first.first != -1) return menace;

                // COMBINAISON 3 : On regarde c2 et c3 -> menace sur c1
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
                cercle1.getCouleur() != getCouleur()) { // Check vs Machine color
                
                int t1 = static_cast<int>(cercle1.getTaille());
                int t2 = static_cast<int>(cercle2.getTaille());
                
                // Si tailles différentes, on cherche la 3ème pour faire la suite (0,1,2)
                if (t1 != t2) {
                    // La taille manquante est toujours 3 moins la somme des deux autres
                    int t3 = 3 - (t1 + t2);
                    
                    if (t3 >= 0 && t3 <= 2) {
                        Taille tailleManquante = static_cast<Taille>(t3);
                        
                        // Vérifier si la case cible (c3) est libre pour cette taille
                        bool occupe = false;
                        for (const Cercle& c : c3.getCercles()) {
                            if (c.getTaille() == tailleManquante) { occupe = true; break; }
                        }
                        
                        if (!occupe) {
                            // On renvoie x3, y3 car c'est toujours la coordonnée cible passée en paramètre
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
            // Même couleur, même taille, pas nous
            if (cercle1.getCouleur() == cercle2.getCouleur() &&
                cercle1.getTaille() == cercle2.getTaille() &&
                cercle1.getCouleur() != getCouleur()) { // Check vs Machine color
                
                // Vérifier si case3 (la cible) a déjà ce cercle
                bool presente = false;
                for (const Cercle& c : c3.getCercles()) {
                    if (c.getTaille() == cercle1.getTaille()) {
                        presente = true;
                        break;
                    }
                }
                
                if (!presente) {
                    // On renvoie les coordonnées de la cible (x3, y3)
                    return {{x3, y3}, Cercle(Couleur::Rouge, cercle1.getTaille())};
                }
            }
        }
    }
    return {{-1, -1}, Cercle()};
}

Taille Machine::analyserLigne(const Case& c1, const Case& c2, const Case& cible) {
    return Taille::Moyen; // Placeholder si cette fonction était déclarée dans le hpp
}