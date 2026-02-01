#include <iostream>
#include <cassert>
#include "Machine.hpp"
#include "Plateau.hpp"
#include "Case.hpp"
#include "Enums.h"

using namespace std;

void afficherResultatTest(string nomTest, bool succes) {
    if (succes) cout << "[OK] " << nomTest << endl;
    else cout << "[ECHEC] " << nomTest << endl;
}

int main() {
    cout << "=== TEST DE L'INTELLIGENCE ARTIFICIELLE ===" << endl;

    // --- TEST 1 : PRIORITÉ ATTAQUE (VICTOIRE) ---
    {
        cout << "\n--- Scenario 1 : Opportunite de Victoire ---" << endl;
        Plateau p;
        Machine bot("Terminator", Couleur::Rouge);

        // Mise en place : 2 Rouges alignés sur la ligne 0
        // (0,0) Petit Rouge
        p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
        // (1,0) Petit Rouge
        p.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Petit));
        
        // Le coup gagnant est (2,0) Petit Rouge
        cout << "Configuration : 2 Petits Rouges en (0,0) et (1,0). Le bot doit jouer en (2,0)." << endl;

        auto action = bot.deciderAction(p);

        bool bonEndroit = (action.first.first == 2 && action.first.second == 0);
        bool bonnePiece = (action.second.getCouleur() == Couleur::Rouge && action.second.getTaille() == Taille::Petit);

        afficherResultatTest("Detection Victoire Ligne", bonEndroit && bonnePiece);
        if(!bonEndroit) cout << "   -> Le bot a joue en (" << action.first.first << "," << action.first.second << ")" << endl;
    }

    // --- TEST 2 : PRIORITÉ DÉFENSE (BLOCAGE) ---
    {
        cout << "\n--- Scenario 2 : Menace Adverse (Bleu) ---" << endl;
        Plateau p;
        Machine bot("Defenseur", Couleur::Rouge); // Je suis Rouge

        // Mise en place : L'ennemi (Bleu) a 2 Moyens alignés en diagonale
        // (0,0) Moyen Bleu
        p.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Moyen));
        // (1,1) Moyen Bleu
        p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Moyen));

        // La menace est en (2,2) Moyen Bleu. Le bot DOIT jouer (2,2) Moyen Rouge pour bloquer.
        cout << "Configuration : Menace Bleue diagonale. Le bot doit bloquer en (2,2) avec Moyen." << endl;

        auto action = bot.deciderAction(p);

        bool bonEndroit = (action.first.first == 2 && action.first.second == 2);
        // Important : Le bot doit jouer SA couleur (Rouge) pour bloquer
        bool bonnePiece = (action.second.getCouleur() == Couleur::Rouge && action.second.getTaille() == Taille::Moyen);

        afficherResultatTest("Blocage Diagonale", bonEndroit && bonnePiece);
        if(!bonEndroit) cout << "   -> Le bot a joue en (" << action.first.first << "," << action.first.second << ")" << endl;
    }

    // --- TEST 3 : STRATÉGIE (CENTRE) ---
    {
        cout << "\n--- Scenario 3 : Plateau Vide (Ouverture) ---" << endl;
        Plateau p;
        Machine bot("Strategist", Couleur::Rouge);

        cout << "Configuration : Plateau vide. Le bot doit prendre le centre (1,1) Grand." << endl;

        auto action = bot.deciderAction(p);

        bool bonEndroit = (action.first.first == 1 && action.first.second == 1);
        bool bonnePiece = (action.second.getTaille() == Taille::Grand);

        afficherResultatTest("Prise du Centre", bonEndroit && bonnePiece);
    }

    return 0;
}