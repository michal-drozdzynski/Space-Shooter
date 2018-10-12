#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "enemys.h"
#include "upgrades.h"

int startGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&st, sf::Sprite&kc);
int pauzeGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&cont, sf::Sprite&kc);
int winOrLoseGame(sf::RenderWindow& window,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite&wl);
int gameMechanics(std::vector<std::unique_ptr<Enemys>>& enemys,SpaceShip& s,sf::RenderWindow& window,
sf::Music& music,sf::Vector2i& pozycja,sf::Sprite& space,sf::Sprite& lose,int& licz,sf::Sound& sound2,
int& licz2,int& licz3,int& experience,bool& m_b,int&stage,sf::Sound& sound,sf::Sprite& win);
void upgrade(SpaceShip& s,std::vector<std::unique_ptr<Upgrades>>&upgrades);

int first_mission(sf::RenderWindow& window);//pierwsza misja, być może dodam kiedyś więcej
