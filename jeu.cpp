#include "jeu.h"

enum Directions
{
    IMMOBILE, GAUCHE, DROITE
};

struct AABB
{
  float x;
  float y;
  int largeur;
  int hauteur;
};

bool Collision(AABB objet1, AABB objet2)
{
   if((objet2.x >= objet1.x + objet1.largeur)   // trop � droite
	|| (objet2.x + objet2.largeur <= objet1.x)  // trop � gauche
	|| (objet2.y >= objet1.y + objet1.hauteur)  // trop en bas
	|| (objet2.y + objet2.hauteur <= objet1.y)) // trop en haut
          return false;
   else
          return true;
}

Jeu Jeu::m_Jeu;

void Jeu::Init()
{
    m_dimensionsJeu.x = 400;
    m_dimensionsJeu.y = 700;

    m_fond = new Fond(m_dimensionsJeu);

    m_dansLeJeu = false;
    m_pause = false;
    m_difficulte = 0.5;
    m_niveau = 1;
    m_morts = 0;
    m_aliensTotal = 0;
    m_score = 0;
    m_scoreFinal = 0;
    m_highscore = 0;
    m_finPartie = false;

    m_police.loadFromFile("ressources/bnmachine.ttf");
    m_start.setFont(m_police);
    m_start.setString("I Wanna Kill Aliens !");
    m_start.setCharacterSize(32);
    m_start.setColor(sf::Color::Red);
    m_rectangle = m_start.getLocalBounds();
    m_start.setOrigin(m_rectangle.width/2, m_rectangle.height/2);

    m_version.setFont(m_police);
    m_version.setString("Beta 1.0");
    m_version.setCharacterSize(13);
    m_version.setColor(sf::Color::White);

    m_texteScore.setFont(m_police);
    m_texteScore.setCharacterSize(42);
    m_texteScore.setColor(sf::Color::White);

    m_texteScorePrecedent.setFont(m_police);
    m_texteScorePrecedent.setCharacterSize(32);
    m_texteScorePrecedent.setColor(sf::Color::White);

    m_texteHighscore.setFont(m_police);
    m_texteHighscore.setCharacterSize(32);
    m_texteHighscore.setColor(sf::Color::Yellow);

    m_textePause.setFont(m_police);
    m_textePause.setString("Pause");
    m_textePause.setCharacterSize(50);
    m_textePause.setColor(sf::Color::White);

    m_img_joueur.loadFromFile("ressources/images/joueur.png");
    m_img_alien.loadFromFile("ressources/images/alien.png");
    m_img_tir.loadFromFile("ressources/images/tir.png");
    m_img_explosion.loadFromFile("ressources/images/explosion.png");

    m_tailleTir = m_img_tir.getSize();
    m_tailleJoueur = Vaisseau::get_taille(m_img_joueur.getSize());
    m_tailleAlien = Vaisseau::get_taille(m_img_alien.getSize());
}

void Jeu::Cleanup()
{
    delete m_fond;
}

void Jeu::Pause()
{
}

void Jeu::Resume()
{
}

