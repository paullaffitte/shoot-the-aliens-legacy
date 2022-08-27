#ifndef MENU_H
#define JEU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "gameengine.h"
#include "gamestate.h"
#include "joueur.h"
#include "alien.h"
#include "tir.h"
#include "explosion.h"
#include "fond.h"
#include "soundmanager.h"


class Jeu : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameEngine* shootTheAliens);
	void Update(GameEngine* shootTheAliens);
	void Draw(GameEngine* shootTheAliens);

	void EventFenetre();

private:
	sf::View m_vuePrincipale;
	sf::Vector2u m_dimensionsFenetre;
	sf::Vector2u m_dimensionsJeu;
	int m_score;
    int m_scoreFinal;
    int m_highscore;
    bool m_finPartie;

    sf::Font m_police;
    sf::Text m_start;
    sf::Text m_texteScore;
    sf::Text m_texteScorePrecedent;
    sf::Text m_texteHighscore;
    sf::Text m_version;
    sf::Text m_textePause;
    sf::FloatRect m_rectangle;

    bool m_chargementFini;
    bool m_dansLeJeu;
    bool m_pause;
    float m_difficulte;
    int m_niveau; // Float pour �viter les r�sultat de division incoh�rents
                    // A voir si possible de remettre en int sans bug
    int m_mortsNiveauPrec;
    int m_morts;
    int m_aliensTotal;

    sf::Clock horlogePrincipale;
    sf::Time tempsPassePrincipal;
    sf::Time tempsPassePause;
    sf::Time m_debutPause;
    sf::Time tempsPasseNiveau;
    sf::Time tempsPassePop;

    std::vector<Alien> m_alien;
    sf::Texture m_img_alien;
    std::vector<sf::Sprite> m_sprite_alien;
    sf::Vector2u m_tailleAlien;

    std::vector<Tir> m_tir;
    sf::Texture m_img_tir;
    std::vector<sf::Sprite> m_sprite_tir;
    sf::Vector2u m_tailleTir;

    std::vector<Explosion> m_explosion;
    sf::Texture m_img_explosion;
    std::vector<sf::Sprite> m_sprite_explosion;

    Joueur m_joueur;
    sf::Texture m_img_joueur;
    sf::Sprite m_sprite_joueur;
    sf::Vector2u m_tailleJoueur;
    int m_deplacerJoueur;

    Fond *m_fond = NULL;
    sf::RectangleShape m_fondPause;

    ostringstream nomScreenshot;
    time_t timer;
    int alea;
};

#endif
