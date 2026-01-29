#include <iostream>
#include "Jeu.hpp"
#include "Plateau.hpp"
#include "Cercle.hpp"
#include "Enums.h"

using namespace std;

void testVisualisation(string titre) {
    cout << "\n--- TEST : " << titre << " ---" << endl;
}

int main() {
    cout << "=== Tests de la logique de victoire ===" << endl;
    
    // Test 1: Victoire horizontale avec 3 cercles de même taille et couleur
    testVisualisation("Victoire horizontale - 3 Petits Rouges en ligne (y=0)");
    Jeu jeu1;
    Plateau& p1 = jeu1.getPlateau();
    
    // Placer 3 petits cercles rouges en ligne horizontale
    p1.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
    p1.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Petit));
    p1.placerCercle(2, 0, Cercle(Couleur::Rouge, Taille::Petit));
    
    if(jeu1.testerVictoire(Couleur::Rouge)) {
        cout << "✓ SUCCÈS: Victoire détectée correctement" << endl;
    } else {
        cout << "✗ ÉCHEC: Victoire non détectée" << endl;
    }
    
    // Test 2: Victoire verticale
    testVisualisation("Victoire verticale - 3 Moyens Verts en colonne (x=1)");
    Jeu jeu2;
    Plateau& p2 = jeu2.getPlateau();
    
    p2.placerCercle(1, 0, Cercle(Couleur::Vert, Taille::Moyen));
    p2.placerCercle(1, 1, Cercle(Couleur::Vert, Taille::Moyen));
    p2.placerCercle(1, 2, Cercle(Couleur::Vert, Taille::Moyen));
    
    if(jeu2.testerVictoire(Couleur::Vert)) {
        cout << "✓ SUCCÈS: Victoire verticale détectée" << endl;
    } else {
        cout << "✗ ÉCHEC: Victoire verticale non détectée" << endl;
    }
    
    // Test 3: Victoire diagonale (haut-gauche vers bas-droite)
    testVisualisation("Victoire diagonale - 3 Grands Bleus (0,0) -> (2,2)");
    Jeu jeu3;
    Plateau& p3 = jeu3.getPlateau();
    
    p3.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Grand));
    p3.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Grand));
    p3.placerCercle(2, 2, Cercle(Couleur::Bleu, Taille::Grand));
    
    if(jeu3.testerVictoire(Couleur::Bleu)) {
        cout << "✓ SUCCÈS: Victoire diagonale détectée" << endl;
    } else {
        cout << "✗ ÉCHEC: Victoire diagonale non détectée" << endl;
    }
    
    // Test 4: Victoire diagonale (haut-droite vers bas-gauche)
    testVisualisation("Victoire diagonale - 3 Petits Jaunes (2,0) -> (0,2)");
    Jeu jeu4;
    Plateau& p4 = jeu4.getPlateau();
    
    p4.placerCercle(2, 0, Cercle(Couleur::Jaune, Taille::Petit));
    p4.placerCercle(1, 1, Cercle(Couleur::Jaune, Taille::Petit));
    p4.placerCercle(0, 2, Cercle(Couleur::Jaune, Taille::Petit));
    
    if(jeu4.testerVictoire(Couleur::Jaune)) {
        cout << "✓ SUCCÈS: Victoire diagonale inverse détectée" << endl;
    } else {
        cout << "✗ ÉCHEC: Victoire diagonale inverse non détectée" << endl;
    }
    
    // Test 5: Victoire dans une case (3 tailles différentes)
    testVisualisation("Victoire dans une case - Petit, Moyen et Grand Rouge en (1,1)");
    Jeu jeu5;
    Plateau& p5 = jeu5.getPlateau();
    
    p5.placerCercle(1, 1, Cercle(Couleur::Rouge, Taille::Petit));
    p5.placerCercle(1, 1, Cercle(Couleur::Rouge, Taille::Moyen));
    p5.placerCercle(1, 1, Cercle(Couleur::Rouge, Taille::Grand));
    
    if(jeu5.testerVictoire(Couleur::Rouge)) {
        cout << "✓ SUCCÈS: Victoire dans une case détectée" << endl;
    } else {
        cout << "✗ ÉCHEC: Victoire dans une case non détectée" << endl;
    }
    
    // Test 6: Pas de victoire - plateau vide
    testVisualisation("Pas de victoire - Plateau vide");
    Jeu jeu6;
    
    if(!jeu6.testerVictoire(Couleur::Rouge)) {
        cout << "✓ SUCCÈS: Aucune victoire détectée sur plateau vide" << endl;
    } else {
        cout << "✗ ÉCHEC: Fausse victoire détectée" << endl;
    }
    
    // Test 7: Pas de victoire - configuration incomplète
    testVisualisation("Pas de victoire - Seulement 2 cercles alignés");
    Jeu jeu7;
    Plateau& p7 = jeu7.getPlateau();
    
    p7.placerCercle(0, 0, Cercle(Couleur::Vert, Taille::Petit));
    p7.placerCercle(1, 0, Cercle(Couleur::Vert, Taille::Petit));
    
    if(!jeu7.testerVictoire(Couleur::Vert)) {
        cout << "✓ SUCCÈS: Aucune victoire détectée avec seulement 2 cercles" << endl;
    } else {
        cout << "✗ ÉCHEC: Fausse victoire détectée" << endl;
    }
    
    cout << "\n=== Fin des tests ===" << endl;
    return 0;
}