void Jeu::HandleEvents(GameEngine* shootTheAliens)
{
    // On inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
    m_shootTheAliens = shootTheAliens;
    sf::Event event;
    while(shootTheAliens->getFenetre()->pollEvent(event))
    {
        //Ev�nement "fermeture demand�e" : on ferme la fen�tre
        if(event.type == sf::Event::Closed)
        {
            shootTheAliens->getFenetre()->close();
            shootTheAliens->Quit();
        }

         //On attrape les �v�nements de redimensionnement
        if(event.type == sf::Event::Resized)
        {
            //On met � jour la vue, avec la nouvelle taille de la fen�tre
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            shootTheAliens->getFenetre()->setView(sf::View(visibleArea));
        }

        //Commencer, Pause, Quitter
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space && m_dansLeJeu == false)
            {
                m_dansLeJeu = true;
                SoundManager::getInstance()->jouerReacteur(m_joueur.get_id(), false);
            }

            if(event.key.code == sf::Keyboard::P && m_dansLeJeu)
            {
                if(m_pause)
                {
                    tempsPassePause += horlogePrincipale.getElapsedTime() - m_debutPause;
                    SoundManager::getInstance()->pause(false);
                }else{
                    m_debutPause = horlogePrincipale.getElapsedTime();
                    SoundManager::getInstance()->pause(true);
                }
                m_pause = (m_pause) ? false : true;
            }
            if(event.key.code == sf::Keyboard::C)
            {
                if(!(m_pause))
                {
                    m_debutPause = horlogePrincipale.getElapsedTime();
                    m_pause = true;
                }
                timer = time(NULL);
                alea = rand()%(90)+10;
                nomScreenshot << "screens/" << timer << "_" << alea << ".png";
                shootTheAliens->getFenetre()->capture().saveToFile(nomScreenshot.str());
                nomScreenshot.str("");
                if(m_pause)
                {
                    tempsPassePause += horlogePrincipale.getElapsedTime() - m_debutPause;
                    m_pause = false;
                }
            }
            if(event.key.code == sf::Keyboard::Q)
            {
                shootTheAliens->getFenetre()->close();
                shootTheAliens->Quit();
            }
        }

        if(m_dansLeJeu)
        {
            //D�placement du joueur
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                m_deplacerJoueur = GAUCHE;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                m_deplacerJoueur = DROITE;
            }else{
                m_deplacerJoueur = IMMOBILE;
            }
        }
    }
}

