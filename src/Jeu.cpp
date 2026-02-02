#include "Jeu.hpp"
#include <string>

// Constructeur

Jeu::Jeu(){
    joueurs = std::vector<std::unique_ptr<Joueur>>();
    plateau = Plateau();
}
// Getter

int Jeu::getVersion(){
    return version;
}

// Méthodes

void Jeu::ajouterJoueurHumain(const std::string& nom, Couleur couleur){
    Humain joueur = Humain(nom, couleur);
    joueurs.push_back(std::make_unique<Humain>(nom, couleur));
}

void Jeu::ajouterJoueurMachine(const std::string& nom, Couleur couleur){
    joueurs.push_back(std::make_unique<Machine>(nom, couleur));
}

void Jeu::choisirVersion(){
    int version;
    std::cout << "Entrez une version du jeu (1 2 ou 3): ";
    std::cin >> version;
    if(version >= 1 && version <= 3){
        this->version = version;
        std::cout << "Version choisie : " << version << std::endl;
    } else {
        std::cout << "La version entrée n'est pas valide. Retentez (1 2 ou 3) : " <<std::endl;
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
        //int nbJoueurs;
        //int nbOrdinateurs;

        //nbJoueurs = entrerNombreJoueurs();

        //nbOrdinateurs = 4 - nbJoueurs;
        
        //for(int i = 0; i < nbJoueurs; i++){
            std::string nom;

            //std::cout << "Entrez le nom du joueur " << i+1 << " : ";
            std::cout << "Entrez le nom du joueur : ";
            std::cin >> nom;
            //ajouterJoueurHumain(nom, static_cast<Couleur>(i));
            ajouterJoueurHumain(nom, Couleur::Bleu);
        //}

        ajouterJoueurMachine("Otriotor", Couleur::Rouge);
        /* for(int j = 0; j < nbOrdinateurs; j ++){
            std::string nom = "Ordinateur_" + std::to_string(j+1);
            ajouterJoueurMachine(nom, static_cast<Couleur>(j + nbJoueurs));
        } */
    }
}

void Jeu::initialiser(){

    // Affichage !!!!!!!!!!!
    std::cout << "<========> Bienvenue dans le jeu Otrio <========>" << std::endl;

    // Choix de la version
    choisirVersion();

    // Entrée des joueurs
    entrerNomJoueurs();
}

void Jeu::lancerPartie(){

    // Début de la partie
    std::cout << "<========> Début de la partie <========>" << std::endl << std::endl;

    // Tirage 
    this->joueurCourant = rand() % joueurs.size();

    std::cout << "\033[32m" << "C'est " << joueurs[joueurCourant]->getNom() << " qui commence !" << "\033[0m" << std::endl;

    lancerTourSuivant();

    plateau.afficher();

    std::cout << "<========> Fin de la partie <========>" << std::endl << std::endl;
}

void Jeu::lancerTourSuivant(){
    std::pair<std::pair<int, int>, Cercle> action;
    bool testAction = false;

    plateau.afficher();

    // Demander action au joueur (humain ou machine)
    action = joueurs[joueurCourant]->deciderAction(plateau);

    // Tester compteur de cercle du joueur en fonction de l'action
    if((action.second.getTaille() == Taille::Petit) && (joueurs[joueurCourant]->getPetitCercle() > 0)){
        // Tenter de poser
        testAction = plateau.placerCercle(action.first.first, action.first.second, action.second);
    }
    else if((action.second.getTaille() == Taille::Moyen) && (joueurs[joueurCourant]->getMoyenCercle() > 0)){
        testAction = plateau.placerCercle(action.first.first, action.first.second, action.second);
    }
    else if((action.second.getTaille() == Taille::Grand) && (joueurs[joueurCourant]->getGrandCercle() > 0)){
        testAction = plateau.placerCercle(action.first.first, action.first.second, action.second);
    }
    else std::cout << "\033[31m" <<"Aucun cercle de cette taille à retirer pour le joueur " << joueurs[joueurCourant]->getNom() << "." << "\033[0m" << std::endl;
    
    if(testAction){
        // Quand l'action est validée on retire le cercle au joueur
        joueurs[joueurCourant]->retirerCercle(action.second.getTaille());
        if(testerVictoire(joueurs[joueurCourant]->getCouleur(), action)){
            std::cout << joueurs[joueurCourant]->getNom() << " a gagné !" << std::endl;
        }
        else {
            // Joueur suivant
            joueurCourant = (joueurCourant + 1) % joueurs.size();

            if(!verifierFinDePartie()){
                std::cout << "\033[32m" << "C'est au tour de " << joueurs[joueurCourant]->getNom() << "\033[0m" << std::endl;
                lancerTourSuivant();
            }
            else{
                std::cout << "\033[32m" << "Plus personne n'a de cercle, match nul !" << "\033[0m" << std::endl;
            }
        }
    }
    else {

        lancerTourSuivant();
    }
}


