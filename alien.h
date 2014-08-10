#ifndef ALIEN_H
#define ALIEN_H

#include "gamestate.h"
#include "vaisseau.h"

class Alien : public Vaisseau
{
    public:
        Alien(sf::Time tempsPassePrincipal, int niveau, float difficulte, sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau);
        virtual ~Alien();

        void avancer(sf::Time tempsPassePrincipal);
        bool tirer(sf::Time tempsPassePrincipal);

        const int get_vitesse() const
        {
            return m_vitesse;
        }
    private:
        bool m_arme;
        sf::Vector2u m_tailleTir;
};

#endif // ALIEN_H