void Jeu::Update(GameEngine* shootTheAliens)
{
    m_dimensionsFenetre = shootTheAliens->getFenetre()->getSize();
    m_rectangle = m_version.getLocalBounds();
    m_version.setPosition(m_rectangle.width - 45, m_dimensionsJeu.y - m_rectangle.height - 7);

    if(m_dansLeJeu)
    {
        if(m_pause)
        {
            m_rectangle = m_textePause.getLocalBounds();
            m_textePause.setPosition(m_dimensionsJeu.x - m_rectangle.width - 5, -5);
            m_textePause.setOrigin(m_rectangle.width/2, m_rectangle.height/2);
            m_textePause.setPosition(m_dimensionsJeu.x/2, m_dimensionsJeu.y/2);
            m_fondPause.setSize(sf::Vector2f(m_dimensionsJeu.x, m_dimensionsJeu.y));
            m_fondPause.setFillColor(sf::Color(0,15,31,127));
            SoundManager::getInstance()->jouerStrafe(false, horlogePrincipale.getElapsedTime() - tempsPassePause, true);
        }else{
            m_fond->update(horlogePrincipale.getElapsedTime() - tempsPassePause);
            SoundManager::getInstance()->fx(horlogePrincipale.getElapsedTime() - tempsPassePause);
            //Niveaux
            tempsPassePrincipal = horlogePrincipale.getElapsedTime() - tempsPassePause;
            if(tempsPassePrincipal.asSeconds() - tempsPasseNiveau.asSeconds() > 5 / m_difficulte)
            {
                tempsPasseNiveau = tempsPassePrincipal;
                m_niveau++;
            }

            //Score
            stringstream convert;
            convert << m_score;
            string score = convert.str();
            m_texteScore.setString(score);
            m_rectangle = m_texteScore.getLocalBounds();
            m_texteScore.setPosition(m_dimensionsJeu.x - m_rectangle.width - 5, -5);


            //D�placements du joueur
            m_joueur.deplacer(horlogePrincipale.getElapsedTime() - tempsPassePause, m_deplacerJoueur);
            m_sprite_joueur.setPosition(m_joueur.get_position());
            if(m_deplacerJoueur == GAUCHE || m_deplacerJoueur == DROITE) SoundManager::getInstance()->jouerStrafe(false, horlogePrincipale.getElapsedTime() - tempsPassePause);
            else SoundManager::getInstance()->jouerStrafe(true, horlogePrincipale.getElapsedTime() - tempsPassePause);
            //Tir du joueur
            if(m_joueur.tirer(horlogePrincipale.getElapsedTime() - tempsPassePause))
            {
                m_tir.push_back(Tir(horlogePrincipale.getElapsedTime() - tempsPassePause, false, 0, m_joueur.get_position(), m_tailleJoueur, m_tailleTir));
                m_sprite_tir.push_back(sf::Sprite());
                m_sprite_tir.back().setTexture(m_img_tir);
                m_sprite_tir.back().setPosition(m_tir.back().get_position());
            }

            //Pop
            tempsPassePrincipal = horlogePrincipale.getElapsedTime() - tempsPassePause;
            if(tempsPassePrincipal.asSeconds() - tempsPassePop.asSeconds() > 0.5 / (m_difficulte + float(m_niveau) / 5) || m_alien.size() == 0)
            {
                tempsPassePop = tempsPassePrincipal;
                m_alien.push_back(Alien(horlogePrincipale.getElapsedTime() - tempsPassePause, m_niveau, m_difficulte, m_dimensionsJeu, m_tailleAlien));
                m_sprite_alien.push_back(sf::Sprite());
                m_sprite_alien.back().setTexture(m_img_alien);
                m_sprite_alien.back().setPosition(sf::Vector2f(m_alien.back().get_position()));
                m_aliensTotal++;
            }
            //Alien dans l'�cran
            sf::Vector2f posAlien = m_alien.front().get_position();
            if(posAlien.y < m_dimensionsJeu.y)
            {
                //Actions
                for(unsigned int i = 0 ; i < m_alien.size() && m_alien.size() > 0 ; i++)
                {
                    //D�placements alien
                    m_sprite_alien[i].setPosition(sf::Vector2f(m_alien[i].get_position()));
                    m_alien[i].avancer(horlogePrincipale.getElapsedTime() - tempsPassePause);
                    //Tir des aliens
                    if(m_alien[i].get_vivant() == true && m_alien[i].tirer(horlogePrincipale.getElapsedTime() - tempsPassePause))
                    {
                        m_tir.push_back(Tir(horlogePrincipale.getElapsedTime() - tempsPassePause, true, m_alien[i].get_vitesse(), m_alien[i].get_position(), m_tailleAlien, m_tailleTir));
                        m_sprite_tir.push_back(sf::Sprite());
                        m_sprite_tir.back().setTexture(m_img_tir);
                        m_sprite_tir.back().setPosition(m_tir.back().get_position());
                    }
                }
            }else{
                //Destruction de l'alien sorti de l'�cran
                m_alien.erase(m_alien.begin());
                m_sprite_alien.erase(m_sprite_alien.begin());
            }

            //D�placement tirs
            for(unsigned int i = 0 ; i < m_tir.size() && m_tir.size() > 0 ; i++)
            {
                m_tir[i].avancer(horlogePrincipale.getElapsedTime() - tempsPassePause);
                m_sprite_tir[i].setPosition(m_tir[i].get_position());
            }
            //Destruction des tirs sortis de l'�cran
            if(m_tir.size() > 1)
            {
                sf::Vector2f posTir = m_tir.front().get_position();
                while(posTir.y > m_dimensionsJeu.y || posTir.y < -100)
                {
                    m_tir.erase(m_tir.begin());
                    m_sprite_tir.erase(m_sprite_tir.begin());
                    if(m_tir.size() > 0)
                    {
                        posTir = m_tir.front().get_position();
                    }
                }
            }

            //Tests de collision
            sf::Vector2f posJoueur = m_joueur.get_position();
            AABB aabbJoueur = {posJoueur.x, posJoueur.y, m_tailleJoueur.x, m_tailleJoueur.y};
            sf::Vector2f posTir;

            vector<Tir>::iterator iteratorTir;
            vector<Alien>::iterator iteratorAlien;
            vector<sf::Sprite>::iterator iteratorSprite;

            //Aliens-Joueur
            for(unsigned int i=0 ; i < m_alien.size() ; i++)
            {
                posAlien = m_alien[i].get_position();
                AABB aabbAlien = {posAlien.x, posAlien.y, m_tailleAlien.x, m_tailleAlien.y};
                if(m_alien[i].get_vivant() == true && Collision(aabbJoueur, aabbAlien))
                {
                    m_joueur.set_vivant(horlogePrincipale.getElapsedTime() - tempsPassePause, false);
                    m_alien[i].set_vivant(horlogePrincipale.getElapsedTime() - tempsPassePause, false);
                }
            }

            //Tirs
            for(unsigned int i=0 ; i < m_tir.size() ; i++)
            {
                //Tirs-Joueur
                if(m_tir[i].get_ennemi())
                {
                    posTir = m_tir[i].get_position();
                    AABB aabbTir = {posTir.x, posTir.y, m_tailleTir.x, m_tailleTir.y};
                    if(m_joueur.get_vivant() == true && Collision(aabbJoueur, aabbTir)) m_joueur.set_vivant(horlogePrincipale.getElapsedTime() - tempsPassePause, false);
                } //Tirs-Aliens
                else if(!(m_tir[i].get_ennemi()))
                {
                    posTir = m_tir[i].get_position();
                    AABB aabbTir = {posTir.x, posTir.y, m_tailleTir.x, m_tailleTir.y};
                    for(unsigned int a=0 ; a < m_alien.size() ; a++)
                    {
                        posAlien = m_alien[a].get_position();
                        AABB aabbAlien = {posAlien.x, posAlien.y, m_tailleAlien.x, m_tailleAlien.y};
                        if(m_alien[a].get_vivant() == true && Collision(aabbTir, aabbAlien))
                        {
                            m_score++;
                            m_alien[a].set_vivant(horlogePrincipale.getElapsedTime() - tempsPassePause, false);

                            iteratorTir = m_tir.begin() + i;
                            m_tir.erase(iteratorTir);
                            iteratorSprite = m_sprite_tir.begin() + i;
                            m_sprite_tir.erase(iteratorSprite);
                        }
                    }
                }
            }
            //Mort des vaisseaux
            //Aliens
            for(unsigned int i=0 ; i < m_alien.size() ; i++)
            {
                if(m_alien[i].get_vivant() == false)
                {
                    if(m_alien[i].get_opacite() == 255)
                    {
                        m_explosion.push_back(Explosion(horlogePrincipale.getElapsedTime() - tempsPassePause, m_alien[i].get_position(), m_tailleAlien, m_img_explosion.getSize().y, m_alien[i].get_vitesse()));
                        m_sprite_explosion.push_back(sf::Sprite());
                        m_sprite_explosion.back().setTexture(m_img_explosion);
                        m_sprite_explosion.back().setTextureRect(sf::IntRect(0, 0, 100, 100));
                        m_sprite_explosion.back().setPosition(m_explosion.back().get_position());
                    }
                    m_alien[i].mourir(horlogePrincipale.getElapsedTime() - tempsPassePause);
                    m_sprite_alien[i].setColor(sf::Color(255, 255, 255, m_alien[i].get_opacite()));
                    if(m_alien[i].get_opacite() == 0)
                    {
                        iteratorAlien = m_alien.begin() + i;
                        m_alien.erase(iteratorAlien);
                        iteratorSprite = m_sprite_alien.begin() + i;
                        m_sprite_alien.erase(iteratorSprite);
                    }
                }
            }
            //Joueur
            if(m_joueur.get_vivant() == false)
            {
                if(m_joueur.get_opacite() == 255)
                {
                    m_explosion.push_back(Explosion(horlogePrincipale.getElapsedTime() - tempsPassePause, m_joueur.get_position(), m_tailleJoueur, m_img_explosion.getSize().y, 0));
                    m_sprite_explosion.push_back(sf::Sprite());
                    m_sprite_explosion.back().setTexture(m_img_explosion);
                    m_sprite_explosion.back().setTextureRect(sf::IntRect(0, 0, 100, 100));
                    m_sprite_explosion.back().setPosition(m_explosion.back().get_position());
                }
                m_joueur.mourir(horlogePrincipale.getElapsedTime() - tempsPassePause);
                m_sprite_joueur.setColor(sf::Color(255, 255, 255, m_joueur.get_opacite()));
                if(m_joueur.get_opacite() == 0)
                {
                    m_scoreFinal = m_score;
                    m_finPartie = true;
                    m_dansLeJeu = false;
                }
            }
            //Gestion des explosions
            if(m_explosion.size() > 0)
            {
                for(unsigned int i = 0 ; i < m_explosion.size() ; i++)
                {
                    m_explosion[i].changerEtat(horlogePrincipale.getElapsedTime() - tempsPassePause);
                    m_sprite_explosion[i].setTextureRect(sf::IntRect(100*m_explosion[i].get_etat(), 0, 100, 100));
                    m_explosion[i].avancer(horlogePrincipale.getElapsedTime() - tempsPassePause);
                    m_sprite_explosion[i].setPosition(m_explosion[i].get_position());
                }
                if(m_explosion.front().get_etat() >= 9)
                {
                    m_explosion.erase(m_explosion.begin());
                    m_sprite_explosion.erase(m_sprite_explosion.begin());
                }
            }
            //Animation des vaisseaux
            m_sprite_joueur.setTextureRect(sf::IntRect(0, 0, m_tailleJoueur.x, m_tailleJoueur.y));
            m_joueur.changerEtat(horlogePrincipale.getElapsedTime() - tempsPassePause);
            m_sprite_joueur.setTextureRect(sf::IntRect(m_tailleJoueur.x*m_joueur.get_etat(), 0, m_tailleJoueur.x, m_tailleJoueur.y));
            for(unsigned int i = 0 ; i < m_alien.size() ; i++)
            {
                m_sprite_alien[i].setTextureRect(sf::IntRect(0, 0, m_tailleAlien.x, m_tailleAlien.y));
                m_alien[i].changerEtat(horlogePrincipale.getElapsedTime() - tempsPassePause);
                m_sprite_alien[i].setTextureRect(sf::IntRect(m_tailleAlien.x*m_alien[i].get_etat(), 0, m_tailleAlien.x, m_tailleAlien.y));
            }
        }
    }else{
        m_fond->update(horlogePrincipale.getElapsedTime() - tempsPassePause);
        m_start.setPosition(m_dimensionsJeu.x/2, m_dimensionsJeu.y/3);

        //Ouverture des highscores
        ifstream highscore("highscore", ios::in);
        if(highscore)
        {
            highscore >> m_highscore;
            highscore.close();
        }

        if(m_finPartie)
        {
            //On coupe le son des strafe
            SoundManager::getInstance()->jouerStrafe(false, horlogePrincipale.getElapsedTime() - tempsPassePause, true);
            //Enregistrement du highscore
            if(m_score > m_highscore)
            {
                m_highscore = m_score;
                ofstream highscore("highscore", ios::out | ios::trunc);
                if(highscore)
                {
                    highscore << m_scoreFinal;
                    highscore.close();
                }
            }
            //Enregistrement des performances
            ofstream historique("history", ios::out | ios::app);
            if(historique)
            {
                float ratioKill;
                (m_aliensTotal > 0) ? (ratioKill = (float)m_scoreFinal / (float)m_aliensTotal) : (ratioKill = 0);
                historique << m_niveau << ";" << m_scoreFinal << ";" << m_aliensTotal << ";" << ratioKill << "\n";
                historique.close();
            }

            //R�initialisation pour une nouvelle partie
            m_score = 0;
            m_niveau = 1;
            m_mortsNiveauPrec = 0;
            m_morts = 0;
            m_aliensTotal = 0;
            tempsPasseNiveau = horlogePrincipale.getElapsedTime() - tempsPassePause;
            tempsPassePop = horlogePrincipale.getElapsedTime() - tempsPassePause;
            m_alien.clear();
            m_sprite_alien.clear();
            m_tir.clear();
            m_sprite_tir.clear();
            m_explosion.clear();
            m_sprite_explosion.clear();
            m_finPartie = false;
            m_joueur.set_vivant(horlogePrincipale.getElapsedTime() - tempsPassePause, true);
            m_joueur.set_opacite(255);
            m_sprite_joueur.setColor(sf::Color(255, 255, 255, 255));
        }

        //affichage du score et highscore
        string score = "Your score : ";
        stringstream convert;
        convert << m_scoreFinal;
        score += convert.str();
        convert.str("");
        m_texteScorePrecedent.setString(score);
        m_rectangle = m_texteScorePrecedent.getLocalBounds();
        m_texteScorePrecedent.setOrigin(m_rectangle.width/2, m_rectangle.height/2);
        m_texteScorePrecedent.setPosition(m_dimensionsJeu.x/2, m_dimensionsJeu.y/2);

        score = "Highscore : ";
        convert << m_highscore;
        score += convert.str();
        m_texteHighscore.setString(score);
        m_rectangle = m_texteHighscore.getLocalBounds();
        m_texteHighscore.setOrigin(m_rectangle.width/2, m_rectangle.height/2);
        m_texteHighscore.setPosition(m_dimensionsJeu.x/2, m_dimensionsJeu.y/3*2);

        m_sprite_joueur.setTexture(m_img_joueur);
        m_joueur.set_joueur(m_dimensionsJeu, sf::Vector2u(m_tailleJoueur.x, m_tailleJoueur.y));
    }

    m_vuePrincipale.reset(sf::FloatRect(0, 0, 400, 700));
    m_vuePrincipale.setSize(400, 700);
    sf::Vector2f facteurViewport;
    if((float)m_dimensionsFenetre.x/m_dimensionsFenetre.y < (float)m_dimensionsJeu.x/m_dimensionsJeu.y)
    {
        //largeur de fenetre petite
        facteurViewport.x = 1;
        facteurViewport.y = ((float)m_dimensionsFenetre.x/m_dimensionsFenetre.y)*((float)m_dimensionsJeu.y/m_dimensionsJeu.x);
        m_vuePrincipale.setViewport(sf::FloatRect(0, (float)(1-facteurViewport.y) / 2, facteurViewport.x, facteurViewport.y));
    }else{
        //largeur de fenetre grande
        facteurViewport.x = ((float)m_dimensionsFenetre.y/m_dimensionsFenetre.x)*((float)m_dimensionsJeu.x/m_dimensionsJeu.y);
        facteurViewport.y = 1;
        m_vuePrincipale.setViewport(sf::FloatRect((float)(1-facteurViewport.x)/2, 0, facteurViewport.x, facteurViewport.y));
    }

    SoundManager::getInstance()->nettoyer();
    shootTheAliens->getFenetre()->setView(m_vuePrincipale);
}

