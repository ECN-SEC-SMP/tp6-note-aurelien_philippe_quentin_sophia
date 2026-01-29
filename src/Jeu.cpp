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

void Jeu::ajouterJoueurMachine(const std::string& nom, Couleur couleur){
    Machine joueur = Machine(nom, couleur);
    joueurs.push_back(joueur);
}

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
        std::cout << "Le joueur " << joueurs[joueurCourant].getNom() << " a gagné" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Test de victoire horizontale
    for(int y = 0; y < 3; y++){
        for(int taille_idx = 0; taille_idx < 3; taille_idx++){
            Taille taille = static_cast<Taille>(taille_idx);
            bool victoire = true;
            for(int x = 0; x < 3; x++){
                const Case& c = plateau.getCase(x, y);
                bool found = false;
                for(const Cercle& cercle : c.getCercles()){
                    if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    victoire = false;
                    break;
                }
            }
            if(victoire) return true;
        }
    }

    // Test de victoire verticale
    for(int x = 0; x < 3; x++){
        for(int taille_idx = 0; taille_idx < 3; taille_idx++){
            Taille taille = static_cast<Taille>(taille_idx);
            bool victoire = true;
            for(int y = 0; y < 3; y++){
                const Case& c = plateau.getCase(x, y);
                bool found = false;
                for(const Cercle& cercle : c.getCercles()){
                    if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    victoire = false;
                    break;
                }
            }
            if(victoire) return true;
        }
    }

    // Test de victoire diagonale (haut-gauche vers bas-droite)
    for(int taille_idx = 0; taille_idx < 3; taille_idx++){
        Taille taille = static_cast<Taille>(taille_idx);
        bool victoire = true;
        for(int i = 0; i < 3; i++){
            const Case& c = plateau.getCase(i, i);
            bool found = false;
            for(const Cercle& cercle : c.getCercles()){
                if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                    found = true;
                    break;
                }
            }
            if(!found){
                victoire = false;
                break;
            }
        }
        if(victoire) return true;
    }

    // Test de victoire diagonale (haut-droite vers bas-gauche)
    for(int taille_idx = 0; taille_idx < 3; taille_idx++){
        Taille taille = static_cast<Taille>(taille_idx);
        bool victoire = true;
        for(int i = 0; i < 3; i++){
            const Case& c = plateau.getCase(2 - i, i);
            bool found = false;
            for(const Cercle& cercle : c.getCercles()){
                if(cercle.getCouleur() == couleur && cercle.getTaille() == taille){
                    found = true;
                    break;
                }
            }
            if(!found){
                victoire = false;
                break;
            }
        }
        if(victoire) return true;
    }

    // Test de victoire dans une seule case (3 tailles différentes de la même couleur)
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            const Case& c = plateau.getCase(x, y);
            bool hasPetit = false;
            bool hasMoyen = false;
            bool hasGrand = false;
            
            for(const Cercle& cercle : c.getCercles()){
                if(cercle.getCouleur() == couleur){
                    if(cercle.getTaille() == Taille::Petit) hasPetit = true;
                    if(cercle.getTaille() == Taille::Moyen) hasMoyen = true;
                    if(cercle.getTaille() == Taille::Grand) hasGrand = true;
                }
            }
            
            if(hasPetit && hasMoyen && hasGrand){
                return true;
            }
        }
    }

    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}