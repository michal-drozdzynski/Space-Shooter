#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include "contents.h"
#include "iostream"



int first_mission(sf::RenderWindow& window,sf::Sprite&kc)
{
    if(window.getSize().x!=1440) return 1;


    sf::Vector2i pozycja = sf::Mouse::getPosition(window);

    //////tło//////////
    sf::Texture background;
    background.loadFromFile("img/back.png");
    sf::Sprite space;
    space.setTexture(background);

    /////////napis wznów grę//////////
    sf::Texture contin;
    contin.loadFromFile("img/kontynuuj.png");
    sf::Sprite cont;
    cont.setTexture(contin);
    cont.setPosition(20,170);
    cont.setColor(sf::Color(255, 255,255 , 128));

    /////////napis start i wyjdź z gry////////
    sf::Texture start, k;
    k.loadFromFile("img/koniec.png");
    //sf::Sprite kc;
   /* kc.setTexture(k);
    kc.setPosition(280,500);*/



    window.setMouseCursorVisible(false);

    sf::Texture text1,boss,bw;
    bw.loadFromFile("img/Boss_weapon.png");

    boss.loadFromFile("img/boss1.png");
    text1.loadFromFile("img/weapon.png");


    SpaceShip s(window,text1);
    int shot_frequency=10;//częstotliwość strzałów
    int change_frequency=10;//częstotliwość zmiany broni
    bool m_b = false;// zmienna m_b ma wartość false gdy mini bossa nie ma na mapie
    int experience = 0;//doświadczenie
    int neededExp = 500;//potrzebne doświadczenie do upgradu
    int stage = 0;//faza walki z bossem

    ////////napis wygrałeś//////////
    sf::Texture w;
    w.loadFromFile("img/win.png");
    sf::Sprite win;
    win.setTexture(w);
    win.setPosition(20,200);
    win.setColor(sf::Color(255, 255,255 , 128));

    ///////////napis przegrałeś/////////
    sf::Texture l;
    l.loadFromFile("img/lose.png");
    sf::Sprite lose;
    lose.setTexture(l);
    lose.setPosition(20,200);
    lose.setColor(sf::Color(255, 255,255 , 128));

    //////////tekstura ulepszeń////////
    sf::Texture upg;
    upg.loadFromFile("img/upgrade.png");

    ////////tekstura wrogów////////////
    sf::Texture text2;
    text2.loadFromFile("img/wrogowie.png");

    ////////////////efekty dźwiękowe///////////
    sf:: SoundBuffer bum,shot;
    if(!bum.loadFromFile("audio/bum.wav")) return 0;
    if(!shot.loadFromFile("audio/shot.wav")) return 0;
    sf::Sound sound,sound2;
    sound.setBuffer(bum);
    sound2.setBuffer(shot);
    sound2.setVolume(3);//3
    sound.setVolume(10);//10

    /////////muzyka w tle//////////////////////
    sf::Music music;
    if(!music.openFromFile("audio/1.ogg")) return 0;
    music.setVolume(50);
    music.setLoop(true);
    music.play();
    /////////////////////////////////////

    int licznik = 0;//licznik dzięki któremu pojawiają się przeciwnicy
    int licz = 0;// licznik dzięki któremu przeciwnicy strzelają
    int licz2 = 0;//licznik dzięki któremu mini boss strzela
    int licz3 = 0;//licznik dzięki któremu boss strzela


    bool bs = false;//// zmienna bs ma wartość true gdy walczysz z bossem



    std::vector<std::unique_ptr<Upgrades>> upgrades; //konstener z upgradami. w zasadzie to nie jest on
    //potrzebny bo pojawia się tylko jeden, ale w przyszłości jak będę ulepszał grę to coś z tym zrobię i dodam możliwość np.
    // wyboru ulepszenia

    std::vector<std::unique_ptr<Enemys>> enemys;//kontener z przeciwnikami

    int value;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&shot_frequency>=10)//strzał po kliknięciu LPM
            {
                s.attack();
                shot_frequency=0;
                sound2.play();
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))&&change_frequency>=10)
            //zmiana broni po klinięciu w Shift(na początku ma się tylko jedną broń więc Shift nic nie robi)
            {
                s.change_weapon();
                change_frequency=0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//zatrzymanie gry po wciśnięciu ESC
            {
                music.pause();
                window.setMouseCursorVisible(true);
                if(!pauzeGame(window,pozycja,space,cont,kc)) return 0;
                window.setMouseCursorVisible(false);
                s.position(window);
                music.play();
            }
        }

        if(experience>=neededExp)//sprawdza czy gracz ma wystarczająco doświadczenia
        {
            experience+=-neededExp;
            neededExp+=100;

            int los1,los2;
            los1 = (rand()%10)+1;//wylosowanie upgradu
            los2 = (rand()%1300)+100;//wylosowanie położenia startowego upgradu
            upgrades.push_back(std::unique_ptr<Upgrades>(new Upgrades(upg,los2,-30,los1)));//stworzenie upgradu
        }

        //////////////tworzenie przeciwników////////////////////////////////////////////////
        switch(licznik)
        {
        case 0:
        case 100:
        case 200:
        case 300:
        case 400:
        case 600:
        case 800:
        case 1000:
        case 1200:
        case 1400:
        case 1700:
        case 2000:
        case 4900:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,1,text2,false)));
        }
        break;
        case 500:
        case 700:
        case 900:
        case 1500:
        case 1800:
        case 2100:
        case 2300:
        case 2500:
        case 2700:
        case 2900:
        case 5100:
        case 5900:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,1,text2,false)));
        }
        break;
        case 1100:
        case 1300:
        case 1600:
        case 1900:
        case 2200:
        case 2400:
        case 2600:
        case 2800:
        case 3000:
        case 5300:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,1,text2,text1,false)));
        }
        break;
        case 3400:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(505,-30,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(335,-45,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(645,-40,3,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(1205,-42,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(1265,-80,4,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(250,-157,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(335,-204,2,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(316,-303,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(645,-192,2,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(955,-225,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(797,-214,4,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(519,-249,3,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(64,-239,3,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(25,-330,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(335,-345,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(645,-340,3,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(955,-342,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(1105,-280,4,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(250,-457,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(385,-504,2,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(1245,-492,2,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(1001,-525,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(97,-514,4,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(156,-503,1,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(469,-549,3,text2)));
            enemys.push_back(std::unique_ptr<Enemys>(new Meteor(664,-539,3,text2)));
        }
        break;
        case 3600:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Mini_boss(-150,300,1,text2,text1)));
            m_b = true;
        }
        break;
        case 3700:
        case 3900:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,1,text2,false)));
        }
        break;
        case 3800:
        case 4000:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,true)));
        }
        break;
        case 4100:
        case 4300:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,1,text2,false)));
        }
        break;
        case 4200:
        case 4400:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,true)));
        }
        break;
        case 4500:
        case 4700:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,1,text2,text1,false)));
        }
        break;
        case 4600:
        case 4800:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 5000:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,true)));
        }
        break;

        case 5200:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,true)));
        }
        break;

        case 5400:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 5500:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,1,text2,false)));
        }
        break;
        case 5600:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,1,text2,true)));
        }
        break;
        case 5700:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,1,text2,false)));
        }
        break;
        case 5800:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,1,text2,text1,true)));
        }
        break;

        case 6000:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,1,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,1,text2,text1,true)));
        }
        break;
        case 6100:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,false)));
        }
        break;
        case 6200:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,true)));
        }
        break;
        case 6300:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,false)));
        }
        break;
        case 6400:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 6500:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,1,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,false)));
        }
        break;
        case 6600:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,1,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 6700:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,false)));
        }
        break;
        case 6800:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,true)));
        }
        break;
        case 6900:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(1265,-30,2,text2,false)));
        }
        break;
        case 7000:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(335,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Easy(955,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 7100:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(25,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(335,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(645,-30,2,text2,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(955,-30,2,text2,text1,false)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(1265,-30,2,text2,false)));
        }
        break;
        case 7200:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(25,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(335,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(645,-30,2,text2,text1,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Medium(955,-30,2,text2,true)));
            enemys.push_back(std::unique_ptr<Enemys>(new Hard(1265,-30,2,text2,text1,true)));
        }
        break;
        case 7600:
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Boss(524,-300,1,boss,bw)));
            bs = true;
        }
        break;

        }

        licz++;
        licz2++;
        shot_frequency++;
        change_frequency++;

        if(m_b&&!bs)licznik = 3690;//po pojawieniu się minibossa licznik zatrzymuje się na 3690(chyba że jednocześnie walczysz z bossem)
        if(!m_b)licznik++;//gdy nie ma minibossa licznik normalnie rośnie
        if(stage==3&&!m_b)//po rozpoczęciu 3 fazy walki z bossem pojawia się miniboss
        {
            enemys.push_back(std::unique_ptr<Enemys>(new Mini_boss(-150,300,1,text2,text1)));
            m_b = true;
        }

        value = gameMechanics(enemys,s,window,music,pozycja,space,lose,licz,sound2,licz2,licz3,experience,m_b,stage,sound,win);

        if(value==1)return 1;
        if(value==0)return 0;

        upgrade(s,upgrades);


        if(licz>=100) licz = 0;//reset licznika
        if(licz2>=25) licz2 = 0;//reset licznika
        if(bs)licz3++;//podczas walki z bossem licznik rośnie


        s.move(window);

        window.clear();
        window.draw(space);

        for(std::vector<std::unique_ptr<Enemys>>::iterator itr = enemys.begin(), koniec = enemys.end(); itr != koniec; ++itr)
        {
            for(std::vector<std::unique_ptr<Enemys>>::iterator i = enemys.begin(),k = enemys.end(); i != k; ++i)
            {
                if(i!=itr&&(*itr)->pozycja_wroga.intersects((*i)->pozycja_wroga)&&(*itr)->Visible&&(*i)->Visible&&(*itr)->Type!=4)
                {
                    if((*itr)->right == false) (*itr)->right=true;
                    else (*itr)->right = false;
                }
            }
            (*itr)->draw(window);
            (*itr)->move(s.x,stage);
        }

        for(std::vector<std::unique_ptr<Upgrades>>::iterator itr = upgrades.begin(), koniec = upgrades.end(); itr != koniec; ++itr)
        {
            (*itr)->draw(window);
            (*itr)->move();
        }
        s.draw(window);
        window.display();
    }

    return 0;
}

