#include <gtest/gtest.h>
#include "../lib/Joueur.hpp"

// Test du constructeur et des compteurs initiaux
TEST(JoueurTest, InitialisationCompteurs) {
    Joueur j("Alice", Couleur::Bleu);

    EXPECT_EQ(j.getNom(), "Alice");
    EXPECT_EQ(j.getCouleur(), Couleur::Bleu);
    // On vérifie que le joueur commence avec des cercles
    EXPECT_TRUE(j.aDesCercles());
}

// Test du retrait progressif des cercles
TEST(JoueurTest, RetirerCerclesDisponibles) {
    Joueur j("Bob", Couleur::Rouge);

    // Retrait des 3 petits cercles
    j.retirerCercle(Taille::Petit);
    j.retirerCercle(Taille::Petit);
    j.retirerCercle(Taille::Petit);

    // Le joueur doit encore avoir des cercles (moyens et grands)
    EXPECT_TRUE(j.aDesCercles());
}

// Test de la limite de retrait (retrait dans le vide)
TEST(JoueurTest, RetirerCercleInexistant) {
    Joueur j("Charlie", Couleur::Vert);

    // Vider totalement une taille
    for(int i = 0; i < 3; ++i) {
        j.retirerCercle(Taille::Grand);
    }

    // Tenter de retirer un 4ème cercle (ne doit pas planter)
    // Le code affiche un message d'erreur dans la console
    j.retirerCercle(Taille::Grand);
    
    // Le joueur a encore ses petits et moyens
    EXPECT_TRUE(j.aDesCercles());
}

// Test de la méthode aDesCercles quand tout est vide
TEST(JoueurTest, PlusDeCerclesDuTout) {
    Joueur j("Dora", Couleur::Jaune);

    // Retirer absolument tout
    for(int i = 0; i < 3; ++i) {
        j.retirerCercle(Taille::Petit);
        j.retirerCercle(Taille::Moyen);
        j.retirerCercle(Taille::Grand);
    }

    // Le joueur ne doit plus avoir de cercles
    EXPECT_FALSE(j.aDesCercles());
}

// Test du comportement par défaut de deciderAction
TEST(JoueurTest, ActionParDefaut) {
    Joueur j("Testeur", Couleur::Bleu);
    Plateau p;
    
    auto action = j.deciderAction(p);
    
    // Vérifie que l'action par défaut retourne bien {{-1, -1}, Cercle()}
    EXPECT_EQ(action.first.first, -1);
    EXPECT_EQ(action.first.second, -1);
}