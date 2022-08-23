#include <SFML/System.hpp>
#include <iostream>
#include "gameengine.h"
#include "jeu.h"

//PROJET DEBUTE LE 20 FEVRIER 2014
int main()
{
    srand(time(NULL));
    GameEngine shootTheAliens;
    Jeu jeu;
	shootTheAliens.Init("Shoot The Aliens", 400, 700);
	//shootTheAliens.getFenetre()->setMouseCursorVisible(false);
    shootTheAliens.getFenetre()->setFramerateLimit(60);
    shootTheAliens.getFenetre()->setVerticalSyncEnabled(true);
	shootTheAliens.ChangeState(&jeu);
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
+ Fluidifier les d�placements
+ Un seul chronom�tre
+ Pause
+ Graphismes
+ Animations
+ Bruitages :
    + Explosions
    + Tirs
    + R�acteurs :
        + Avancer
        + Strafe
    + Ambiance d'espace

+ Musique
+ Screenshots
BETA :
- Detection des mises � jour
- Ajouter un curseur
- Multi-threading
- R�glages volume
/ Historique des scores
- Bruitages am�lior�s :
    - Bruitages g�n�r�s al�atoirement � partir de la fusion des bruitages de base
    - Prise en compte de la distance
    - Prise en compte du positionnement relatif (droite/gauche)
- Acc�l�ration du fond lors de l'acc�l�ration des vaisseaux
- Intro
- Modes de jeu : Chaqu'un accessibles ind�pendamment ou simultan�ments (cases � cocher)
    + Normal (gratuit)
    - Bouclier (payant) : Bouclier disponible pour une dur�e limit�e, chaque kill rajoutent de l'�nergie au bouclier (ou tout les x kills)
    - Assassin (payant) : Cooldown de game over remis � z�ro par un kill
    - Infinite Runner (payant) : Reprend la partie � 80% de la progression pr�c�dente (comprend les 3 modes de jeu pr�c�dents)
- Optimisations
*/
