#include <iostream>
#include "Plateau.hpp"
#include "Cercle.hpp"
#include "Enums.h"
#include "Jeu.hpp"

using namespace std;

void testVisualisation(string titre) {
    cout << "\n--- TEST : " << titre << " ---" << endl;
}

int main() {
    Plateau p;
    
    // Test 1: Victory on first row (horizontal)
    testVisualisation("Test 1: Victory horizontale (première ligne)");
    p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
    p.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Moyen));
    p.placerCercle(2, 0, Cercle(Couleur::Rouge, Taille::Grand));
    
    // Manual test of victory logic (since Jeu needs players)
    // Check that all 3 cells in row 0 have Rouge
    bool victoire = true;
    for(int x = 0; x < 3; x++){
        const Case& currentCase = p.getCase(x, 0);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        bool hasCouleur = false;
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == Couleur::Rouge){
                hasCouleur = true;
                break;
            }
        }
        
        if(!hasCouleur){
            victoire = false;
            break;
        }
    }
    
    if(victoire){
        cout << "✓ Rouge a gagné sur la première ligne !" << endl;
    } else {
        cout << "✗ Échec du test de victoire horizontale" << endl;
    }
    
    p.afficher();
    
    // Test 2: No victory with mixed colors
    Plateau p2;
    testVisualisation("Test 2: Pas de victoire avec couleurs mélangées");
    p2.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
    p2.placerCercle(1, 0, Cercle(Couleur::Vert, Taille::Moyen));
    p2.placerCercle(2, 0, Cercle(Couleur::Rouge, Taille::Grand));
    
    victoire = true;
    for(int x = 0; x < 3; x++){
        const Case& currentCase = p2.getCase(x, 0);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        bool hasCouleur = false;
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == Couleur::Rouge){
                hasCouleur = true;
                break;
            }
        }
        
        if(!hasCouleur){
            victoire = false;
            break;
        }
    }
    
    if(!victoire){
        cout << "✓ Pas de victoire détectée (correct)" << endl;
    } else {
        cout << "✗ Échec: victoire détectée à tort" << endl;
    }
    
    p2.afficher();
    
    // Test 3: Diagonal victory
    Plateau p3;
    testVisualisation("Test 3: Victory en diagonale");
    p3.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Petit));
    p3.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Moyen));
    p3.placerCercle(2, 2, Cercle(Couleur::Bleu, Taille::Grand));
    
    victoire = true;
    for(int i = 0; i < 3; i++){
        const Case& currentCase = p3.getCase(i, i);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        bool hasCouleur = false;
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == Couleur::Bleu){
                hasCouleur = true;
                break;
            }
        }
        
        if(!hasCouleur){
            victoire = false;
            break;
        }
    }
    
    if(victoire){
        cout << "✓ Bleu a gagné en diagonale !" << endl;
    } else {
        cout << "✗ Échec du test de victoire en diagonale" << endl;
    }
    
    p3.afficher();

    return 0;
}
