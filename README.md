# Cluedo Project ING2 2021
Maxence Thomine - Victor Simorre - Candice Legay

## Description

Dans le cadre de notre 2ème année en école d'ingénieurs à l'ECE Paris, notre projet en informatique se concentre sur le développement d'une version informatique du Cluedo, plongeant les joueurs dans l'univers magique d'Harry Potter. Ce projet ambitieux n'est pas seulement une réinvention du jeu classique en C++, mais il sert également de terrain d'application pratique pour l'usage avancé de concepts de programmation orientée objet, notamment les classes et les classes abstraites.

## Architecture

L'architecture du jeu est soigneusement conçue autour de plusieurs classes qui modélisent les différents aspects du Cluedo : les personnages, avec des héros emblématiques de la saga Harry Potter, les lieux mystérieux de Poudlard et d'autres sites emblématiques du monde des sorciers, ainsi que les énigmes et sortilèges qui enrichissent le gameplay. Chaque élément du jeu est représenté par une classe distincte, permettant une gestion claire et une évolutivité du code.

## Scénario du jeu

Les joueurs doivent résoudre le meurtre du Dobby en découvrant :

- **Suspect** : Qui a commis le meurtre ?
- **Lieu** : Dans quelle pièce du manoir le meurtre a-t-il eu lieu ?
- **Arme** : Quelle arme a été utilisée ?

### Déroulement du jeu

- Les joueurs se déplacent dans le manoir en lançant un dé.
- Lorsqu'un joueur entre dans une pièce, il peut faire une hypothèse sur le meurtre.
- Les autres joueurs doivent fournir des alibis en montrant des cartes.

### Fin du jeu

- Lorsqu'un joueur pense avoir trouvé les trois éléments (suspect, lieu, arme), il fait une accusation.
- Si l'accusation est correcte, le jeu se termine ; sinon, le joueur est éliminé.

## Cahier des charges

Le projet respecte les éléments suivants :

- Création d'un plateau de jeu avec des lieux.
- Création de cartes pour les suspects, les armes et les lieux.
- Gestion des joueurs et de leurs cartes.
- Enregistrement des matchs en cours pour une reprise ultérieure.
- Possibilité de jouer contre des adversaires virtuels.

## Installation

Télécharger une version d'allegro *[ici](https://liballeg.org/old.html)*.

## Getting Started

Nous vous recommandons d'utiliser CodeBlocks comme environnement de développement principal. Voici un bref guide sur la façon de configurer le projet :

Ouvrir le projet dans CodeBlocks :

1. Lancez CodeBlocks.
2. Accédez au menu "Fichier" et sélectionnez "Ouvrir un dossier".
3. Localisez et sélectionnez le répertoire racine du projet Cluedo pour l'ouvrir dans CodeBlocks.
4. Allez dans **"Project" > "Build options..."** pour ouvrir les options de compilation.

Sous l'onglet **"Search directories"**, ajoutez les chemins vers les en-têtes (headers) d'Allegro dans **"Compiler"**. Vous devez pointer vers le dossier qui contient les fichiers d'en-tête d'Allegro (généralement <chemin_vers_allegro>/include).

Dans l'onglet **"Linker"**, ajoutez les chemins vers les bibliothèques Allegro. Pointez vers le dossier contenant les fichiers de bibliothèque d'Allegro (généralement <chemin_vers_allegro>/lib).

5. Une fois que le dossier du projet est ouvert dans CodeBlocks, cliquer sur **Build and Run** pour lancer le projet.

## Vidéo

Vous pouvez retrouver notre vidéo de présentation de notre Cluedo avec ce lien  : *Voir la video*

## Usages

Ce projet ne s'adapte que sur Ordinateur avec taille d'écran 1920 x 1080 pixels.

## Bibliothèque

- Time.h
- Thread
- Chrono
- Fstream
