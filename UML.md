classDiagram
    %% Relations
    Jeu *-- "1" Plateau : Contient
    Jeu *-- "2..4" Joueur : Gere
    Plateau *-- "9" Case : Compose de
    Case o-- "0..3" Cercle : Contient 
    Joueur <|-- Machine
    Joueur <|-- Humain

    %% Classes
    class Jeu {
      -int version
      -List~Joueur~ joueurs
      -Plateau plateau
      +Jeu()
      +initialiser()
      +lancerPartie()
      +tourSuivant()
      +demanderAction(Joueur j)
      +verifierFinDePartie() bool
    }

    class Plateau {
      -Case[3][3] grille
      +placerCercle(x: int, y: int, c: Cercle) bool
      +afficher() void
      +verifierVictoire(couleur: Couleur) bool
    }

    class Joueur {
      -Couleur couleur
      -string nom
      -int petitCercle
      -int moyenCercle
      -int grandCercle
      +Joueur(nom, couleur)
      +retirerCercle(taille) Cercle
      +aDesCercles() bool
    }

    class Case {
      %% Struct
      -List~Cercle~ contenu
      +peutAccueillir(Taille t) bool
      +ajouter(Cercle c) void
      +estPleine() bool
    }

    class Cercle {
      %% Struct
      -Taille taille
      -Couleur couleur
    }

    class Humain {
      +void testerMenance()
      +void deciderAction()
    }


    %% Definitions des Enums 
    class Couleur {
      <<enumeration>>
      ROUGE
      VERT
      BLEU
      VIOLET
    }
    
    class Taille {
      <<enumeration>>
      PETIT
      MOYEN
      GRAND
    }
