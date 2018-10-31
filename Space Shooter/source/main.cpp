#include "contents.h"

int main()
{
    srand( time( NULL ) );

    //pętla służy do zapętlania misji
    sf::RenderWindow window(sf::VideoMode(1440, 900), "My window");
    sf::Vector2i pozycja = sf::Mouse::getPosition(window);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Texture background;
    background.loadFromFile("img/menuback.jpg");
    sf::Sprite space;
    space.setTexture(background);

    sf::Sprite num[4];
    sf::Sprite samouczek;
    sf::Texture num1,num2,num3,num4,tutorial;
    tutorial.loadFromFile("img/tutorial.png");
    num1.loadFromFile("img/1.png");
    num2.loadFromFile("img/2.png");
    num3.loadFromFile("img/3.png");
    num4.loadFromFile("img/mark.png");

    num[0].setTexture(num1);
    num[1].setTexture(num2);
    num[2].setTexture(num3);
    num[3].setTexture(num4);

    samouczek.setTexture(tutorial);
    samouczek.setPosition(20,100);

    num[0].setPosition(20,450);
    num[1].setPosition(520,450);
    num[2].setPosition(1020,450);
    //num[3].setPosition(1260,450);



    sf::Sprite kc,st;
    sf::Texture start, k;
    start.loadFromFile("img/start.png");
    k.loadFromFile("img/koniec.png");
    st.setTexture(start);
    kc.setTexture(k);
    st.setPosition(20,150);
    kc.setPosition(20,500);
    st.setColor(sf::Color(255, 255,255 , 128));
    kc.setColor(sf::Color(255, 255,255 , 128));
    while(true)
    {
        if(startGame(window,pozycja,space,st,kc)==1)
        {
            if(chooseLevel(window,space,num,samouczek)==1)
            {
                if(!first_mission(window,kc)) return 0;
            }
           // while(!first_mission(window,kc)) return 0;
        }
        else return 0;
    }

    return 0;
}


