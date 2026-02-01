#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "../lib/Machine.hpp"
#include "../lib/Plateau.hpp"
#include "../lib/Case.hpp"

using namespace std;

// --- Outils d'affichage couleur ---
const string VERT = "\033[32m";
const string ROUGE = "\033[31m";
const string JAUNE = "\033[33m";
const string RESET = "\033[0m";

void testResult(string nom, bool succes) {
    if (succes) cout << VERT << "[OK] " << nom << RESET << endl;
    else {
        cout << ROUGE << "[ECHEC] " << nom << RESET << endl;
        exit(1); // On arrête tout si ça rate
    }
}

// --- Classe Spéciale pour le Test ---
// Elle hérite de Machine pour avoir accès aux variables 'protected' (les stocks)
class MachineTesteur : public Machine {
public:
    MachineTesteur(string nom, Couleur c) : Machine(nom, c) {}

    void tricherViderStockGrand() { grandCercle = 0; }
    void tricherResetStock() { petitCercle = 3; moyenCercle = 3; grandCercle = 3; }
    
    // Pour vérifier l'état après coup
    int getNbGrands() { return grandCercle; }
};

int main() {
    cout << "\n==========================================" << endl;
    cout << "   PROTOCOLE DE TEST : INTELLIGENCE & ROBUSTESSE" << endl;
    cout << "==========================================\n" << endl;

    // ---------------------------------------------------------
    // TEST 1 : ATTAQUE (Victoire Immédiate)
    // ---------------------------------------------------------
    {
        cout << ">>> Test 1 : Instinct de Tueur (Attaque)... ";
        Plateau p;
        MachineTesteur bot("Terminator", Couleur::Rouge);

        // Situation : 2 Rouges alignés, il manque le 3ème en (2,0)
        p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
        p.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Petit));

        auto action = bot.deciderAction(p);

        bool victoireTrouvee = (action.first.first == 2 && action.first.second == 0 && action.second.getTaille() == Taille::Petit);
        testResult("Detection Victoire", victoireTrouvee);
    }

    // ---------------------------------------------------------
    // TEST 2 : DÉFENSE (Blocage)
    // ---------------------------------------------------------
    {
        cout << ">>> Test 2 : Mur de fer (Defense)... ";
        Plateau p;
        MachineTesteur bot("Defender", Couleur::Rouge);

        // Situation : L'ennemi (Bleu) va gagner en diagonale (2,2)
        p.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Moyen));
        p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Moyen));

        auto action = bot.deciderAction(p);

        // Le bot doit jouer en (2,2) avec un Moyen (pour bloquer) et SA couleur (Rouge)
        bool blocageReussi = (action.first.first == 2 && action.first.second == 2 
                           && action.second.getTaille() == Taille::Moyen 
                           && action.second.getCouleur() == Couleur::Rouge);
        
        testResult("Blocage Menace", blocageReussi);
    }

    // ---------------------------------------------------------
    // TEST 3 : LE BUG DES STOCKS (Crash Test)
    // ---------------------------------------------------------
    {
        cout << ">>> Test 3 : Gestion de crise (Stock Vide)... " << endl;
        Plateau p;
        MachineTesteur bot("Genius", Couleur::Rouge);

        // Situation : Une victoire est possible avec un GRAND cercle en (0,2)
        p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
        p.placerCercle(0, 1, Cercle(Couleur::Rouge, Taille::Moyen));
        // Il manque (0,2) Grand pour faire une suite Croissante

        // PIÈGE : On retire tous les grands cercles au robot !
        bot.tricherViderStockGrand();
        cout << "    (Contexte : Victoire possible avec Grand Cercle, mais Stock Grand = 0)" << endl;

        // Si le bug est présent, cette ligne va faire une boucle infinie ou planter
        auto action = bot.deciderAction(p);

        // Vérification : Le bot NE DOIT PAS avoir joué un Grand Cercle
        bool aJoueGrand = (action.second.getTaille() == Taille::Grand);
        
        if (aJoueGrand) {
            testResult("Echec : A joue une piece inexistante", false);
        } else {
            // S'il a joué autre chose (ou rien), c'est qu'il a contourné le piège
            testResult("Succes : A renonce a la victoire impossible", true);
            cout << "    -> A joue a la place : (" << action.first.first << "," << action.first.second << ")" << endl;
        }
    }

    cout << "\n==========================================" << endl;
    cout << VERT << "   TOUS LES SYSTEMES SONT OPERATIONNELS" << RESET << endl;
    cout << "==========================================" << endl;

    return 0;
}