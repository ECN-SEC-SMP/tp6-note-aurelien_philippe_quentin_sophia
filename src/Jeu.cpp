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
    // Victoire type 1: Trois cercles de même couleur en ligne (horizontale, verticale ou diagonale)
    // avec au moins un cercle de chaque taille visible (petit, moyen, grand) sur les 3 cases
    
    // Vérification des lignes horizontales
    for(int y = 0; y < 3; y++){
        bool petitTrouve = false, moyenTrouve = false, grandTrouve = false;
        bool ligneCouleurOK = true;
        
        for(int x = 0; x < 3; x++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            bool caseCouleurOK = false;
            
            for(const Cercle& c : cercles){
                if(c.getCouleur() == couleur){
                    caseCouleurOK = true;
                    if(c.getTaille() == Taille::Petit) petitTrouve = true;
                    if(c.getTaille() == Taille::Moyen) moyenTrouve = true;
                    if(c.getTaille() == Taille::Grand) grandTrouve = true;
                }
            }
            
            if(!caseCouleurOK){
                ligneCouleurOK = false;
                break;
            }
        }
        
        if(ligneCouleurOK && petitTrouve && moyenTrouve && grandTrouve){
            return true;
        }
    }
    
    // Vérification des colonnes verticales
    for(int x = 0; x < 3; x++){
        bool petitTrouve = false, moyenTrouve = false, grandTrouve = false;
        bool colonneCouleurOK = true;
        
        for(int y = 0; y < 3; y++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            bool caseCouleurOK = false;
            
            for(const Cercle& c : cercles){
                if(c.getCouleur() == couleur){
                    caseCouleurOK = true;
                    if(c.getTaille() == Taille::Petit) petitTrouve = true;
                    if(c.getTaille() == Taille::Moyen) moyenTrouve = true;
                    if(c.getTaille() == Taille::Grand) grandTrouve = true;
                }
            }
            
            if(!caseCouleurOK){
                colonneCouleurOK = false;
                break;
            }
        }
        
        if(colonneCouleurOK && petitTrouve && moyenTrouve && grandTrouve){
            return true;
        }
    }
    
    // Vérification de la diagonale descendante (top-left à bottom-right)
    {
        bool petitTrouve = false, moyenTrouve = false, grandTrouve = false;
        bool diagonaleCouleurOK = true;
        
        for(int i = 0; i < 3; i++){
            const std::vector<Cercle>& cercles = plateau.getCase(i, i).getCercles();
            bool caseCouleurOK = false;
            
            for(const Cercle& c : cercles){
                if(c.getCouleur() == couleur){
                    caseCouleurOK = true;
                    if(c.getTaille() == Taille::Petit) petitTrouve = true;
                    if(c.getTaille() == Taille::Moyen) moyenTrouve = true;
                    if(c.getTaille() == Taille::Grand) grandTrouve = true;
                }
            }
            
            if(!caseCouleurOK){
                diagonaleCouleurOK = false;
                break;
            }
        }
        
        if(diagonaleCouleurOK && petitTrouve && moyenTrouve && grandTrouve){
            return true;
        }
    }
    
    // Vérification de la diagonale ascendante (bottom-left à top-right)
    {
        bool petitTrouve = false, moyenTrouve = false, grandTrouve = false;
        bool diagonaleCouleurOK = true;
        
        for(int i = 0; i < 3; i++){
            const std::vector<Cercle>& cercles = plateau.getCase(i, 2 - i).getCercles();
            bool caseCouleurOK = false;
            
            for(const Cercle& c : cercles){
                if(c.getCouleur() == couleur){
                    caseCouleurOK = true;
                    if(c.getTaille() == Taille::Petit) petitTrouve = true;
                    if(c.getTaille() == Taille::Moyen) moyenTrouve = true;
                    if(c.getTaille() == Taille::Grand) grandTrouve = true;
                }
            }
            
            if(!caseCouleurOK){
                diagonaleCouleurOK = false;
                break;
            }
        }
        
        if(diagonaleCouleurOK && petitTrouve && moyenTrouve && grandTrouve){
            return true;
        }
    }
    
    // Victoire type 2: Trois cercles de même couleur et taille croissante dans une même case
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            bool petitTrouve = false, moyenTrouve = false, grandTrouve = false;
            
            for(const Cercle& c : cercles){
                if(c.getCouleur() == couleur){
                    if(c.getTaille() == Taille::Petit) petitTrouve = true;
                    if(c.getTaille() == Taille::Moyen) moyenTrouve = true;
                    if(c.getTaille() == Taille::Grand) grandTrouve = true;
                }
            }
            
            if(petitTrouve && moyenTrouve && grandTrouve){
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