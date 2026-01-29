#include "Jeu.hpp"
#include <string>

Jeu::Jeu(){
    joueurs = std::vector<Joueur*>();
    plateau = Plateau();
}

int Jeu::getVersion(){
    return version;
}

void Jeu::ajouterJoueurHumain(const std::string& nom, Couleur couleur){
    Joueur* joueur = new Humain(nom, couleur);
    joueurs.push_back(joueur);
}

void Jeu::ajouterJoueurMachine(const std::string& nom, Couleur couleur){
    // TODO: À implémenter plus tard quand Machine sera défini
    (void)nom; // Suppress unused parameter warning
    (void)couleur; // Suppress unused parameter warning
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

    // Get current player's color
    Couleur couleurJoueurCourant = joueurs[joueurCourant]->getCouleur();
    
    if(testerVictoire(couleurJoueurCourant) || verifierFinDePartie()){
        std::cout << "Le joueur jsp quoi a gagné" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Check rows for victory
    for(int y = 0; y < 3; y++){
        bool victoire = true;
        for(int x = 0; x < 3; x++){
            const Case& currentCase = plateau.getCase(x, y);
            const std::vector<Cercle>& cercles = currentCase.getCercles();
            
            bool hasCouleur = false;
            for(const auto& cercle : cercles){
                if(cercle.getCouleur() == couleur){
                    hasCouleur = true;
                    break;
                }
            }
            
            if(!hasCouleur){
                victoire = false;
                break;
            }
        }
        if(victoire) return true;
    }
    
    // Check columns for victory
    for(int x = 0; x < 3; x++){
        bool victoire = true;
        for(int y = 0; y < 3; y++){
            const Case& currentCase = plateau.getCase(x, y);
            const std::vector<Cercle>& cercles = currentCase.getCercles();
            
            bool hasCouleur = false;
            for(const auto& cercle : cercles){
                if(cercle.getCouleur() == couleur){
                    hasCouleur = true;
                    break;
                }
            }
            
            if(!hasCouleur){
                victoire = false;
                break;
            }
        }
        if(victoire) return true;
    }
    
    // Check diagonal (top-left to bottom-right)
    bool victoire = true;
    for(int i = 0; i < 3; i++){
        const Case& currentCase = plateau.getCase(i, i);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        bool hasCouleur = false;
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == couleur){
                hasCouleur = true;
                break;
            }
        }
        
        if(!hasCouleur){
            victoire = false;
            break;
        }
    }
    if(victoire) return true;
    
    // Check diagonal (top-right to bottom-left)
    victoire = true;
    for(int i = 0; i < 3; i++){
        const Case& currentCase = plateau.getCase(2 - i, i);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        bool hasCouleur = false;
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == couleur){
                hasCouleur = true;
                break;
            }
        }
        
        if(!hasCouleur){
            victoire = false;
            break;
        }
    }
    if(victoire) return true;
    
    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}