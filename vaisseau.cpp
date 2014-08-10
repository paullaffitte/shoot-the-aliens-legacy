#include "vaisseau.h"

int Vaisseau::nbrEtat = 4;
int Vaisseau::nbrDeVaisseaux = 0;

Vaisseau::Vaisseau()
{
    m_vivant = true;
    m_opacite = 255;
    m_etat = 0;
    m_id = Vaisseau::nbrDeVaisseaux;
    Vaisseau::nbrDeVaisseaux++;
}

Vaisseau::~Vaisseau()
{
}

void Vaisseau::mourir(sf::Time tempsPassePrincipal)
{
    if(m_opacite > 0)
    {
        m_opacite = m_opacite - 255 * (tempsPassePrincipal.asSeconds() - m_tempsPasseMourir.asSeconds()) * 2;
        m_tempsPasseMourir = tempsPassePrincipal;
    }
    else if(m_opacite < 0)
    {
        m_opacite = 0;
    }
    if(m_opacite == 0)
    {
        SoundManager::getInstance()->jouerReacteur(m_id, true);
    }
}

bool Vaisseau::tirer(sf::Time tempsPassePrincipal)
{
    m_tirer = false;
    if(tempsPassePrincipal.asSeconds() - m_tempsPasseTirer.asSeconds() > 1 / m_freqDeTir)
    {
        m_tempsPasseTirer = tempsPassePrincipal;
        m_tirer = true;
    }
    return m_tirer;
}

void Vaisseau::changerEtat(sf::Time tempsPassePrincipal)
{
    if((tempsPassePrincipal.asMilliseconds() - m_tempsPasseEtat.asMilliseconds()) >= 75)
    {
        if(m_etat >= nbrEtat-2)
        {
            m_etat = 0;
        }else{
            m_etat++;
        }
        m_tempsPasseEtat = tempsPassePrincipal;
    }
    if((tempsPassePrincipal.asMilliseconds() - m_tempsPasseRupture.asMilliseconds()) >= 30)
    {
        if(m_etat == nbrEtat-1)
        {
            m_etat = 0;
        }else{
            if(rand() % 50 + 1 == 1)
            {
                m_etat = nbrEtat-1;
            }
        }
        m_tempsPasseRupture = tempsPassePrincipal;
    }
}

sf::Vector2u Vaisseau::get_taille(sf::Vector2u tailleJoueur)
{
    sf::Vector2u taille = sf::Vector2u(tailleJoueur.x/nbrEtat, tailleJoueur.y);
    return taille;
}