void Jeu::Draw(GameEngine* shootTheAliens)
{
    shootTheAliens->getFenetre()->clear(sf::Color::Black);

    m_fond->draw(shootTheAliens);

    if(m_dansLeJeu)
    {
        for(unsigned int i = 0 ; i < m_sprite_tir.size() ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_sprite_tir[i]);
        }
        shootTheAliens->getFenetre()->draw(m_sprite_joueur);
        for(unsigned int i = 0 ; i < m_sprite_alien.size() && m_sprite_alien.size() > 0 ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_sprite_alien[i]);
        }
        for(unsigned int i = 0 ; i < m_sprite_explosion.size() && m_sprite_explosion.size() > 0 ; i++)
        {
            shootTheAliens->getFenetre()->draw(m_sprite_explosion[i]);
        }
        if(m_pause)
        {
            shootTheAliens->getFenetre()->draw(m_fondPause);
            shootTheAliens->getFenetre()->draw(m_textePause);
        }
        shootTheAliens->getFenetre()->draw(m_texteScore);
    }else{
        shootTheAliens->getFenetre()->draw(m_start);
        shootTheAliens->getFenetre()->draw(m_texteScorePrecedent);
        shootTheAliens->getFenetre()->draw(m_texteHighscore);
    }
    shootTheAliens->getFenetre()->draw(m_version);
    shootTheAliens->getFenetre()->display();
}

//THREAD

void Jeu::EventFenetre()
{

}
