#include <gtest/gtest.h>
#include "Plateau.hpp"
#include "Cercle.hpp"
#include "Enums.h"

// Fixture pour éviter de redéclarer le plateau à chaque test
class PlateauTest : public ::testing::Test {
protected:
    Plateau p;
};

// 1. Test du placement valide
TEST_F(PlateauTest, PlacementValide) {
    Cercle c1(Couleur::Rouge, Taille::Petit);
    // On s'attend à ce que placerCercle retourne true
    EXPECT_TRUE(p.placerCercle(0, 0, c1));
}

// 2. Test de l'empilement (tailles différentes sur la même case)
TEST_F(PlateauTest, EmpilementTaillesDifferentes) {
    Cercle petit(Couleur::Rouge, Taille::Petit);
    Cercle moyen(Couleur::Vert, Taille::Moyen);
    
    p.placerCercle(0, 0, petit);
    
    // On s'attend à ce que cela réussisse car les tailles sont différentes
    EXPECT_TRUE(p.placerCercle(0, 0, moyen));
}

// 3. Test du conflit de taille (Même taille sur la même case)
TEST_F(PlateauTest, ConflitTailleIdentique) {
    Cercle rougePetit(Couleur::Rouge, Taille::Petit);
    Cercle bleuPetit(Couleur::Bleu, Taille::Petit);
    
    p.placerCercle(0, 0, rougePetit);
    
    // On s'attend à ce que cela échoue (false) car la place 'Petit' est prise
    EXPECT_FALSE(p.placerCercle(0, 0, bleuPetit));
}

// 4. Test des limites du plateau
TEST_F(PlateauTest, HorsLimites) {
    Cercle c(Couleur::Rouge, Taille::Petit);
    
    // Test coordonnées négatives et trop grandes
    EXPECT_FALSE(p.placerCercle(-1, 0, c));
    EXPECT_FALSE(p.placerCercle(0, 5, c));
}

// 5. Test de remplissage complet d'une case
TEST_F(PlateauTest, CasePleine) {
    EXPECT_TRUE(p.placerCercle(2, 2, Cercle(Couleur::Jaune, Taille::Petit)));
    EXPECT_TRUE(p.placerCercle(2, 2, Cercle(Couleur::Vert, Taille::Moyen)));
    EXPECT_TRUE(p.placerCercle(2, 2, Cercle(Couleur::Bleu, Taille::Grand)));
    
    // Un quatrième ajout sur la même case devrait échouer (si votre logique le prévoit)
    Cercle surplus(Couleur::Rouge, Taille::Petit);
    EXPECT_FALSE(p.placerCercle(2, 2, surplus));
}