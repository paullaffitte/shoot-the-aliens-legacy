#ifndef TIR_H
#define TIR_H

#include "gamestate.h"
#include "soundmanager.h"
#include <vector>
#include <iostream>

class Tir
{
    public:
        Tir(sf::Time tempsPassePrincipal, bool ennemi, int vitesse, sf::Vector2f position, sf::Vector2u tailleAlien, sf::Vector2u m_tailleTir);
        virtual ~Tir();

        void avancer(sf::Time tempsPassePrincipal);

        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const bool get_ennemi() const
        {
            return m_ennemi;
        }
    private:
        sf::Vector2f m_position;
        int m_vitesse;
        bool m_ennemi;

        sf::Time m_tempsPasseAvancer;
};

#endif // TIR_H
