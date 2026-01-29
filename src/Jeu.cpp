#include "Jeu.hpp"
#include <string>

// Constructeur

Jeu::Jeu(){
    joueurs = std::vector<Joueur>();
    plateau = Plateau();
}
// Getter

int Jeu::getVersion(){
    return version;
}

// Méthodes

void Jeu::ajouterJoueurHumain(const std::string& nom, Couleur couleur){
    Humain joueur = Humain(nom, couleur);
    joueurs.push_back(joueur);
}

// void Jeu::ajouterJoueurMachine(const std::string, Couleur couleur){
//     // À implémenter plus tard
// }

void Jeu::choisirVersion(){
    int version;
    std::cout << "Entrez une version du jeu (1 2 ou 3): ";
    std::cin >> version;
    if(version >= 1 && version <= 3){
        this->version = version;
    } else {
        std::cout << "La version entrée n'est pas valide. Retentez (1 2 ou 3) : ";
        choisirVersion();
    }
}

int Jeu::entrerNombreJoueurs(){
    int nombreJoueurs;
    std::cout << "Entrez le nombre de joueurs (0 à 3) : ";
    std::cin >> nombreJoueurs;

    if(nombreJoueurs < 0 && nombreJoueurs > 3){
        std::cout << "Le nombre de joueurs entré n'est pas valide. Retentez (0 1 2 ou 3): ";
        entrerNombreJoueurs();
    }
    return nombreJoueurs;  
}

void Jeu::entrerNomJoueurs(){

    if(this->getVersion() == 1){
        // Version 1

        for(int i = 0; i < 4; i++){
            std::string nom;

            std::cout << "Entrez le nom du joueur " << i+1 << " : ";
            std::cin >> nom;
            ajouterJoueurHumain(nom, static_cast<Couleur>(i));
        }
    }
    else if(this->getVersion() == 2){
        // Version 2

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
        // Sinon, version 3
        int nbJoueurs;
        int nbOrdinateurs;

        nbJoueurs = entrerNombreJoueurs();

        nbOrdinateurs = 4 - nbJoueurs;
        
        for(int i = 0; i < nbJoueurs; i++){
            std::string nom;

            std::cout << "Entrez le nom du joueur " << i+1 << " : ";
            std::cin >> nom;
            ajouterJoueurHumain(nom, static_cast<Couleur>(i));
        }

        for(int j = 0; j < nbOrdinateurs; j ++){
            std::string nom = "Ordinateur_" + std::to_string(j+1);
            // ajouterJoueurMachine(nom, static_cast<Couleur>(j + nbJoueurs));
        }
    }
}

void Jeu::initialiser(){

    // Affichage !!!!!!!!!!!
    std::cout << "<========> Bienvenue dans le jeu Otrio <========>" << std::endl;

    // Choix de la version
    choisirVersion();

    // Entrée des joueurs
    entrerNomJoueurs();

    // Démarrer la partie
    lancerPartie();
}

void Jeu::lancerPartie(){

    // Début de la partie
    std::cout << "<========> Début de la partie <========>" << std::endl;

    // Tirage 
    this->joueurCourant = rand() % joueurs.size();

    std::cout << "C'est " << joueurs[joueurCourant].getNom() << " qui commence !" << std::endl;

    lancerTourSuivant();

    std::cout << "<========> Fin de la partie <========>" << std::endl;
}

void Jeu::lancerTourSuivant(){
    std::string action;
    // Demander action au joueur courant
    // action = joueurs[joueurCourant].deciderAction(plateau);

    // tester si le joueur a le cercle qu'il a décidé

    // plateau.placerCercle();

    if(testerVictoire(joueurs[joueurCourant].getCouleur())){
        std::cout << joueurs[joueurCourant].getNom() << "a gagné !" << std::endl;
    }
    else {
        // Joueur suivant
        joueurCourant = (joueurCourant + 1) % 4;

        if(!verifierFinDePartie()){
            std::cout << "C'est au tour de " << joueurs[joueurCourant].getNom() << std::endl;
            lancerTourSuivant();
        }
        else{
            std::cout << "Plus personne n'a de cercle, match nul !" << std::endl;
        }
    }
}

bool Jeu::testerVictoire(Couleur couleur){  
    bool test = false;

    // A implétmenter

    return test;
}

bool Jeu::verifierFinDePartie(){
    if((joueurs[joueurCourant].getGrandCercle() == 0) && (joueurs[joueurCourant].getMoyenCercle() == 0) && (joueurs[joueurCourant].getPetitCercle() == 0)){
        // Le joueur qui doit jouer n'a plus de cercle donc la partie est finie
        return true;
    }
    return false;
}