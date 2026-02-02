#include <gtest/gtest.h>
#include "../lib/Jeu.hpp"

//  Test de l'ajout de joueurs
TEST(JeuTest, AjouterJoueurs) {
    Jeu jeu;
    
    jeu.ajouterJoueurHumain("Alice", Couleur::Bleu);
    jeu.ajouterJoueurMachine("Robot", Couleur::Rouge);
    
    // On ne peut pas accéder directement au vecteur (privé), 
    // mais on vérifie que les méthodes ne crashent pas.
}

// Test de la logique de victoire : Superposition (3 cercles même case)
TEST(JeuTest, VictoireSuperposition) {
    Jeu jeu;
    Plateau& p = jeu.getPlateau(); // Nécessite un getter ou de passer par l'objet
    
    // On simule 3 cercles de la même couleur sur la case (1,1)
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Petit));
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Moyen));
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Grand));
    
    // L'action qui déclenche le test (la dernière posée)
    std::pair<std::pair<int, int>, Cercle> lastAction = {{1, 1}, Cercle(Couleur::Bleu, Taille::Grand)};
    
    EXPECT_TRUE(jeu.testerVictoire(Couleur::Bleu, lastAction));
}

// Test de la logique de victoire : Alignement même taille
TEST(JeuTest, VictoireAlignementHorizontal) {
    Jeu jeu;
    Plateau& p = jeu.getPlateau();
    
    // 3 Grands cercles bleus alignés horizontalement
    p.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Grand));
    p.placerCercle(1, 0, Cercle(Couleur::Bleu, Taille::Grand));
    p.placerCercle(2, 0, Cercle(Couleur::Bleu, Taille::Grand));
    
    std::pair<std::pair<int, int>, Cercle> lastAction = {{2, 0}, Cercle(Couleur::Bleu, Taille::Grand)};
    
    EXPECT_TRUE(jeu.testerVictoire(Couleur::Bleu, lastAction));
}

// Test de la logique de victoire : Suite (Petit, Moyen, Grand)
TEST(JeuTest, VictoireSuiteDiagonale) {
    Jeu jeu;
    Plateau& p = jeu.getPlateau();
    
    // Diagonale : (0,0) Petit, (1,1) Moyen, (2,2) Grand
    p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Petit));
    p.placerCercle(1, 1, Cercle(Couleur::Rouge, Taille::Moyen));
    p.placerCercle(2, 2, Cercle(Couleur::Rouge, Taille::Grand));
    
    std::pair<std::pair<int, int>, Cercle> lastAction = {{2, 2}, Cercle(Couleur::Rouge, Taille::Grand)};
    
    EXPECT_TRUE(jeu.testerVictoire(Couleur::Rouge, lastAction));
}

// Test de non-victoire
TEST(JeuTest, PasDeVictoireSiMelange) {
    Jeu jeu;
    Plateau& p = jeu.getPlateau();
    
    p.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Petit));
    p.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Petit)); // Autre couleur
    p.placerCercle(2, 0, Cercle(Couleur::Bleu, Taille::Petit));
    
    std::pair<std::pair<int, int>, Cercle> lastAction = {{2, 0}, Cercle(Couleur::Bleu, Taille::Petit)};
    
    EXPECT_FALSE(jeu.testerVictoire(Couleur::Bleu, lastAction));
}