#include "enemys.h"
#include <iostream>

void Enemys::move(int k,int stage)
{
    if(Type==4)
    {
        s.move(0,7);
        y+=7;
    }

    else if(Type==6)
    {
        if(y<=0)
        {
            s.move(0,5);
            y+=5;
        }
        if(stage==2||stage==5)
        {
            if(right)
            {
                s.move(5,0);
                x+=5;
                if(x>1043) right = false;
            }
            else if(!right)
            {
                s.move(-5,0);
                x+=-5;
                if(x<5) right = true;
            }
        }
        if(stage==3)
        {
            if(x<530)
            {
                s.move(5,0);
                x+=5;
            }
            if(x>520)
            {
                s.move(-5,0);
                x+=-5;
            }
        }
    }
    else if(Type==5)
    {
        if(x<k-24)
        {
            s.move(10,0);
            x+=10;
        }
        else if(x>k-13)
        {
            s.move(-10,0);
            x+=-10;
        }
    }
    else
    {
        if(right)
        {
            s.move(5,2);
            x+=5;
            y+=2;

            switch(Type)
            {
                case 1:
                {
                    if(x>1390)
                        right = false;
                }
                break;
                case 2:
                {
                    if(x>1375)
                    if(x>1375)
                        right = false;
                }
                break;
                case 3:
                {
                    if(x>1365)
                        right = false;
                }
                break;
            }

        }
        else
        {
            s.move(-5,2);
            x+=-5;
            y+=2;
            if(x<5) right = true;
        }

    }
    pozycja_wroga=s.getGlobalBounds();
}

