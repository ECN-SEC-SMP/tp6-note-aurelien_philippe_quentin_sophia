# TP noté 2 - Otrio

## Résumé du Projet
Implémentation du jeu Otrio avec 3 versions pour des joueurs humains et une intelligence artificielle basique. Le jeu se joue sur un plateau 3x3 avec des cercles de différentes tailles.

## Procédure de compilation et lancement
1) cd build && cmake --build .
2) ./tp6

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

### 5. Tests

Dossier `tests/` :
- fichier `testPlateau.cpp` qui teste l'affichage, le placement, l'empilement, conflits, zone hors plateau, cas du remplissage complet

---

## Architecture

### Diagramme de Classes
Voir [UML.md](UML.md) pour le diagramme complet des classes et leurs relations.

### Collaborations
- Lien Excalidraw (tableau interactif) : https://excalidraw.com/#room=ea663029a2f5d0156c9e,mXN1gxchhdujUEnQ5p9o7A

- Lien Mermaid (diagramme de classes) : https://mermaid.ai/app/projects/84b852e5-5100-4d66-8dab-02dbfe78b077/diagrams/d162bb1f-1ef2-4b2b-a193-4e41ef5dca2f/share/invite/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkb2N1bWVudElEIjoiZDE2MmJiMWYtMWVmMi00YjJiLWExOTMtNGU0MWVmNWRjYTJmIiwiYWNjZXNzIjoiVmlldyIsImlhdCI6MTc2ODkyMDU5NH0.GMzww-fmbTNQI7TzBGFAdZksDuhMCwJ5AlaOUCv2m84

---

## Organisation de l'Équipe

| Membre | Responsabilités | 
|--------|-----------------------------|
| **Aurélien** | Classe Jeu |
| **Philippe** | Joueurs : Classe joueur, classe humain |
| **Quentin** | Enums, classe Case, classe Cercle, classe Machine |
| **Sophia** | Programme principal (UI), classe Plateau |

### Répartition des Fichiers
- `Plateau.cpp/.hpp`, `testPlateau.cpp/.cpp`,`main.cpp` → Sophia
- `Jeu.cpp` → Aurélien
- `Joueur.cpp`, `Humain.cpp` → Philippe
- `Machine.cpp`, `Case.cpp/.hpp`, `Cercle.cpp/.hpp`, `Enums.h` → Quentin


