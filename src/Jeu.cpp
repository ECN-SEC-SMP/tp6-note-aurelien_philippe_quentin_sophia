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

    Couleur couleurCourante = joueurs[joueurCourant].getCouleur();
    
    if(testerVictoire(couleurCourante) || verifierFinDePartie()){
        std::cout << "Le joueur " << joueurs[joueurCourant].getNom() << " a gagné !" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Vérifier les alignements horizontaux, verticaux et diagonaux
    
    // 1. Vérifier les alignements de même couleur
    // Lignes horizontales
    for(int y = 0; y < 3; y++){
        for(Taille taille : {Taille::Petit, Taille::Moyen, Taille::Grand}){
            bool aligned = true;
            for(int x = 0; x < 3; x++){
                const Case& c = plateau.getCase(x, y);
                const std::vector<Cercle>& cercles = c.getCercles();
                
                bool found = false;
                for(const Cercle& cercle : cercles){
                    if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    aligned = false;
                    break;
                }
            }
            if(aligned) return true;
        }
    }
    
    // Colonnes verticales
    for(int x = 0; x < 3; x++){
        for(Taille taille : {Taille::Petit, Taille::Moyen, Taille::Grand}){
            bool aligned = true;
            for(int y = 0; y < 3; y++){
                const Case& c = plateau.getCase(x, y);
                const std::vector<Cercle>& cercles = c.getCercles();
                
                bool found = false;
                for(const Cercle& cercle : cercles){
                    if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    aligned = false;
                    break;
                }
            }
            if(aligned) return true;
        }
    }
    
    // Diagonale principale (0,0 -> 2,2)
    for(Taille taille : {Taille::Petit, Taille::Moyen, Taille::Grand}){
        bool aligned = true;
        for(int i = 0; i < 3; i++){
            const Case& c = plateau.getCase(i, i);
            const std::vector<Cercle>& cercles = c.getCercles();
            
            bool found = false;
            for(const Cercle& cercle : cercles){
                if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                    found = true;
                    break;
                }
            }
            if(!found){
                aligned = false;
                break;
            }
        }
        if(aligned) return true;
    }
    
    // Diagonale anti-principale (0,2 -> 2,0)
    for(Taille taille : {Taille::Petit, Taille::Moyen, Taille::Grand}){
        bool aligned = true;
        for(int i = 0; i < 3; i++){
            const Case& c = plateau.getCase(i, 2-i);
            const std::vector<Cercle>& cercles = c.getCercles();
            
            bool found = false;
            for(const Cercle& cercle : cercles){
                if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                    found = true;
                    break;
                }
            }
            if(!found){
                aligned = false;
                break;
            }
        }
        if(aligned) return true;
    }
    
    // 2. Vérifier les stacks complets (3 cercles de tailles différentes dans une même case)
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            const Case& c = plateau.getCase(x, y);
            const std::vector<Cercle>& cercles = c.getCercles();
            
            if(cercles.size() == 3){
                // Vérifier si les 3 cercles sont de la même couleur
                bool sameColor = true;
                for(const Cercle& cercle : cercles){
                    if(cercle.getCouleur() != couleur){
                        sameColor = false;
                        break;
                    }
                }
                if(sameColor) return true;
            }
        }
    }
    
    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}