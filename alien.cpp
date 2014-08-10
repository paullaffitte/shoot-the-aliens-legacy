#include "alien.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>

Alien::Alien(sf::Time tempsPassePrincipal, int niveau, float difficulte, sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau)
{
    m_vitesse = 500 * difficulte + niveau * 20;
    if(niveau == 1)
    {
        if(rand() % 100 + 1 < 30)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }
    else if(niveau <= 2)
    {
        if(rand() % 100 + 1 < 60)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }
    else if(niveau <= 4)
    {
        if(rand() % 100 + 1 < 90)
        {
            m_arme = true;
        }else{
            m_arme = false;
        }
    }else{
        m_arme = true;
    }
    m_position.x = rand() % (dimensionJeu.x + 1 - tailleVaisseau.x);
    m_position.y = -100;
    m_freqDeTir = 1 + difficulte + niveau / 5;
    m_tempsPasseMouvement = tempsPassePrincipal;
}

Alien::~Alien()
{
}

void Alien::avancer(sf::Time tempsPassePrincipal)
{
    m_position.y = m_position.y + m_vitesse * (tempsPassePrincipal.asSeconds() - m_tempsPasseMouvement.asSeconds());
    m_tempsPasseMouvement = tempsPassePrincipal;
}

bool Alien::tirer(sf::Time tempsPassePrincipal)
{
    Vaisseau::tirer(tempsPassePrincipal);
    if(!(m_arme)) m_tirer = false;
    return m_tirer;
}
