#include <SFML/Graphics.hpp>
#include <vector>

//using namespace sf;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Weapon
{
private:
    sf::Sprite spr;//sprite pocisku
    bool przyjaciel; // true jeśli to pocisk gracza
    int x,y;//współrzędne pocisku
    int damage;//obrażenia pocisku
public:
    bool Visible; //widoczność pocisku
    int move_type; // rodzaj poruszania się pocisku
    //Argumenty kostruktora: wymiary i początek sprita, teskstura pocisków, zmienna która zostanie
    //przypisana do zmiennej "przyjaciel" oraz obrażenia pocisku
    Weapon(int,int,int,int,sf::Texture *,bool,int);
    bool poza_mapa();//false jeśli pocisk jest poza ekranem
    int show_damage();//metoda zwaraca wartość atrybutu damage
    void move(); // poruszanie się pocisku
    void position(int,int);//pozycja startowa pocisku
    void draw(sf::RenderWindow &window);// narysowanie pocisku
    sf::FloatRect pozycja_broni;//pozycja broni
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SpaceShip
{
private:
    int hp;
    int RED_LV,GREEN_LV,BLUE_LV;// poziom 3 rodzajów broni
    bool inviolability;// true jeśli
    int inv;
    sf::Texture t;
    sf::Texture *texture;
    sf::Sprite s;
public:
    int x,y;//współrzędne
    std::vector<std::unique_ptr<Weapon>> bron;//kontener z pociskami
    sf::FloatRect pozycja_statku;//pozycja statku
    int weapon;// rodzaj broni 1-red 2-green 3-blue
    SpaceShip(sf::RenderWindow &window,sf::Texture&);//argumenty konstruktora: okno i tekstura statku kosmicznego
    void change_weapon();//zmiana broni
    void upgrade(int);//ulepszenia broni
    void attack();//atak
    void hp_up();
    bool hp_down();
    void move(sf::RenderWindow &window);//ruch statku kosmicznego
    void draw(sf::RenderWindow &window);//narysowanie statku kosmicznego
    void position(sf::RenderWindow &window);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

