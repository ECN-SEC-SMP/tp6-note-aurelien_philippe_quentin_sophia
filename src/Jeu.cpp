#include "Jeu.hpp"
#include <string>

Jeu::Jeu(){
    joueurs = std::vector<Joueur>();
    plateau = Plateau();
}

int Jeu::getVersion(){
    return version;
}

void Jeu::ajouterJoueurHumain(const std::string& nom, Couleur couleur){
    Humain joueur = Humain(nom, couleur);
    joueurs.push_back(joueur);
}

// void Jeu::ajouterJoueurMachine(const std::string, Couleur couleur){
//     // À implémenter plus tard
// }

void Jeu::choisirVersion(){
    int version;
    std::cout << "Entrez une version du jeu : ";
    std::cin >> version;
    if(version >= 1 && version <= 3){
        this->version = version;
    } else {
        std::cout << "La version entrée n'est pas valide. Retentez : ";
        choisirVersion();
    }
}

int Jeu::entrerNombreJoueurs(){
    int nombreJoueurs;
    std::cout << "Entrez le nombre de joueurs (0 à 3) : ";
    std::cin >> nombreJoueurs;

    if(nombreJoueurs < 0 && nombreJoueurs > 3){
        std::cout << "Le nombre de joueurs entré n'est pas valide. Retentez : ";
        entrerNombreJoueurs();
    }
    return nombreJoueurs;  
}

void Jeu::entrerJoueurs(){

    if(this->getVersion() == 1){
        for(int i = 0; i < 4; i++){
            std::string nom;

            std::cout << "Entrez le nom du joueur " << i+1 << " : ";
            std::cin >> nom;
            ajouterJoueurHumain(nom, static_cast<Couleur>(i));
        }
    }
    else if(this->getVersion() == 2){
        std::string nom1;
        std::string nom2;

        std::cout << "Entrez le nom du joueur 1 : ";
        std::cin >> nom1;
        std::cout << "Entrez le nom du joueur 2 : ";
        std::cin >> nom2;

        ajouterJoueurHumain(nom1, Couleur::Rouge);
        ajouterJoueurHumain(nom2, Couleur::Vert);
        ajouterJoueurHumain(nom1, Couleur::Bleu);
        ajouterJoueurHumain(nom2, Couleur::Jaune);
    }
    else {
        int nbJoueurs;
        int nbOrdinateurs;

        std::cout << "Entrez le nombre de joueurs humains (0 à 3) : ";
        std::cin >> nbJoueurs;

        nbOrdinateurs = 4 - nbJoueurs;
        
        for(int i = 0; i < nbJoueurs; i++){
            std::string nom;

            std::cout << "Entrez le nom du joueur " << i+1 << " : ";
            std::cin >> nom;
            ajouterJoueurHumain(nom, static_cast<Couleur>(i));
        }

        for(int j = 0; j < nbOrdinateurs; j ++){
            std::string nom = "Ordinateur_" + std::to_string(j+1);
            ajouterJoueurMachine(nom, static_cast<Couleur>(j + nbJoueurs));
        }
    }
}

void Jeu::initialiser(){


    // Affichage !!!!!!!!!!!



    // Choix de la version
    choisirVersion();

    // Entrée des joueurs
    entrerJoueurs();

    // Tirage 
    this->joueurCourant = rand() % joueurs.size();

    lancerPartie();
}

void Jeu::lancerPartie(){
    std::cout << "=== Début de la partie ===" << std::endl;
    lancerTourSuivant();
}

void Jeu::lancerTourSuivant(){
    // Demander action au joueur courant
    // joueurs[joueurCourant].deciderAction();

    // tester si le joueur a le cercle décidé

    // plateau.placerCercle();

    Couleur couleurJoueurCourant = joueurs[joueurCourant].getCouleur();
    if(testerVictoire(couleurJoueurCourant) || verifierFinDePartie()){
        std::cout << "Le joueur jsp quoi a gagné" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Tester les victoires pour chaque taille de cercle
    for(int taille_idx = 0; taille_idx < 3; taille_idx++){
        Taille taille = static_cast<Taille>(taille_idx);
        
        // Vérifier les lignes horizontales
        for(int y = 0; y < 3; y++){
            bool ligne_gagnante = true;
            for(int x = 0; x < 3; x++){
                const Case& case_courante = plateau.getCase(x, y);
                const std::vector<Cercle>& cercles = case_courante.getCercles();
                bool trouve = false;
                for(const auto& c : cercles){
                    if(c.getCouleur() == couleur && c.getTaille() == taille){
                        trouve = true;
                        break;
                    }
                }
                if(!trouve){
                    ligne_gagnante = false;
                    break;
                }
            }
            if(ligne_gagnante) return true;
        }
        
        // Vérifier les colonnes verticales
        for(int x = 0; x < 3; x++){
            bool colonne_gagnante = true;
            for(int y = 0; y < 3; y++){
                const Case& case_courante = plateau.getCase(x, y);
                const std::vector<Cercle>& cercles = case_courante.getCercles();
                bool trouve = false;
                for(const auto& c : cercles){
                    if(c.getCouleur() == couleur && c.getTaille() == taille){
                        trouve = true;
                        break;
                    }
                }
                if(!trouve){
                    colonne_gagnante = false;
                    break;
                }
            }
            if(colonne_gagnante) return true;
        }
        
        // Vérifier la diagonale principale (0,0) -> (1,1) -> (2,2)
        bool diag_principale = true;
        for(int i = 0; i < 3; i++){
            const Case& case_courante = plateau.getCase(i, i);
            const std::vector<Cercle>& cercles = case_courante.getCercles();
            bool trouve = false;
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur && c.getTaille() == taille){
                    trouve = true;
                    break;
                }
            }
            if(!trouve){
                diag_principale = false;
                break;
            }
        }
        if(diag_principale) return true;
        
        // Vérifier la diagonale anti-principale (0,2) -> (1,1) -> (2,0)
        bool diag_anti = true;
        for(int i = 0; i < 3; i++){
            const Case& case_courante = plateau.getCase(i, 2-i);
            const std::vector<Cercle>& cercles = case_courante.getCercles();
            bool trouve = false;
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur && c.getTaille() == taille){
                    trouve = true;
                    break;
                }
            }
            if(!trouve){
                diag_anti = false;
                break;
            }
        }
        if(diag_anti) return true;
    }
    
    // Vérifier la victoire "Otrio" : toutes les 3 tailles dans une seule case
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            const Case& case_courante = plateau.getCase(x, y);
            const std::vector<Cercle>& cercles = case_courante.getCercles();
            bool a_petit = false, a_moyen = false, a_grand = false;
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur){
                    if(c.getTaille() == Taille::Petit) a_petit = true;
                    if(c.getTaille() == Taille::Moyen) a_moyen = true;
                    if(c.getTaille() == Taille::Grand) a_grand = true;
                }
            }
            if(a_petit && a_moyen && a_grand) return true;
        }
    }
    
    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}