bool Jeu::testerVictoire(Couleur couleur, std::pair<std::pair<int, int>, Cercle> lastAction){  
    // Test superposition (3 cercles de meme couleur sur une case)
    Case caseTestee = plateau.getCase(lastAction.first.first, lastAction.first.second);
    int compteurCercles = 0;
    for(Cercle cercleCourant : caseTestee.getCercles()){
        if(cercleCourant.getCouleur() == couleur){
            compteurCercles++;
        }
    }
    if(compteurCercles == 3){
        return true;
    }

    // Test aligenement de trois cercles identiques en taille et couleur
    // Horizontal
    for(int y = 0; y < 3; y++){
        int cptCercle = 0;
        for(int x = 0; x < 3; x++){
            Case caseCourante = plateau.getCase(x,y);
            for(Cercle cercleCourant : caseCourante.getCercles()){
                if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == lastAction.second.getTaille()){
                    cptCercle++;
                    break;
                }
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Vertical
    for(int x = 0; x < 3; x++){
        int cptCercle = 0;
        for(int y = 0; y < 3; y++){
            Case caseCourante = plateau.getCase(x,y);
            for(Cercle cercleCourant : caseCourante.getCercles()){
                if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == lastAction.second.getTaille()){
                    cptCercle++;
                    break;
                }
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Diagonale
    int cptCercle = 0;
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == lastAction.second.getTaille()){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }
    
    // Diagonale 2
    cptCercle = 0; // reset cptCercle pour la diagonale 2
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, 2 - i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == lastAction.second.getTaille()){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }
    
    // Test suite du plus petit au plus grand de meme couleur en alignement
    // Horizontal
    // Commençant par un petit
    
    for(int x = 0; x < 3; x++){
        cptCercle = 0;
        Case case1 = plateau.getCase(x, 0);
        Case case2 = plateau.getCase(x, 1);
        Case case3 = plateau.getCase(x, 2);

        for(Cercle cercleCourant : case1.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Petit){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case2.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Moyen){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case3.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Grand){
                cptCercle++;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Et commençant par le plus grand

    for(int x = 0; x < 3; x++){
        cptCercle = 0;
        Case case1 = plateau.getCase(x, 0);
        Case case2 = plateau.getCase(x, 1);
        Case case3 = plateau.getCase(x, 2);

        for(Cercle cercleCourant : case1.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Grand){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case2.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Moyen){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case3.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Petit){
                cptCercle++;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Vertical
    // Commençant par un petit
    
    for(int y = 0; y < 3; y++){
        cptCercle = 0;
        Case case1 = plateau.getCase(0, y);
        Case case2 = plateau.getCase(1, y);
        Case case3 = plateau.getCase(2, y);

        for(Cercle cercleCourant : case1.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Petit){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case2.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Moyen){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case3.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Grand){
                cptCercle++;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Et commençant par le plus grand

    for(int y = 0; y < 3; y++){
        cptCercle = 0;
        Case case1 = plateau.getCase(0, y);
        Case case2 = plateau.getCase(1, y);
        Case case3 = plateau.getCase(2, y);

        for(Cercle cercleCourant : case1.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Grand){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case2.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Moyen){
                cptCercle++;
            }
        }
        for(Cercle cercleCourant : case3.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == Taille::Petit){
                cptCercle++;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Diagonales
    cptCercle = 0;
    Case centre = plateau.getCase(1, 1);
    Case angle1 = plateau.getCase(0,0);
    Case angle2 = plateau.getCase(2,0);
    Case angle3 = plateau.getCase(0,2);
    Case angle4 = plateau.getCase(2,2);
    for(int i = 0; i < 3; i++){
        
    }

    // Diagonale1 petit -> Grand
    cptCercle = 0;
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == static_cast<Taille>(i + 1)){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Diagonale1 Grand -> petit
    cptCercle = 0;
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == static_cast<Taille>(3 - i)){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Diagonale2 petit -> Grand
    cptCercle = 0;
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, 2-i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == static_cast<Taille>(i + 1)){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    // Diagonale2 Grand -> petit
    cptCercle = 0;
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, 2-i);
        for(Cercle cercleCourant : caseCourante.getCercles()){
            if(cercleCourant.getCouleur() == couleur && cercleCourant.getTaille() == static_cast<Taille>(3 - i)){
                cptCercle++;
                break;
            }
        }
        if(cptCercle == 3){
            return true;
        }
    }

    return false;
}

bool Jeu::verifierFinDePartie(){
    if((joueurs[joueurCourant]->getGrandCercle() == 0) && (joueurs[joueurCourant]->getMoyenCercle() == 0) && (joueurs[joueurCourant]->getPetitCercle() == 0)){
        // Le joueur qui doit jouer n'a plus de cercle donc la partie est finie
        return true;
    }
    return false;
}