//////////////////////////////////////////////////
void Enemys::draw(sf::RenderWindow& window)
{
    if(Type==3||Type==5||Type==6)
    {
        for(std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.begin(), koniec = bron.end(); itr != koniec; ++itr)
        {
            (*itr)->draw(window);
            (*itr)->move();
        }
    }
    if(Visible)window.draw(s);
}
//////////////////////////////////////////////////////////
bool Enemys::hp_down(int s)
{
    hp=hp-s;
    if(hp<=0) return true;
    else return false;
}
///////////////////////////////////////////////////////////////
bool Enemys::poza_mapa()
{
    if(y>900) return true;
    else return false;
}
/////////////////////////////////////////////////
Easy::Easy(int xx,int yy,int mod,sf::Texture& text,bool r)
{
    Visible = true;
    s.setTexture(text);
    Type=1;
    model=mod;
    right = r;
    x=xx;
    y=yy;

    switch(model)
    {
    case 1:
    {
        s.setTextureRect(sf::IntRect(1, 1, 30, 30));
        s.setPosition(x,y);
        hp=10;
    }
    break;
    case 2:
    {
        s.setTextureRect(sf::IntRect(32, 1, 30, 30));
        s.setPosition(x,y);
        hp=12;
    }
    break;
    case 3:
    {
        s.setTextureRect(sf::IntRect(63, 1, 30, 30));
        s.setPosition(x,y);
        hp=15;
    }
    break;
    case 4:
    {
        s.setTextureRect(sf::IntRect(94, 1, 30, 30));
        s.setPosition(x,y);
        hp=18;
    }
    break;
    case 5:
    {
        s.setTextureRect(sf::IntRect(125, 1, 30, 30));
        s.setPosition(x,y);
        hp=20;
    }
    break;
    }
    exp = hp;
    pozycja_wroga=s.getGlobalBounds();
}
////////////////////////////////////////////////////////////////////
void Easy::attack()
{
    ;
}
/////////////////////////////////////////////////////////////////////
Medium::Medium(int xx,int yy,int mod,sf::Texture &text,bool r)
{
    Visible = true;
    s.setTexture(text);
    Type=2;
    model = mod;
    right = r;
    x=xx;
    y=yy;

    switch(model)
    {
    case 1:
    {
        s.setTextureRect(sf::IntRect(1, 32, 46, 49));
        s.setPosition(x,y);
        hp = 30;
    }
    break;
    case 2:
    {
        s.setTextureRect(sf::IntRect(48, 32, 46, 49));
        s.setPosition(x,y);
        hp = 35;
    }
    break;
    case 3:
    {
        s.setTextureRect(sf::IntRect(95, 32, 46, 49));
        s.setPosition(x,y);
        hp = 40;
    }
    break;
    case 4:
    {
        s.setTextureRect(sf::IntRect(142, 32, 46, 49));
        s.setPosition(x,y);
        hp = 45;
    }
    break;
    case 5:
    {
        s.setTextureRect(sf::IntRect(189, 32, 46, 49));
        s.setPosition(x,y);
        hp = 50;
    }
    break;
    }

    pozycja_wroga=s.getGlobalBounds();
    exp = hp;
}
///////////////////////////////////////////////////////////////////////////
void Medium::attack()
{
    ;
}
//////////////////////////////////////////////////////////////////////////
Hard::Hard(int xx,int yy,int mod,sf::Texture &text,sf::Texture &text2,bool r)
{
    Visible = true;
    x=xx;
    y=yy;
    s.setTexture(text);
    b=&text2;
    Type=3;
    model=mod;
    right = r;
    //zniszcz = false;

    switch(model)
    {
    case 1:
    {
        s.setTextureRect(sf::IntRect(1, 82, 58, 69));
        s.setPosition(x,y);
        hp = 50;
    }
    break;
    case 2:
    {
        s.setTextureRect(sf::IntRect(60, 82, 58, 69));
        s.setPosition(x,y);
        hp = 75;
    }
    break;
    case 3:
    {
        s.setTextureRect(sf::IntRect(119, 82, 58, 69));
        s.setPosition(x,y);
        hp = 100;
    }
    break;
    case 4:
    {
        s.setTextureRect(sf::IntRect(178, 82, 58, 69));
        s.setPosition(x,y);
        hp = 125;
    }
    break;
    case 5:
    {
        s.setTextureRect(sf::IntRect(237, 82, 58, 69));
        s.setPosition(x,y);
        hp = 150;
    }
    break;
    }
    pozycja_wroga=s.getGlobalBounds();
    exp = hp;
}
/////////////////////////////////////////////////////////////////////////////////////
void Hard::attack()
{
    if(Visible)
    {
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,9,7,7,b,false,1)));
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,9,7,7,b,false,1)));
        std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
        itr--;
        (*itr)->position(x+2,y+63);
        itr--;
        (*itr)->position(x+49,y+63);
    }
}
////////////////////////////////////////////////////////////////////////////////////
Meteor::Meteor(int xx,int yy,int mod,sf::Texture &text)
{

    Visible = true;
    x=xx;
    y=yy;
    s.setTexture(text);
    Type = 4;
    model=mod;

    switch(model)
    {
    case 1:
    {
        s.setTextureRect(sf::IntRect(156, 1, 30, 30));
        s.setPosition(x,y);
        hp = 50;
    }
    break;
    case 2:
    {
        s.setTextureRect(sf::IntRect(235, 31, 50, 50));
        s.setPosition(x,y);
        hp = 100;
    }
    break;
    case 3:
    {
        s.setTextureRect(sf::IntRect(203, 152, 75, 75));
        s.setPosition(x,y);
        hp = 150;
    }
    break;
    case 4:
    {
        s.setTextureRect(sf::IntRect(102, 152, 100, 100));
        s.setPosition(x,y);
        hp = 200;
    }
    break;
    }
    exp = hp;
}
///////////////////////////////////////////////////////////////////////////////
void Meteor::attack()
{
    ;
}
//////////////////////////////////////////////////////////////////////////////////////
Mini_boss::Mini_boss(int xx,int yy,int mod,sf::Texture &text,sf::Texture &text2)
{
    x=xx;
    y=yy;
    s.setTexture(text);
    b=&text2;
    Type = 5;
    model=mod;
    Visible = true;

    switch(model)
    {
    case 1:
    {
        s.setTextureRect(sf::IntRect(1, 152, 100, 100));
        s.setPosition(x,y);
        hp = 500;
    }
    break;
    }
    exp = hp;
}
//////////////////////////////////////////////////////////////////////////////////
void Mini_boss::attack()
{
    if(Visible)
    {
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,9,7,7,b,false,1)));
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,9,7,7,b,false,1)));
        std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
        itr--;
        (*itr)->position(x+9,y+85);
        itr--;
        (*itr)->position(x+84,y+85);
    }
}
/////////////////////////////////////////////////////////////////////////////////
Boss::Boss(int xx,int yy,int mod,sf::Texture &text,sf::Texture &text2)
{
    x=xx;
    y=yy;
    s.setTexture(text);
    b=&text2;
    Type = 6;
    model=mod;
    Visible = true;
    right = true;
    stage = 1;

    switch(model)
    {
    case 1:
    {
        s.setPosition(x,y);
        hp = 3000;
    }
    break;
    }
}
////////////////////////////////////////////////////////////////////////////////////
void Boss::attack()
{
    switch(kind_attack)
    {
    case 1:
    {
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,73,36,72,b,false,6)));
        std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
        itr--;
        (*itr)->position(x+178,y+208);
    }
    break;
    case 2:
    {
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,1,25,25,b,false,3)));
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,1,25,25,b,false,2)));
        std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
        itr--;
        (*itr)->position(x+105,y+220);
        itr--;
        (*itr)->position(x+262,y+220);
    }
    break;
    case 3:
    {
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,27,45,45,b,false,4)));
        bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,27,45,45,b,false,5)));
        std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
        itr--;
        (*itr)->position(x+18,y+155);
        itr--;
        (*itr)->position(x+330,y+155);
    }
    break;
    }
}

