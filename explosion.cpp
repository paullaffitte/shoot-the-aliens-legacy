#include "explosion.h"

Explosion::Explosion(sf::Time tempsPassePrincipal, sf::Vector2f position, sf::Vector2u tailleVaisseau, unsigned int tailleExplosion, int vitesse)
{
    m_etat = 0;
    m_position.x = position.x - tailleExplosion / 2 + tailleVaisseau.x / 2;
    m_position.y = position.y - tailleExplosion / 2 + tailleVaisseau.y / 2;
    m_vitesse = vitesse;
    m_tempsPasseEtat = tempsPassePrincipal;
    m_tempsPasseAvancer = tempsPassePrincipal;
    SoundManager::getInstance()->jouerSon(EXPLOSION);
}

Explosion::~Explosion()
{
}

void Explosion::changerEtat(sf::Time tempsPassePrincipal)
{
    if((tempsPassePrincipal.asMilliseconds() - m_tempsPasseEtat.asMilliseconds()) >= 75)
    {
        m_etat++;
        m_tempsPasseEtat = tempsPassePrincipal;
    }
}

void Explosion::avancer(sf::Time tempsPassePrincipal)
{
    m_position.y = m_position.y + m_vitesse * (tempsPassePrincipal.asSeconds() - m_tempsPasseAvancer.asSeconds());
    m_tempsPasseAvancer = tempsPassePrincipal;
}
