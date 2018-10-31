#include <SFML/Graphics.hpp>
#include "contents.h"

//argumenty funkcji: okno, pozycja myszki, t³o, napis start i napis wyjdŸ z gry
int startGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&st, sf::Sprite&kc)
{
    while(window.isOpen())
    {
        sf::Event e;
        pozycja = sf::Mouse::getPosition(window);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if(st.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
                st.setColor(sf::Color(255, 255,255 , 180));
                if (e.type == sf::Event::MouseButtonPressed)
                    {
                        if (e.mouseButton.button == sf::Mouse::Left)
                        {
                            return 1;
                        }
                    }
            }
            else st.setColor(sf::Color(255, 255,255 , 128));
            if(kc.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
               kc.setColor(sf::Color(255, 255,255 , 180));
               /* if(pozycja.x>=510&&pozycja.x<=910&&pozycja.y>=150&&pozycja.y<=350)
                    return 1;//po klikniêciu start program zwraca 1 co rozpoczyna grê*/
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    return 0; // po klikniêciu wyjdŸ z gry program zwraca 0 co koñczy pracê programu
            }
            else kc.setColor(sf::Color(255, 255,255 , 128));
        }

        window.draw(space);
        window.draw(st);
        window.draw(kc);
        window.display();
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int chooseLevel(sf::RenderWindow& window,sf::Sprite& space,sf::Sprite num[],sf::Sprite& samouczek)
{
    while(window.isOpen())
    {
        sf::Event e;
       // pozycja = sf::Mouse::getPosition(window);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            for(int i=0;i<4;i++)
            {
                if (num[i].getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
                {
                    num[i].setColor(sf::Color(255, 255,255 , 180));
                    if (e.type == sf::Event::MouseButtonPressed)
                    {
                        if (e.mouseButton.button == sf::Mouse::Left)
                        {
                            return i+1;
                        }
                    }

                }
                else num[i].setColor(sf::Color(255, 255,255 , 128));
            }
            if(samouczek.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
                samouczek.setColor(sf::Color(255, 255,255 , 180));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                return 0;
            }
            else samouczek.setColor(sf::Color(255, 255,255 , 128));
        }

        window.clear();

        window.draw(space);
        window.draw(samouczek);
        window.draw(num[0]);
        window.draw(num[1]);
        window.draw(num[2]);
        //window.draw(num[3]);
        window.display();
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//argumenty funkcji: okno, pozycja myszki, t³o, napis wznów grê i napis wyjdŸ z gry
int pauzeGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&cont, sf::Sprite&kc)
{
    while(window.isOpen())
    {
        sf::Event e;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if(cont.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
                cont.setColor(sf::Color(255, 255,255 , 180));
                 if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    return 1;//po klikniêciu wznów grê program zwraca 1 co wznawia grê

            }
            else cont.setColor(sf::Color(255, 255,255 , 128));
            if(kc.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
               kc.setColor(sf::Color(255, 255,255 , 180));
               /* if(pozycja.x>=510&&pozycja.x<=910&&pozycja.y>=150&&pozycja.y<=350)
                    return 1;//po klikniêciu start program zwraca 1 co rozpoczyna grê*/
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    return 0; // po klikniêciu wyjdŸ z gry program zwraca 0 co koñczy pracê programu
            }
            else kc.setColor(sf::Color(255, 255,255 , 128));
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if(wl.getGlobalBounds().contains(window.mapPixelToCoords(mousePos)))
            {
                wl.setColor(sf::Color(255, 255,255 , 180));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                return 1;

            }
            else wl.setColor(sf::Color(255, 255,255 , 128));
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
                return 2;
            }
            else if(!(*itr)->Visible&&(((*itr)->Type==1)||(*itr)->Type==2||(*itr)->Type==4))
            {
                enemys.erase(itr);
                return 2;
            }
            else if(((*itr)->Type==3||(*itr)->Type==5||(*itr)->Type==6)&&!(*itr)->Visible&&(*itr)->bron.empty())
            {
                enemys.erase(itr);
                return 2;
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
                    return 2;
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
        return 2;
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


