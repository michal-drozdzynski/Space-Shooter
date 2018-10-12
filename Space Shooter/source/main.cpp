#include "contents.h"

int main()
{
    srand( time( NULL ) );
    //pętla służy do zapętlania misji
    sf::RenderWindow window(sf::VideoMode(1440, 900), "My window");
    sf::Vector2i pozycja = sf::Mouse::getPosition(window);

    sf::Texture background;
    background.loadFromFile("img/menuback.jpg");
    sf::Sprite space;
    space.setTexture(background);

    sf::Sprite kc,st;
    sf::Texture start, k;
    start.loadFromFile("img/start.png");
    k.loadFromFile("img/koniec.png");
    st.setTexture(start);
    kc.setTexture(k);
    st.setPosition(510,150);
    kc.setPosition(280,500);
    while(true)
    {
        if(startGame(window,pozycja,space,st,kc)==1)
        {
            while(!first_mission(window)) return 0;
        }
        else return 0;
    }

    return 0;
}


