#include "upgrades.h"

Upgrades::Upgrades(sf::Texture& t,int xx,int yy,int type)
{
    x=xx;
    y=yy;
    Type=type;
    s.setTexture(t);

    switch(type)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        {
            s.setTextureRect(sf::IntRect(1, 1, 30, 30));
            s.setPosition(x,y);
            Type=1;
        }
        break;
        case 5:
        case 6:
        case 7:
        {
            s.setTextureRect(sf::IntRect(63, 1, 30, 30));
            Type=2;
            s.setPosition(x,y);
        }
        break;
        case 8:
        {
            s.setTextureRect(sf::IntRect(32, 1, 30, 30));
            Type=3;
            s.setPosition(x,y);
        }
        break;
        case 9:
        case 10:
        {
            s.setTextureRect(sf::IntRect(94, 1, 30, 30));
            Type=4;
            s.setPosition(x,y);
        }
        break;
    }
    pozycja=s.getGlobalBounds();
}
void Upgrades::move()
{
    s.move(0,10);
    y+=10;
    pozycja=s.getGlobalBounds();
}
void Upgrades::draw(sf::RenderWindow& window)
{
    window.draw(s);
}

