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

    Couleur couleurJoueur = joueurs[joueurCourant].getCouleur();
    if(testerVictoire(couleurJoueur) || verifierFinDePartie()){
        std::cout << "Le joueur jsp quoi a gagné" << std::endl;
        return;
    }
    else lancerTourSuivant();
}

bool Jeu::testerVictoire(Couleur couleur){
    // Victoire Condition 1: Trois cercles de la même couleur en ligne (horizontale, verticale ou diagonale)
    // Victoire Condition 2: Trois cercles de la même couleur dans une même case (un de chaque taille)
    // Victoire Condition 3: Trois cercles alignés où les trois tailles sont représentées (peu importe la couleur)

    // Test Condition 1: Alignements (lignes, colonnes, diagonales)
    // Vérifier les lignes et colonnes
    for(int i = 0; i < 3; i++){
        // Vérifier ligne i
        int compteurLigne = 0;
        for(int j = 0; j < 3; j++){
            const Case& caseActuelle = plateau.getCase(i, j);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getCouleur() == couleur){
                    compteurLigne++;
                    break; // Un cercle de cette couleur dans cette case suffit
                }
            }
        }
        if(compteurLigne == 3) return true;

        // Vérifier colonne i
        int compteurColonne = 0;
        for(int j = 0; j < 3; j++){
            const Case& caseActuelle = plateau.getCase(j, i);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getCouleur() == couleur){
                    compteurColonne++;
                    break;
                }
            }
        }
        if(compteurColonne == 3) return true;
    }

    // Vérifier les diagonales
    int compteurDiag1 = 0;
    int compteurDiag2 = 0;
    for(int i = 0; i < 3; i++){
        // Diagonale principale (0,0) -> (1,1) -> (2,2)
        const Case& case1 = plateau.getCase(i, i);
        const std::vector<Cercle>& cercles1 = case1.getCercles();
        for(const auto& cercle : cercles1){
            if(cercle.getCouleur() == couleur){
                compteurDiag1++;
                break;
            }
        }

        // Diagonale secondaire (0,2) -> (1,1) -> (2,0)
        const Case& case2 = plateau.getCase(i, 2 - i);
        const std::vector<Cercle>& cercles2 = case2.getCercles();
        for(const auto& cercle : cercles2){
            if(cercle.getCouleur() == couleur){
                compteurDiag2++;
                break;
            }
        }
    }
    if(compteurDiag1 == 3 || compteurDiag2 == 3) return true;

    // Test Condition 2: Trois cercles de même couleur dans une même case
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            const Case& caseActuelle = plateau.getCase(i, j);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            
            bool aPetit = false, aMoyen = false, aGrand = false;
            for(const auto& cercle : cercles){
                if(cercle.getCouleur() == couleur){
                    if(cercle.getTaille() == Taille::Petit) aPetit = true;
                    if(cercle.getTaille() == Taille::Moyen) aMoyen = true;
                    if(cercle.getTaille() == Taille::Grand) aGrand = true;
                }
            }
            if(aPetit && aMoyen && aGrand) return true;
        }
    }

    // Test Condition 3: Trois cercles en ligne avec les trois tailles différentes
    // Vérifier les lignes
    for(int i = 0; i < 3; i++){
        bool aPetit = false, aMoyen = false, aGrand = false;
        for(int j = 0; j < 3; j++){
            const Case& caseActuelle = plateau.getCase(i, j);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getTaille() == Taille::Petit) aPetit = true;
                if(cercle.getTaille() == Taille::Moyen) aMoyen = true;
                if(cercle.getTaille() == Taille::Grand) aGrand = true;
            }
        }
        if(aPetit && aMoyen && aGrand) return true;
    }

    // Vérifier les colonnes
    for(int i = 0; i < 3; i++){
        bool aPetit = false, aMoyen = false, aGrand = false;
        for(int j = 0; j < 3; j++){
            const Case& caseActuelle = plateau.getCase(j, i);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getTaille() == Taille::Petit) aPetit = true;
                if(cercle.getTaille() == Taille::Moyen) aMoyen = true;
                if(cercle.getTaille() == Taille::Grand) aGrand = true;
            }
        }
        if(aPetit && aMoyen && aGrand) return true;
    }

    // Vérifier diagonale principale
    {
        bool aPetit = false, aMoyen = false, aGrand = false;
        for(int i = 0; i < 3; i++){
            const Case& caseActuelle = plateau.getCase(i, i);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getTaille() == Taille::Petit) aPetit = true;
                if(cercle.getTaille() == Taille::Moyen) aMoyen = true;
                if(cercle.getTaille() == Taille::Grand) aGrand = true;
            }
        }
        if(aPetit && aMoyen && aGrand) return true;
    }

    // Vérifier diagonale secondaire
    {
        bool aPetit = false, aMoyen = false, aGrand = false;
        for(int i = 0; i < 3; i++){
            const Case& caseActuelle = plateau.getCase(i, 2 - i);
            const std::vector<Cercle>& cercles = caseActuelle.getCercles();
            for(const auto& cercle : cercles){
                if(cercle.getTaille() == Taille::Petit) aPetit = true;
                if(cercle.getTaille() == Taille::Moyen) aMoyen = true;
                if(cercle.getTaille() == Taille::Grand) aGrand = true;
            }
        }
        if(aPetit && aMoyen && aGrand) return true;
    }

    return false;
}

bool Jeu::verifierFinDePartie(){
    // TODO: implémenter la logique de vérification de fin de partie
    return false;
}