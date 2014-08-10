#include "joueur.h"
#include <iostream>

enum Directions
{
    IMMOBILE, GAUCHE, DROITE
};

Joueur::Joueur()
{
    m_freqDeTir = 4;
}

Joueur::~Joueur()
{
}

void Joueur::set_joueur(sf::Vector2u dimensionJeu, sf::Vector2u tailleVaisseau)
{
    m_position.x = dimensionJeu.x / 2 - tailleVaisseau.x / 2;
    m_position.y = dimensionJeu.y - tailleVaisseau.y - 10;
    m_vitesseMax = dimensionJeu.x * 1.5;
    m_tailleVaisseau = tailleVaisseau;
    m_dimensionFenetre = dimensionJeu;
}

void Joueur::deplacer(sf::Time tempsPassePrincipal, int direction)
{
    if(this->get_vivant())
    {
        m_acceleration = m_vitesseMax * (tempsPassePrincipal.asSeconds() - m_tempsPasseMouvement.asSeconds()) * 6;

        if(m_vitesse == 0) m_direction = direction;

        if(direction == m_direction && direction != IMMOBILE)
        {
            m_vitesse = m_vitesse + m_acceleration;
        }
        else if(direction == IMMOBILE)
        {
            m_vitesse = m_vitesse - m_acceleration;
        }else{
            m_vitesse = m_vitesse - 2 * m_acceleration;
        }

        if(m_vitesse > m_vitesseMax) m_vitesse = m_vitesseMax;
        if(m_vitesse <= 0)
        {
            m_vitesse = 0;
        }

        if(m_direction == GAUCHE)
        {
            m_position.x = m_position.x - m_vitesse * (tempsPassePrincipal.asSeconds() - m_tempsPasseMouvement.asSeconds());
        }
        else if(m_direction == DROITE)
        {
            m_position.x = m_position.x + m_vitesse * (tempsPassePrincipal.asSeconds() - m_tempsPasseMouvement.asSeconds());
        }

        if(m_position.x < 0)
        {
            m_position.x = 0;
            m_vitesse = 0;
        }

        if(m_position.x > m_dimensionFenetre.x - m_tailleVaisseau.x)
        {
            m_position.x = m_dimensionFenetre.x - m_tailleVaisseau.x;
            m_vitesse = 0;
        }
    }
    m_tempsPasseMouvement = tempsPassePrincipal;
}
