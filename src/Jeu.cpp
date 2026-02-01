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

// void Jeu::ajouterJoueurMachine(const std::string& nom, Couleur couleur){
//     Machine machine = Machine(nom, couleur);
//     joueurs.push_back(std::make_unique<Machine>(nom, couleur));
// }

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

    std::cout << "C'est " << joueurs[joueurCourant]->getNom() << " qui commence !" << std::endl;

    lancerTourSuivant();

    std::cout << "<========> Fin de la partie <========>" << std::endl;
}

void Jeu::lancerTourSuivant(){
    std::pair<std::pair<int, int>, Cercle> action;
    bool testAction = false;

    plateau.afficher();

    // Demander action au joueur courant    
    //action = joueurs[joueurCourant]->deciderAction(plateau);

    // while(testAction){
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
    // }
    if(testAction){
        // Quand l'action est validée on retire le cercle au joueur
        joueurs[joueurCourant]->retirerCercle(action.second.getTaille());
        if(testerVictoire(joueurs[joueurCourant]->getCouleur(), action)){
            std::cout << joueurs[joueurCourant]->getNom() << " a gagné !" << std::endl;
        }
        else {
            // Joueur suivant
            joueurCourant = (joueurCourant + 1) % 4;

            if(!verifierFinDePartie()){
                std::cout << "C'est au tour de " << joueurs[joueurCourant]->getNom() << std::endl;
                lancerTourSuivant();
            }
            else{
                std::cout << "Plus personne n'a de cercle, match nul !" << std::endl;
            }
        }
    }
    else {
        // Redemande un choix au joueur courant
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
    for(int i = 0; i < 3; i++){
        int cptCercle = 0;
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
    
    for(int i = 0; i < 3; i++){
        Case caseCourante = plateau.getCase(i, 2 - i);
        int cptCercle = 0;
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
    // Vertical
    // Diagonal

    return false;
}

bool Jeu::verifierFinDePartie(){
    if((joueurs[joueurCourant]->getGrandCercle() == 0) && (joueurs[joueurCourant]->getMoyenCercle() == 0) && (joueurs[joueurCourant]->getPetitCercle() == 0)){
        // Le joueur qui doit jouer n'a plus de cercle donc la partie est finie
        return true;
    }
    return false;
}