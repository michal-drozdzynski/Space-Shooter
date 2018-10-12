#include <SFML/Graphics.hpp>
#include "contents.h"

//argumenty funkcji: okno, pozycja myszki, t³o, napis start i napis wyjdŸ z gry
int startGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&st, sf::Sprite&kc)
{
    while(window.isOpen())
    {
        sf::Event e;
        pozycja = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(pozycja.x>=510&&pozycja.x<=910&&pozycja.y>=150&&pozycja.y<=350)
                    return 1;//po klikniêciu start program zwraca 1 co rozpoczyna grê
                if(pozycja.x>=280&&pozycja.x<=1130&&pozycja.y>=500&&pozycja.y<=700)
                    return 0; // po klikniêciu wyjdŸ z gry program zwraca 0 co koñczy pracê programu
            }
        }

        window.draw(space);
        window.draw(st);
        window.draw(kc);
        window.display();
    }
    return 0;
}
//argumenty funkcji: okno, pozycja myszki, t³o, napis wznów grê i napis wyjdŸ z gry
int pauzeGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&cont, sf::Sprite&kc)
{
    while(window.isOpen())
    {
        sf::Event e;
        pozycja = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(pozycja.x>=300&&pozycja.x<=1102&&pozycja.y>=170&&pozycja.y<=370)
                    return 1;//po klikniêciu wznów grê program zwraca 1 co wznawia grê
                if(pozycja.x>=280&&pozycja.x<=1130&&pozycja.y>=500&&pozycja.y<=700)
                    return 0;// po klikniêciu wyjdŸ z gry program zwraca 0 co koñczy pracê programu
            }
        }

        window.draw(space);
        window.draw(cont);
        window.draw(kc);
        window.display();
    }
    return 0;
}

