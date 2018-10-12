#include <SFML/Graphics.hpp>
#include "statek.h"

class Enemys
{
public:
    sf::Sprite s;//sprite przeciwnika
    int Type;// typ przeciwnika
    int x,y;//współrzędna przeciwnika
    int exp; //punkty doświadczenia za zniszczenie przeciwnika
    int hp;
    int model;
    bool right;// true jeśli przeciwnika ma poruszać się w prawo
    //bool destroy();
    sf::FloatRect pozycja_wroga;//pozycja wroga
    std::vector<std::unique_ptr<Weapon>> bron;//kontener z pociskami wroga
    void move(int,int);//ruch wroga;
    void draw(sf::RenderWindow& window);//narysowanie przeciwnika
    bool Visible;//widoczność przeciwknika
    bool poza_mapa();//true jeśli przeciwnik jest poza ekranem
    bool hp_down(int);
    virtual void attack()=0;
    int kind_attack;//rodzaj ataku bossa
};
//////////////////////////////////////////////////////////////////////////////////
class Easy :public Enemys
{
public:
   Easy(int,int,int,sf::Texture& text,bool);//wspolrzedne x i y, typ oraz textura.
   void attack();
};
/////////////////////////////////////////////////////////////////////////////////
class Medium :public Enemys
{
public:
   Medium(int,int,int,sf::Texture& text,bool);//wspolrzedne x i y, typ oraz textura.
   void attack();
};
/////////////////////////////////////////////////////////////////////////////////
class Hard :public Enemys
{
private:
    sf::Texture* b;
public:
   Hard(int,int,int,sf::Texture& text,sf::Texture& text2,bool);//wspolrzedne x i y, typ oraz textura statkow i broni.
   ~Hard();
   void attack();
};
/////////////////////////////////////////////////////////////////////////////////
class Meteor :public Enemys
{
public:
    Meteor(int,int,int,sf::Texture& text);//wspolrzedne x i y, typ oraz textura.
    void attack();
};
/////////////////////////////////////////////////////////////////////////////////
class Mini_boss :public Enemys
{
private:
    sf::Texture* b;
public:
    Mini_boss(int,int,int,sf::Texture& text,sf::Texture& text2);//wspolrzedne x i y, typ oraz textura statkow i broni.
    void attack();
};
//////////////////////////////////////////////////////////////////////////////////////
class Boss :public Enemys
{
private:
    sf::Texture* b;
    int stage;
public:
    Boss(int,int,int,sf::Texture& text,sf::Texture& text2);//wspolrzedne x i y, typ oraz textura bossa i broni.
    void attack();
};
