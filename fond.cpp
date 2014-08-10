#include "fond.h"

Fond::Fond(sf::Vector2u dimensionsJeu)
{
    m_dimensionsJeu = dimensionsJeu;
    m_img_fond = new sf::Texture[3];
    m_sprite_fond = new sf::Sprite[3];
    m_img_fond[0].loadFromFile("ressources/images/fond1.png");
    m_img_fond[1].loadFromFile("ressources/images/fond2.png");
    m_img_fond[2].loadFromFile("ressources/images/fond3.png");

    m_img_fond[0].setRepeated(true);
    m_img_fond[1].setRepeated(true);
    m_img_fond[2].setRepeated(true);

    m_sprite_fond[0].setTexture(m_img_fond[0]);
    m_sprite_fond[0].setTextureRect(sf::IntRect(0, 0, m_dimensionsJeu.x, m_img_fond[0].getSize().y * 2));
    m_sprite_fond[1].setTexture(m_img_fond[1]);
    m_sprite_fond[1].setTextureRect(sf::IntRect(0, 0, m_dimensionsJeu.x, m_img_fond[1].getSize().y * 2));
    m_sprite_fond[2].setTexture(m_img_fond[2]);
    m_sprite_fond[2].setTextureRect(sf::IntRect(0, 0, m_dimensionsJeu.x, m_img_fond[2].getSize().y * 2));

    m_sprite_fond[0].setPosition(0, (int)-m_img_fond[0].getSize().y);
    m_sprite_fond[1].setPosition(0, (int)-m_img_fond[1].getSize().y);
    m_sprite_fond[2].setPosition(0, (int)-m_img_fond[2].getSize().y);
}

Fond::~Fond()
{
    delete m_img_fond;
    delete m_sprite_fond;
}

void Fond::update(sf::Time tempsPassePrincipal)
{
    m_sprite_fond[0].move(0, 30 * (tempsPassePrincipal.asSeconds() - m_tempsPasseFond.asSeconds()));
    m_sprite_fond[1].move(0, 70 * (tempsPassePrincipal.asSeconds() - m_tempsPasseFond.asSeconds()));
    m_sprite_fond[2].move(0, 150 * (tempsPassePrincipal.asSeconds() - m_tempsPasseFond.asSeconds()));

    if(m_sprite_fond[0].getPosition().y >= 0)
        m_sprite_fond[0].setPosition(0, (int)-m_img_fond[0].getSize().y);

    if(m_sprite_fond[1].getPosition().y >= 0)
       m_sprite_fond[1].setPosition(0, (int)-m_img_fond[1].getSize().y);

    if(m_sprite_fond[2].getPosition().y >= 0)
        m_sprite_fond[2].setPosition(0, (int)-m_img_fond[2].getSize().y);
    m_tempsPasseFond = tempsPassePrincipal;
}

void Fond::draw(GameEngine* shootTheAliens)
{
    sf::RenderTexture m_fond;
    m_fond.create(m_dimensionsJeu.x, m_dimensionsJeu.y);

    m_fond.draw(m_sprite_fond[0]);
    m_fond.draw(m_sprite_fond[1]);
    m_fond.draw(m_sprite_fond[2]);
    m_fond.display();

    sf::Sprite img;
    img.setTexture(m_fond.getTexture());
    shootTheAliens->getFenetre()->draw(img);
}
