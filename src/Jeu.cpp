#include "Jeu.hpp"
#include <string>
#include <memory>

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
    joueurs.push_back(std::make_unique<Machine>(nom, couleur));
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

    if(testerVictoire(joueurs[joueurCourant]->getCouleur())){
        std::cout << "Le joueur " << joueurs[joueurCourant]->getNom() << " a gagné !" << std::endl;
        return;
    }
    
    if(verifierFinDePartie()){
        std::cout << "Fin de partie" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Vérifier les lignes (horizontales)
    for(int y = 0; y < 3; y++){
        // Vérifier si 3 cercles de la même couleur sont alignés en ligne
        int count = 0;
        for(int x = 0; x < 3; x++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur){
                    count++;
                    break; // Un seul cercle de cette couleur par case suffit
                }
            }
        }
        if(count == 3) return true;
    }
    
    // Vérifier les colonnes (verticales)
    for(int x = 0; x < 3; x++){
        int count = 0;
        for(int y = 0; y < 3; y++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur){
                    count++;
                    break;
                }
            }
        }
        if(count == 3) return true;
    }
    
    // Vérifier la diagonale principale (haut-gauche à bas-droite)
    int countDiag1 = 0;
    for(int i = 0; i < 3; i++){
        const std::vector<Cercle>& cercles = plateau.getCase(i, i).getCercles();
        for(const auto& c : cercles){
            if(c.getCouleur() == couleur){
                countDiag1++;
                break;
            }
        }
    }
    if(countDiag1 == 3) return true;
    
    // Vérifier la diagonale inverse (haut-droite à bas-gauche)
    int countDiag2 = 0;
    for(int i = 0; i < 3; i++){
        const std::vector<Cercle>& cercles = plateau.getCase(2-i, i).getCercles();
        for(const auto& c : cercles){
            if(c.getCouleur() == couleur){
                countDiag2++;
                break;
            }
        }
    }
    if(countDiag2 == 3) return true;
    
    // Vérifier les 3 tailles dans une même case (Petit, Moyen, Grand de même couleur)
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
            bool aPetit = false, aMoyen = false, aGrand = false;
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur){
                    if(c.getTaille() == Taille::Petit) aPetit = true;
                    if(c.getTaille() == Taille::Moyen) aMoyen = true;
                    if(c.getTaille() == Taille::Grand) aGrand = true;
                }
            }
            if(aPetit && aMoyen && aGrand) return true;
        }
    }
    
    // Vérifier les lignes avec 3 cercles de même taille
    for(Taille taille : {Taille::Petit, Taille::Moyen, Taille::Grand}){
        // Lignes horizontales
        for(int y = 0; y < 3; y++){
            int count = 0;
            for(int x = 0; x < 3; x++){
                const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
                for(const auto& c : cercles){
                    if(c.getCouleur() == couleur && c.getTaille() == taille){
                        count++;
                        break;
                    }
                }
            }
            if(count == 3) return true;
        }
        
        // Colonnes verticales
        for(int x = 0; x < 3; x++){
            int count = 0;
            for(int y = 0; y < 3; y++){
                const std::vector<Cercle>& cercles = plateau.getCase(x, y).getCercles();
                for(const auto& c : cercles){
                    if(c.getCouleur() == couleur && c.getTaille() == taille){
                        count++;
                        break;
                    }
                }
            }
            if(count == 3) return true;
        }
        
        // Diagonale principale
        int countDiag1 = 0;
        for(int i = 0; i < 3; i++){
            const std::vector<Cercle>& cercles = plateau.getCase(i, i).getCercles();
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur && c.getTaille() == taille){
                    countDiag1++;
                    break;
                }
            }
        }
        if(countDiag1 == 3) return true;
        
        // Diagonale inverse
        int countDiag2 = 0;
        for(int i = 0; i < 3; i++){
            const std::vector<Cercle>& cercles = plateau.getCase(2-i, i).getCercles();
            for(const auto& c : cercles){
                if(c.getCouleur() == couleur && c.getTaille() == taille){
                    countDiag2++;
                    break;
                }
            }
        }
        if(countDiag2 == 3) return true;
    }
    
    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}