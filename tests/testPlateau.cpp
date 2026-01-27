#include <iostream>
#include "Plateau.hpp"
#include "Cercle.hpp"
#include "Enums.h"

using namespace std;

void testVisualisation(string titre) {
    cout << "\n--- TEST : " << titre << " ---" << endl;
}

int main() {
    // 1. Création du plateau
    Plateau p;
    testVisualisation("Affichage du plateau vide");
    p.afficher();

    // 2. Test d'un placement valide (Petit Rouge en 0,0)
    testVisualisation("Placement Valide : Petit Rouge en (0,0)");
    Cercle c1(Couleur::Rouge, Taille::Petit);
    bool resultat = p.placerCercle(0, 0, c1);
    
    if (resultat) cout << "Succès !" << endl;
    else cout << "Échec inattendu..." << endl;
    p.afficher();

    // 3. Test de superposition valide (Moyen Vert en 0,0)
    // Cela doit marcher car la taille est différente
    testVisualisation("Empilement Valide : Moyen Vert en (0,0)");
    Cercle c2(Couleur::Vert, Taille::Moyen);
    if (p.placerCercle(0, 0, c2)) {
        cout << "Succès ! On doit voir [R V .]" << endl;
    }
    p.afficher();

    // 4. Test CRITIQUE : Conflit de taille (Petit Bleu en 0,0)
    // Cela DOIT échouer car il y a déjà un Petit Rouge
    testVisualisation("Test Conflit : Petit Bleu en (0,0) -> Doit échouer");
    Cercle c3(Couleur::Bleu, Taille::Petit);
    if (p.placerCercle(0, 0, c3)) {
        cout << "ERREUR : Le coup aurait du être bloqué !" << endl;
    } else {
        cout << "Bravo : Le coup a bien été bloqué (Taille déjà prise)." << endl;
    }

    // 5. Test Hors Limites
    testVisualisation("Test Hors Limites : (-1, 5)");
    p.placerCercle(-1, 5, c1);

    // 6. Remplissage d'une autre case pour voir l'affichage global
    testVisualisation("Remplissage complet case (2,2)");
    p.placerCercle(2, 2, Cercle(Couleur::Jaune, Taille::Petit));
    p.placerCercle(2, 2, Cercle(Couleur::Noir, Taille::Moyen));
    p.placerCercle(2, 2, Cercle(Couleur::Blanc, Taille::Grand));
    
    p.afficher();

    return 0;
}