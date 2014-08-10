#include "soundmanager.h"

SoundManager *SoundManager::m_singleton = NULL;

SoundManager::SoundManager()
{
    m_vitesseAttenuationStrafe = 0.15; //En secondes
    tir = 0;

    //Volumes de groupes
    m_volume          = 0.65;
    m_volumeBruitages = 0.75;
    //Volumes de pistes
    m_volumeMusique   = 85;
    m_volumeFX        = 35;
    m_volumeTir       = 15 * m_volumeBruitages;
    m_volumeExplosion = 70 * m_volumeBruitages;
    m_volumeReacteur  = 35 * m_volumeBruitages;
    m_volumeStrafe    = 25 * m_volumeBruitages;

    m_buffer_tir = new sf::SoundBuffer[m_nbrSonsTir];
    m_buffer_tir[0].loadFromFile("ressources/sons/tir1.wav");
    m_buffer_tir[1].loadFromFile("ressources/sons/tir2.wav");
    m_buffer_tir[2].loadFromFile("ressources/sons/tir3.wav");
    m_buffer_explosion = new sf::SoundBuffer[m_nbrSonsExplosion];
    m_buffer_explosion[0].loadFromFile("ressources/sons/explosion1.wav");
    m_buffer_explosion[1].loadFromFile("ressources/sons/explosion2.wav");
    m_buffer_explosion[2].loadFromFile("ressources/sons/explosion3.wav");
    m_buffer_explosion[3].loadFromFile("ressources/sons/explosion4.wav");
    m_buffer_reacteur = new sf::SoundBuffer[m_nbrSonsReacteur];
    m_buffer_reacteur[0].loadFromFile("ressources/sons/reacteur_principal1.wav");
    m_buffer_reacteur[1].loadFromFile("ressources/sons/reacteur_principal2.wav");
    m_buffer_reacteur[2].loadFromFile("ressources/sons/reacteur_principal3.wav");
    m_buffer_reacteur[3].loadFromFile("ressources/sons/reacteur_principal4.wav");
    m_buffer_strafe = new sf::SoundBuffer[m_nbrSonsStrafe];
    m_buffer_strafe[0].loadFromFile("ressources/sons/reacteur_secondaire1.wav");
    m_buffer_strafe[1].loadFromFile("ressources/sons/reacteur_secondaire2.wav");
    m_son_strafe = new sf::Sound[m_nbrSonsStrafe];
    m_buffer_fx = new sf::SoundBuffer[m_nbrFX];
    m_buffer_fx[0].loadFromFile("ressources/sons/fx1.wav");
    m_buffer_fx[1].loadFromFile("ressources/sons/fx2.wav");
    m_buffer_fx[2].loadFromFile("ressources/sons/fx3.wav");
    m_buffer_fx[3].loadFromFile("ressources/sons/fx4.wav");
    m_son_fx = new sf::Sound[m_nbrFX];

    for(int i=0 ; i<m_nbrSonsStrafe ; i++)
    {
        m_son_strafe[i] = sf::Sound(m_buffer_strafe[i]);
        m_son_strafe[i].setLoop(true);
        m_son_strafe[i].setVolume(0);
        m_son_strafe[i].play();
    }
    for(int i=0 ; i<m_nbrFX ; i++)
    {
        m_son_fx[i] = sf::Sound(m_buffer_fx[i]);
        m_son_fx[i].setVolume(m_volumeFX);
    }

    m_musique.openFromFile("ressources/musiques/main_theme.wav");
    m_musique.play();
    m_musique.setVolume(m_volumeMusique);
}

SoundManager::~SoundManager()
{
    delete[] m_buffer_tir;
    delete[] m_buffer_explosion;
    delete[] m_buffer_reacteur;
    delete[] m_buffer_strafe;
    delete[] m_son_strafe;
    delete[] m_buffer_fx;
}

