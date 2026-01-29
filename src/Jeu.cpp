#include "Jeu.hpp"
#include <string>

Jeu::Jeu(){
    joueurs = std::vector<std::unique_ptr<Joueur>>();
    plateau = Plateau();
}

int Jeu::getVersion(){
    return version;
}

void Jeu::ajouterJoueurHumain(const std::string& nom, Couleur couleur){
    joueurs.push_back(std::make_unique<Humain>(nom, couleur));
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
    // Helper lambda to check if a cell has the given color
    auto caseHasCouleur = [&](int x, int y) -> bool {
        const Case& currentCase = plateau.getCase(x, y);
        const std::vector<Cercle>& cercles = currentCase.getCercles();
        
        for(const auto& cercle : cercles){
            if(cercle.getCouleur() == couleur){
                return true;
            }
        }
        return false;
    };
    
    // Check rows for victory
    for(int y = 0; y < 3; y++){
        if(caseHasCouleur(0, y) && caseHasCouleur(1, y) && caseHasCouleur(2, y)){
            return true;
        }
    }
    
    // Check columns for victory
    for(int x = 0; x < 3; x++){
        if(caseHasCouleur(x, 0) && caseHasCouleur(x, 1) && caseHasCouleur(x, 2)){
            return true;
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    if(caseHasCouleur(0, 0) && caseHasCouleur(1, 1) && caseHasCouleur(2, 2)){
        return true;
    }
    
    // Check diagonal (top-right to bottom-left)
    if(caseHasCouleur(2, 0) && caseHasCouleur(1, 1) && caseHasCouleur(0, 2)){
        return true;
    }
    
    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}