#ifndef JOUEUR_H
#define JOUEUR_H

#include "gamestate.h"
#include "vaisseau.h"
#include <SFML/Audio.hpp>

class Joueur : public Vaisseau
{
    public:
        Joueur();
        virtual ~Joueur();

        void deplacer(sf::Time tempsPassePrincipal, int direction);

        void set_joueur(sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau);
    private:
        sf::Vector2u m_dimensionFenetre;
        int m_vitesseMax;
        float m_acceleration;
        int m_direction;

        sf::SoundBuffer buff;
        sf::Sound son;
};

#endif // JOUEUR_H
