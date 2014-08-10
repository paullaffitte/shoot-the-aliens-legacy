#include <SFML/System.hpp>
#include <iostream>
#include "gameengine.h"
#include "jeu.h"

//PROJET DEBUTE LE 20 FEVRIER 2014
int main()
{
    srand(time(NULL));
    GameEngine shootTheAliens;
	shootTheAliens.Init("Shoot The Aliens", 400, 700);
	//shootTheAliens.getFenetre()->setMouseCursorVisible(false);
    shootTheAliens.getFenetre()->setFramerateLimit(60);
    shootTheAliens.getFenetre()->setVerticalSyncEnabled(true);
	shootTheAliens.ChangeState(Jeu::Instance());
    sf::Image icon;
    icon.loadFromFile("ressources/images/64x64.png");
    shootTheAliens.getFenetre()->setIcon(64,64,icon.getPixelsPtr());

	//Boucle principale
	while(shootTheAliens.Running())
	{
		shootTheAliens.HandleEvents();
		shootTheAliens.Update();
		shootTheAliens.Draw();
	}

	//On nettoie l'engine
	shootTheAliens.Cleanup();
    return 0;
}


/*
RESTE A FAIRE :
ALPHA :
+ Vaisseau joueur
+ Scores
+ Permettre le redimensionnement
+ Fond
+ Explosions
+ Fluidifier les déplacements
+ Un seul chronomètre
+ Pause
+ Graphismes
+ Animations
+ Bruitages :
    + Explosions
    + Tirs
    + Réacteurs :
        + Avancer
        + Strafe
    + Ambiance d'espace

+ Musique
+ Screenshots
BETA :
- Detection des mises à jour
- Ajouter un curseur
- Multi-threading
- Réglages volume
/ Historique des scores
- Bruitages améliorés :
    - Bruitages générés aléatoirement à partir de la fusion des bruitages de base
    - Prise en compte de la distance
    - Prise en compte du positionnement relatif (droite/gauche)
- Accélération du fond lors de l'accélération des vaisseaux
- Intro
- Modes de jeu : Chaqu'un accessibles indépendamment ou simultanéments (cases à cocher)
    + Normal (gratuit)
    - Bouclier (payant) : Bouclier disponible pour une durée limitée, chaque kill rajoutent de l'énergie au bouclier (ou tout les x kills)
    - Assassin (payant) : Cooldown de game over remis à zéro par un kill
    - Infinite Runner (payant) : Reprend la partie à 80% de la progression précédente (comprend les 3 modes de jeu précédents)
- Optimisations
*/
