#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <SFML/Audio.hpp>
#include "vaisseau.h"

enum Sons {TIR, EXPLOSION};

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        static SoundManager *getInstance()
        {
            if (SoundManager::m_singleton == NULL)
            {
                SoundManager::m_singleton = new SoundManager;
            }
            return SoundManager::m_singleton;
        }

        static void kill()
        {
            if (SoundManager::m_singleton != NULL)
            {
                delete SoundManager::m_singleton;
                SoundManager::m_singleton = NULL;
            }
        }
        void nettoyer();
        void pause(bool pause);
        void playPause(bool pause, sf::Sound *son);
        void jouerSon(Sons type);
        void jouerStrafe(bool stopper, sf::Time tempsPassePrincipal, bool tuer = false);
        void jouerReacteur(int proprietaire, bool stopper);
        void fx(sf::Time tempsPassePrincipal);
    protected:
    private:
        static SoundManager *m_singleton;
        sf::Music m_musique;
        std::deque<sf::Sound> m_son;
        std::map<int, std::deque<sf::Sound> > m_son_reacteur;
        sf::Sound *m_son_strafe = NULL;
        sf::Sound *m_son_fx = NULL;

        int const m_nbrSonsTir = 3;
        sf::SoundBuffer *m_buffer_tir = NULL;
        int const m_nbrSonsExplosion = 4;
        sf::SoundBuffer *m_buffer_explosion = NULL;
        int const m_nbrSonsReacteur = 4;
        sf::SoundBuffer *m_buffer_reacteur = NULL;
        int const m_nbrSonsStrafe = 2;
        sf::SoundBuffer *m_buffer_strafe = NULL;
        int const m_nbrFX = 4;
        sf::SoundBuffer *m_buffer_fx = NULL;

        unsigned int m_volumeMusique, m_volumeFX, m_volumeTir, m_volumeExplosion, m_volumeReacteur, m_volumeStrafe;
        float m_volume, m_volumeBruitages;

        int tir;
        float m_vitesseAttenuationStrafe;
        sf::Time m_tempsPasseAttenuation;
        sf::Time m_tempsPasseFX;
};

#endif // SOUNDMANAGER_H