void SoundManager::nettoyer()
{
    for(unsigned int i=0 ; i<m_son.size() ; i++)
    {
        if(m_son[i].getStatus() == 0 )
        {
            m_son.erase(m_son.begin() + i);
        }
    }
    if(m_musique.getPlayingOffset() >= sf::seconds(88.61))
    {
        m_musique.setPlayingOffset(sf::seconds(59.07));
    }
}

void SoundManager::pause(bool pause)
{
    for(unsigned int i=0 ; i<m_son.size() ; i++)
    {
        playPause(pause, &m_son[i]);
    }
    playPause(pause, &m_son_strafe[0]);
    playPause(pause, &m_son_strafe[1]);
    for(std::map<int, std::deque<sf::Sound> >::iterator it=m_son_reacteur.begin() ; it!=m_son_reacteur.end() ; it++)
    {
        for(unsigned int i=0 ; i<it->second.size() ; i++)
        {
            playPause(pause, &it->second[i]);
        }
    }
}

void SoundManager::playPause(bool pause, sf::Sound *son)
{
    if(pause) son->pause();
    else son->play();
}

void SoundManager::jouerSon(Sons type)
{
    switch (type)
    {
        case TIR:
        {
            m_son.push_back(sf::Sound(m_buffer_tir[tir]));
            m_son.back().setVolume(m_volumeTir);
            m_son.back().play();
            tir++;
            if(tir == m_nbrSonsTir) tir = 0;
            break;
        }
        case EXPLOSION:
        {
            m_son.push_back(sf::Sound(m_buffer_explosion[rand()%m_nbrSonsExplosion]));
            m_son.back().setVolume(m_volumeExplosion);
            m_son.back().play();
            break;
        }
    }
}

void SoundManager::jouerStrafe(bool stopper, sf::Time tempsPassePrincipal, bool tuer)
{
    if(tuer)
    {
        m_son_strafe[0].setVolume(0);
        m_son_strafe[1].setVolume(0);
    }else{
        float multiplicateur = tempsPassePrincipal.asSeconds() - m_tempsPasseAttenuation.asSeconds();
        if(stopper && m_son_strafe[0].getVolume() > 5)
        {
            m_son_strafe[0].setVolume(m_son_strafe[0].getVolume() - m_volumeStrafe / m_vitesseAttenuationStrafe * multiplicateur);
            m_son_strafe[1].setVolume(m_son_strafe[1].getVolume() - m_volumeStrafe / m_vitesseAttenuationStrafe * multiplicateur);
            if(m_son_strafe[0].getVolume() <= 5)
            {
                m_son_strafe[0].setVolume(0);
                m_son_strafe[1].setVolume(0);
            }
        }
        else if(!stopper && m_son_strafe[0].getVolume() < m_volumeStrafe)
        {
            m_son_strafe[0].setVolume(m_son_strafe[0].getVolume() + m_volumeStrafe / m_vitesseAttenuationStrafe * multiplicateur);
            m_son_strafe[1].setVolume(m_son_strafe[1].getVolume() + m_volumeStrafe / m_vitesseAttenuationStrafe * multiplicateur);
        }
        m_tempsPasseAttenuation = tempsPassePrincipal;
    }
}

void SoundManager::jouerReacteur(int proprietaire, bool stopper)
{
    if(stopper)
    {
        m_son_reacteur.erase(proprietaire);
    }else{
        std::deque<sf::Sound> *pointeur = &m_son_reacteur[proprietaire]; //Pour optimiser la recherche dans la std::map<int, sf::Sound>
        for(int i=0 ; i<m_nbrSonsReacteur ; i++)
        {
            pointeur->push_back(sf::Sound(m_buffer_reacteur[i]));
            pointeur->back().setLoop(true);
            pointeur->back().setVolume(m_volumeReacteur);
            pointeur->back().play();
        }
    }
}

void SoundManager::fx(sf::Time tempsPassePrincipal)
{
    if(tempsPassePrincipal.asSeconds() - m_tempsPasseFX.asSeconds() > 60)
    {
        m_son_fx[rand()%m_nbrFX].play();
        m_tempsPasseFX = tempsPassePrincipal;
    }
}