//Funkcja wyœwietla napis "wygra³eœ" lub "przegra³eœ" po zakoñczonej rozgrywce
int winOrLoseGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&wl)
{
    while(window.isOpen())
    {
        sf::Event e;
        pozycja = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(pozycja.x>=320&&pozycja.x<=1120&&pozycja.y>=200&&pozycja.y<=400)
                  return 1;// po klikniêciu w napis zwraca 1 co powoduje
                  //rozpoczêcie pracy programu od nowa
            }
        }


        window.draw(space);
        window.draw(wl);
        window.display();
    }
    return 0;
}
int gameMechanics(std::vector<std::unique_ptr<Enemys>>& enemys,SpaceShip& s,sf::RenderWindow& window,
sf::Music&music,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite& lose,int& licz,sf::Sound& sound2,
int& licz2,int& licz3,int& experience,bool& m_b,int& stage,sf::Sound& sound,sf::Sprite& win)
{
    for(std::vector<std::unique_ptr<Enemys>>::iterator itr = enemys.begin(), koniec = enemys.end(); itr != koniec; ++itr)
        {

            if((*itr)->poza_mapa())
            {
                enemys.erase(itr);
                break;
            }
            else if(!(*itr)->Visible&&(((*itr)->Type==1)||(*itr)->Type==2||(*itr)->Type==4))
            {
                enemys.erase(itr);
                break;
            }
            else if(((*itr)->Type==3||(*itr)->Type==5||(*itr)->Type==6)&&!(*itr)->Visible&&(*itr)->bron.empty())
            {
                enemys.erase(itr);
                break;
            }

            if((*itr)->pozycja_wroga.intersects(s.pozycja_statku)&&(*itr)->Visible)
            {
                if(!s.hp_down())
                ///////////pora¿ka/////////////////////
                {
                    window.setMouseCursorVisible(true);
                    music.pause();
                    return winOrLoseGame(window,pozycja,space,lose);
                }
            }

            if(licz>=100)
            {
                if((*itr)->Type==3&&(*itr)->Visible)
                {
                    (*itr)->attack();
                    sound2.play();
                }
            }
            if(licz2>=25)
            {
                if((*itr)->Type==5&&(*itr)->Visible)
                {
                    (*itr)->attack();
                    sound2.play();
                }
            }
            if((*itr)->Type==6&&(*itr)->model==1&&(*itr)->Visible)
            switch(licz3)
            {
             case 70:
            {
                (*itr)->kind_attack = 1;
                (*itr)->attack();
                sound2.play();
            }
             break;
             case 85:
            {
                (*itr)->kind_attack = 2;
                (*itr)->attack();
                sound2.play();
            }
            break;
             case 100:
             {
                (*itr)->kind_attack = 3;
                (*itr)->attack();
                sound2.play();
                licz3=55;
             }
             break;
            }

            if((*itr)->Type==3||(*itr)->Type==5||(*itr)->Type==6)
            {
                for(std::vector<std::unique_ptr<Weapon>>::iterator i = (*itr)->bron.begin(),k = (*itr)->bron.end(); i != k; ++i)
                {
                    if((*i)->poza_mapa()||!(*i)->Visible)
                    {
                        (*itr)->bron.erase(i);
                        return 2;
                    }
                    else if((*i)->pozycja_broni.intersects(s.pozycja_statku)&&(*i)->Visible)
                    {
                        if(!s.hp_down())
                        {
                        ////////////////pora¿ka///////////////////////////
                            window.setMouseCursorVisible(true);
                            music.pause();
                            return winOrLoseGame(window,pozycja,space,lose);
                        }
                        (*i)->Visible = false;
                    }
                }
            }
            for(std::vector<std::unique_ptr<Weapon>>::iterator iter = s.bron.begin(), kon = s.bron.end(); iter != kon; ++iter)
            {
                if((*iter)->poza_mapa()||!(*iter)->Visible)
                {
                    s.bron.erase(iter);
                    break;
                }
                else if((*iter)->pozycja_broni.intersects((*itr)->pozycja_wroga)&&(*itr)->Visible&&(*iter)->Visible)
                {
                    if((*itr)->hp_down((*iter)->show_damage()))
                    {
                        experience+=(*itr)->exp;
                        (*itr)->Visible=false;
                        if((*itr)->Type==5)
                        {
                            m_b=false;
                            if(stage==3)
                            stage=4;

                        }
                        sound.play();
                        if((*itr)->Type==6)
                        {
                        /////////zwyciêstwo//////////////////////////
                            window.setMouseCursorVisible(true);
                            music.pause();
                            return winOrLoseGame(window,pozycja,space,win);
                        }

                    }
                    else if((*itr)->Type==6&&(*itr)->hp<=2500&&(*itr)->hp>1500)
                    {
                        stage = 2;
                    }
                    else if((*itr)->Type==6&&(*itr)->hp<=1500&&stage==2)
                    {
                        stage = 3;
                    }
                    else if((*itr)->Type==6&&(*itr)->hp<=1000&&stage==4)
                    {
                        stage = 5;
                    }
                    (*iter)->Visible=false;
                }
            }
        }
}
void upgrade(SpaceShip& s,std::vector<std::unique_ptr<Upgrades>>&upgrades)
{
     for(std::vector<std::unique_ptr<Upgrades>>::iterator itr = upgrades.begin(), koniec = upgrades.end(); itr != koniec; ++itr)
        {
            if((*itr)->pozycja.intersects(s.pozycja_statku))
            {
                switch((*itr)->Type)
                {
                    case 1:
                    {
                        s.upgrade(1);
                        upgrades.erase(itr);
                    }
                    break;
                    case 2:
                    {
                        s.upgrade(2);
                        upgrades.erase(itr);
                    }
                    break;
                    case 3:
                    {
                        s.upgrade(3);
                        upgrades.erase(itr);
                    }
                    break;
                    case 4:
                    {
                        s.hp_up();
                        upgrades.erase(itr);
                    }
                    break;
                }
            }
        }
}
