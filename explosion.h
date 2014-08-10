#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "alien.h"
#include "joueur.h"
#include "soundmanager.h"

class Explosion
{
    public:
        Explosion(sf::Time tempsPassePrincipal, sf::Vector2f position, sf::Vector2u tailleVaisseau, unsigned int tailleExplosion, int vitesse);
        virtual ~Explosion();

        const sf::Vector2f get_position() const
        {
            return m_position;
        }
        const int get_etat() const
        {
            return m_etat;
        }

        void changerEtat(sf::Time tempsPassePrincipal);
        void avancer(sf::Time tempsPassePrincipal);
    private:
        int m_etat;
        sf::Vector2f m_position;
        int m_vitesse;

        sf::Time m_tempsPasseEtat;
        sf::Time m_tempsPasseAvancer;
};

#endif // EXPLOSION_H
