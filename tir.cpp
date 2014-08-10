#include "tir.h"

Tir::Tir(sf::Time tempsPassePrincipal, bool ennemi, int vitesseVaisseau, sf::Vector2f position, sf::Vector2u tailleVaisseau, sf::Vector2u m_tailleTir)
{
    m_ennemi = ennemi;
    m_vitesse = vitesseVaisseau * 2;
    m_position.x = position.x + tailleVaisseau.x / 2 - m_tailleTir.x / 2;
    m_position.y = position.y + tailleVaisseau.y / 2;
    m_tempsPasseAvancer = tempsPassePrincipal;

    if(!m_ennemi) SoundManager::getInstance()->jouerSon(TIR);
}

Tir::~Tir()
{
}

void Tir::avancer(sf::Time tempsPassePrincipal)
{
    if(m_ennemi)
    {
        m_position.y = m_position.y + m_vitesse * (tempsPassePrincipal.asSeconds() - m_tempsPasseAvancer.asSeconds());
        m_tempsPasseAvancer = tempsPassePrincipal;
    }else{
        m_position.y = m_position.y - 600 * (tempsPassePrincipal.asSeconds() - m_tempsPasseAvancer.asSeconds());
        m_tempsPasseAvancer = tempsPassePrincipal;
    }
}
