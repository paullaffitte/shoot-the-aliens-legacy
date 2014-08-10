#ifndef FOND_H
#define FOND_H
#include <SFML/Graphics.hpp>
#include "gamestate.h"


class Fond
{
    public:
        Fond(sf::Vector2u dimensionsJeu);
        virtual ~Fond();

        void update(sf::Time tempsPassePrincipal);
        void draw(GameEngine* shootTheAliens);
    private:
        sf::Vector2u m_dimensionsJeu;

        sf::Texture *m_img_fond;
        sf::Sprite *m_sprite_fond;

        sf::Time m_tempsPasseFond;
};

#endif // FOND_H
