# TP noté 2 - Otrio

## Résumé du Projet
Implémentation du jeu Otrio avec 3 versions pour des joueurs humains et une intelligence artificielle basique. Le jeu se joue sur un plateau 3x3 avec des cercles de différentes tailles.

## Procédure de compilation et lancement
1) mkdir build
2) cd build
3) cmake ..
4) cmake --build .
5) ./unittests 
6) ./tp6


---

## Parties du Rendu

### 1. Spécifications du Modèle de Données
- **Case** : Représente une cellule du plateau (contient des cercles)
- **Cercle** : Élément de jeu avec taille et couleur
- **Enums** : Énumérations pour les états et paramètres du jeu

### 2. Système de Jeu
- **Plateau** : Gestion de la grille 3x3, vérification des victoires
- **Joueur** : Classe parent pour humain et machine
  - **Humain** : Joueur contrôlé par l'utilisateur
  - **Machine** : Joueur contrôlé par IA
- **Jeu** : Orchestration globale du jeu, gestion des tours

### 3. Interface & Interactivité
- **main.cpp** : Point d'entrée du programme
- Gestion des entrées utilisateur et affichage du plateau

### 4. Documentation Technique
- **CMakeLists.txt** : Configuration de compilation
- **UML.md** : Diagramme des classes
- **README.md** : Rapport de TP

---

## Architecture

### Diagramme de Classes
Voir [UML.md](UML.md) pour le diagramme complet des classes et leurs relations

### Collaborations
- Lien Mermaid (diagramme de classes) : https://mermaid.ai/app/projects/84b852e5-5100-4d66-8dab-02dbfe78b077/diagrams/d162bb1f-1ef2-4b2b-a193-4e41ef5dca2f/share/invite/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkb2N1bWVudElEIjoiZDE2MmJiMWYtMWVmMi00YjJiLWExOTMtNGU0MWVmNWRjYTJmIiwiYWNjZXNzIjoiVmlldyIsImlhdCI6MTc2ODkyMDU5NH0.GMzww-fmbTNQI7TzBGFAdZksDuhMCwJ5AlaOUCv2m84

---

## Organisation de l'Équipe

- L'organisation initiale est décrite ci-dessous. Toutefois, un retard global dans l'avancement du projet a modifié ces plans, les membres réalisant des fonctions de supports divers.

| Membre | Responsabilités | 
|--------|-----------------------------|
| **Aurélien** | Classe Jeu |
| **Philippe** | Joueurs : Classe joueur, classe humain, GTests |
| **Quentin** | Enums, classe Case, classe Cercle, Machine "testerMenaceImminente" |
| **Sophia** | classe Plateau, Machine "deciderAction", tests unitaires|

### Répartition des Fichiers
- `Plateau.cpp/.hpp`, `Machine.cpp`, `main.cpp`, `/tests` → Sophia
- `Jeu.cpp` → Aurélien
- `Joueur.cpp`, `Humain.cpp` → Philippe
- `Machine.cpp`, `Case.cpp/.hpp`, `Cercle.cpp/.hpp`, `Enums.h` → Quentin

