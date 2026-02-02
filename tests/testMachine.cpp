#include <gtest/gtest.h>
#include "../lib/Machine.hpp"
#include "../lib/Plateau.hpp"

//Stratégie par défaut (Priorité Centre)
// Si le plateau est vide, la machine doit viser le centre (1,1) avec un Grand cercle.
TEST(MachineTest, StrategieCentreParDefaut) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    auto action = robot.deciderAction(p);
    
    EXPECT_EQ(action.first.first, 1);
    EXPECT_EQ(action.first.second, 1);
    EXPECT_EQ(action.second.getTaille(), Taille::Grand);
    EXPECT_EQ(action.second.getCouleur(), Couleur::Rouge);
}

// Priorité Attaque (Gagner immédiatement)
// On place deux cercles rouges, la machine doit poser le troisième pour gagner.
TEST(MachineTest, PrioriteAttaque) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    // On prépare une victoire imminente en ligne (0,0) et (1,0) avec Taille Moyen
    p.placerCercle(0, 0, Cercle(Couleur::Rouge, Taille::Moyen));
    p.placerCercle(1, 0, Cercle(Couleur::Rouge, Taille::Moyen));
    
    auto action = robot.deciderAction(p);
    
    // Elle doit détecter qu'en jouant en (2,0) elle gagne
    EXPECT_EQ(action.first.first, 2);
    EXPECT_EQ(action.first.second, 0);
    EXPECT_EQ(action.second.getTaille(), Taille::Moyen);
}

// Priorité Défense (Bloquer l'adversaire)
// L'adversaire (Bleu) va gagner, la machine doit bloquer.
TEST(MachineTest, PrioriteDefenseAlignement) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    // L'adversaire prépare un alignement Petit en colonne 0
    p.placerCercle(0, 0, Cercle(Couleur::Bleu, Taille::Petit));
    p.placerCercle(0, 1, Cercle(Couleur::Bleu, Taille::Petit));
    
    auto action = robot.deciderAction(p);
    
    // La machine doit bloquer en (0,2) avec n'importe quelle pièce de taille Petit
    EXPECT_EQ(action.first.first, 0);
    EXPECT_EQ(action.first.second, 2);
    EXPECT_EQ(action.second.getTaille(), Taille::Petit);
}

// Défense Concentrique
// L'adversaire a deux cercles sur la même case, la machine doit bloquer le 3ème.
TEST(MachineTest, DefenseConcentrique) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    // Bleu a mis Petit et Moyen en (2,2)
    p.placerCercle(2, 2, Cercle(Couleur::Bleu, Taille::Petit));
    p.placerCercle(2, 2, Cercle(Couleur::Bleu, Taille::Moyen));
    
    auto action = robot.deciderAction(p);
    
    EXPECT_EQ(action.first.first, 2);
    EXPECT_EQ(action.first.second, 2);
    EXPECT_EQ(action.second.getTaille(), Taille::Grand);
}

// Gestion du stock épuisé
// Si la machine n'a plus de Grands cercles, elle ne doit pas tenter de jouer au centre.
TEST(MachineTest, RespectDuStock) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    // On vide manuellement le stock de Grands cercles (hérité de Joueur)
    robot.retirerCercle(Taille::Grand);
    robot.retirerCercle(Taille::Grand);
    robot.retirerCercle(Taille::Grand);
    
    auto action = robot.deciderAction(p);
    
    // Elle ne doit pas avoir joué de Taille::Grand
    EXPECT_NE(action.second.getTaille(), Taille::Grand);
}

// Sécurité du hasard
// On remplit presque tout le plateau, on vérifie qu'elle finit par trouver une place valide.
TEST(MachineTest, HasardSecurise) {
    Plateau p;
    Machine robot("Bot", Couleur::Rouge);
    
    // On bloque le centre
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Grand));
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Moyen));
    p.placerCercle(1, 1, Cercle(Couleur::Bleu, Taille::Petit));
    
    auto action = robot.deciderAction(p);
    
    // L'action ne doit pas être l'action d'échec {{-1,-1}, ...}
    EXPECT_NE(action.first.first, -1);
}