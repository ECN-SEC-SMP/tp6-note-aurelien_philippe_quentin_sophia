/** *
 * @file Jeu.hpp
 * @brief Définition de la classe Jeu
 * @author Aurelien, Philippe, Quentin, Sophia
 * @date Janvier 2026
 */
#pragma once

#include <vector>
#include <memory>
#include "Enums.h"
#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Humain.hpp"
#include "Machine.hpp" 

/** *@brief Classe représentant le jeu 
  */
class Jeu {
    private :
        /** *
         * @brief Version du jeu (1 ou 2)
         */
        int version;

        /** *
         * @brief Liste des joueurs
         */ 
        std::vector<std::unique_ptr<Joueur>> joueurs;

        /** *
         * @brief Plateau de jeu
         */
        Plateau plateau;

        /** *
         * @brief Indice du joueur courant
         */
        int joueurCourant;
    public :
        // Constructeur
        Jeu();

        // Accesseurs
        int getVersion();

        Plateau& getPlateau() { return plateau; }

        // Mutateurs

        // Méthodes
        /** *@brief Ajoute un joueur humain au jeu 
          *  @param nom Le nom du joueur 
          *  @param couleur La couleur du joueur 
          */
        void ajouterJoueurHumain(const std::string& nom, Couleur couleur);

        /** *@brief Ajoute un joueur machine au jeu 
          *  @param nom Le nom du joueur 
          *  @param couleur La couleur du joueur 
          */
        void ajouterJoueurMachine(const std::string& nom, Couleur couleur);

        /** *@brief Permet de choisir la version du jeu
          */
        void choisirVersion();

        /** *@brief Permet d'entrer le nombre de joueurs
          *  @return Le nombre de joueurs 
          */
        int entrerNombreJoueurs();

        /** *@brief Permet d'entrer les noms des joueurs
          */
        void entrerNomJoueurs();

        /** *@brief Initialise le jeu
          */
        void initialiser(); 

        /** *@brief Lance la partie
          */
        void lancerPartie();

        /** *@brief Lance le tour du joueur courant
          */
        void lancerTourSuivant();

        /** *@brief Teste si le joueur de la couleur donnée a gagné après la dernière action 
          *  @param couleur La couleur du joueur 
          *  @param lastAction La dernière action effectuée 
          *  @return true si le joueur a gagné, false sinon 
          */
        bool testerVictoire(Couleur couleur, std::pair<std::pair<int, int>, Cercle> lastAction);

        /** *@brief Vérifie si la partie est terminée 
          *  @return true si la partie est terminée, false sinon 
          */
        bool verifierFinDePartie();
};