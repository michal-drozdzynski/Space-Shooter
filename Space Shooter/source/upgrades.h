#include <SFML/Graphics.hpp>

class Upgrades
{
private:
    int x,y; //współrzędne
    sf::Sprite s;
public:
    int Type; // typ ulepszenia
    void draw(sf::RenderWindow& window);
    void move();
    Upgrades(sf::Texture&, int,int,int);
    sf::FloatRect pozycja;
};
