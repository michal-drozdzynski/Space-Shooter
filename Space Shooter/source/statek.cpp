#include "statek.h"

Weapon::Weapon(int a,int b, int c, int d,sf::Texture* text,bool p, int e)
{
    przyjaciel=p;
    spr.setTexture(*text);
    spr.setTextureRect(sf::IntRect(a, b, c, d));
    pozycja_broni=spr.getGlobalBounds();
    move_type=e;
    damage = e;
    Visible = true;
}
///////////////////////////////////////////////////////////////////////////////
bool Weapon::poza_mapa()
{
    if(przyjaciel)
    {
        if(y<-30)return true;
        else return false;
    }
    else
    {
        if(y>1000)return true;
        else return false;
    }
}
/////////////////////////////////////////////////////////////////////////////
int Weapon::show_damage()
{
    return damage;
}
////////////////////////////////////////////////////////////////////////////////
void Weapon::draw(sf::RenderWindow &window)
{
    if(Visible)window.draw(spr);
}
///////////////////////////////////////////////////////////////////////////////
void Weapon::position(int xx, int yy)
{
    x=xx;
    y=yy;
    spr.setPosition(x,y);
    pozycja_broni=spr.getGlobalBounds();
}
/////////////////////////////////////////////////////////////////////////
void Weapon::move()
{
    if(przyjaciel) { spr.move(0,-10); y+=-10;}
    else
    {
        if(move_type==2)
        {
            spr.move(3,7);
            x+=3;
            y+=7;
        }
        else if(move_type==3)
        {
            spr.move(-3,7);
            x+=-5;
            y+=7;
        }
        else if(move_type==5)
        {
            spr.move(-5,7);
            x+=-5;
            y+=7;
        }
        else if(move_type==4)
        {
            spr.move(5,7);
            x+=4;
            y+=7;
        }
        else if(move_type==6)
        {
            spr.move(0,20);
            y+=20;
        }
        else
        {
            spr.move(0,10);
            y+=10;
        }
    }
    pozycja_broni=spr.getGlobalBounds();
}
///////////////////////////////////////////////////////////////////////////////////
SpaceShip::SpaceShip(sf::RenderWindow &window,sf::Texture &text)
{
    x=470;
    y=600;
    hp=5;
    t.loadFromFile("img/statek.png");
    texture = &text;
    s.setTexture(t);
    s.setPosition(x,y);
    sf::Mouse::setPosition(sf::Vector2i(x, y), window);
    inviolability=false;
    inv=0;
    weapon=1;
    RED_LV=1;
    GREEN_LV=0;
    BLUE_LV=0;
    pozycja_statku=s.getGlobalBounds();
}
///////////////////////////////////////////////////////////////////////
void SpaceShip::draw(sf::RenderWindow &window)
{
    if(!inviolability) window.draw(s);
    else if(inv%10!=0)
    {
        inv++;
    }
    else if(inv%10==0)
    {
        inv++;
        window.draw(s);
    }
    if(inv>=250)
    {
        inviolability=false;
        inv=0;
    }

    for(std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.begin(), koniec = bron.end(); itr != koniec; ++itr)
    {
        (*itr)->draw(window);
        (*itr)->move();
    }
}
//////////////////////////////////////////////////////////////////////////
void SpaceShip::move(sf::RenderWindow &window)
{
    x=sf::Mouse::getPosition(window).x;
    y=sf::Mouse::getPosition(window).y;

    if(x>1370)x=1370;
    if(y>830)y=830;
    if(x<0)x=0;
    if(y<0)y=0;
    sf::Mouse::setPosition(sf::Vector2i(x, y), window);
    s.setPosition(x,y);
    pozycja_statku=s.getGlobalBounds();
}
///////////////////////////////////////////////////////////////////////
void SpaceShip::attack()
{
    if(weapon==1)
    {
        switch(RED_LV)
        {
        case 1:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,1,8,8,texture,true,10)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,1,8,8,texture,true,10)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+8,y+15);
            itr--;
            (*itr)->position(x+54,y+15);
        }
        break;
        case 2:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(9,1,9,9,texture,true,13)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(9,1,9,9,texture,true,13)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+7,y+14);
            itr--;
            (*itr)->position(x+53,y+14);

        }
        break;
        case 3:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(19,1,15,7,texture,true,15)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(19,1,15,7,texture,true,15)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+4,y+15);
            itr--;
            (*itr)->position(x+50,y+15);
        }
        break;
        case 4:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(35,1,19,9,texture,true,16)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(35,1,19,9,texture,true,16)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+3,y+13);
            itr--;
            (*itr)->position(x+49,y+13);
        }
        break;
        case 5:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(55,1,15,15,texture,true,19)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(55,1,15,14,texture,true,19)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+4,y+8);
            itr--;
            (*itr)->position(x+50,y+8);
        }
        break;
        case 6:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(71,1,15,16,texture,true,20)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(71,1,15,16,texture,true,20)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+4,y+7);
            itr--;
            (*itr)->position(x+50,y+7);
        }
        break;
        case 7:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(87,1,19,16,texture,true,23)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(87,1,19,16,texture,true,23)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+49,y+7);
            itr--;
            (*itr)->position(x+3,y+7);
        }
        break;
        case 8:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(107,1,19,18,texture,true,25)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(107,1,19,18,texture,true,25)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+3,y+5);
            itr--;
            (*itr)->position(x+49,y+5);
        }
        break;
        }
    }
    if(weapon==2)
    {
        switch(GREEN_LV)
        {
        case 1:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,36,9,5,texture,true,11)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,36,9,5,texture,true,11)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+7,y+17);
            itr--;
            (*itr)->position(x+53,y+17);
        }
        break;
        case 2:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(12,36,11,6,texture,true,14)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(12,36,11,6,texture,true,14)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+6,y+16);
            itr--;
            (*itr)->position(x+52,y+16);
        }
        break;
        case 3:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(24,36,17,5,texture,true,17)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(24,36,17,5,texture,true,17)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+3,y+17);
            itr--;
            (*itr)->position(x+49,y+17);
        }
        break;
        case 4:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(42,36,16,6,texture,true,21)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(42,36,16,6,texture,true,21)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+3,y+16);
            itr--;
            (*itr)->position(x+49,y+16);
        }
        break;
        case 5:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(59,36,17,9,texture,true,28)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(59,36,17,9,texture,true,28)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+3,y+14);
            itr--;
            (*itr)->position(x+49,y+14);
        }
        break;
        }
    }
    if(weapon==3)
    {
        switch(BLUE_LV)
        {
        case 1:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,62,5,11,texture,true,12)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(1,62,5,11,texture,true,12)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+9,y+12);
            itr--;
            (*itr)->position(x+55,y+12);
        }
        break;
        case 2:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(7,62,8,15,texture,true,18)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(7,62,8,15,texture,true,18)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+7,y+8);
            itr--;
            (*itr)->position(x+53,y+8);
        }
        break;
        case 3:
        {
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(17,62,11,19,texture,true,30)));
            bron.push_back(std::unique_ptr<Weapon>(new Weapon(17,62,11,19,texture,true,30)));

            std::vector<std::unique_ptr<Weapon>>::iterator itr = bron.end();
            itr--;
            (*itr)->position(x+6,y+4);
            itr--;
            (*itr)->position(x+52,y+4);
        }
        break;
        }
    }

}
////////////////////////////////////////////////////////////////////////////
void SpaceShip::change_weapon()
{
    if(weapon==1&&GREEN_LV>0)weapon=2;
    else if(weapon==1&&BLUE_LV>0)weapon=3;
    else if(weapon==2&&BLUE_LV>0)weapon=3;
    else if(weapon==2&&BLUE_LV==0)weapon=1;
    else if(weapon==3)weapon=1;
}
/////////////////////////////////////////////////////////////////////////////////
void SpaceShip::upgrade(int q)
{
    switch(q)
    {
    case 1:
    {
        if(RED_LV<8)RED_LV++;
        weapon = 1;
    }
        break;
    case 2:
    {
        if(GREEN_LV<5)GREEN_LV++;
        weapon = 2;
    }
        break;
    case 3:
    {
        if(BLUE_LV<3)BLUE_LV++;
        weapon = 3;
    }
        break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
void SpaceShip::hp_up()
{
    hp++;
}
//////////////////////////////////////////////////////////////////////////////////////////////
bool SpaceShip::hp_down()
{
    if(!inviolability)
    {
        hp--;
        if(hp>0)
        {
            inviolability=true;
            inv++;
        }
    }
    if(hp<=0) return false;
    else return true;

}
//////////////////////////////////////////////////////////////////////////////////////////////
void SpaceShip::position(sf::RenderWindow &window)
{
    sf::Mouse::setPosition(sf::Vector2i(x, y), window);
}
