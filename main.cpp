
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>


#include "screens.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "framework.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

string resourcePath() {
	//comment out if on mac!
	return "Resources/";
}

int main()
{
    //Grab these from a config file eventually
    const sf::Vector2f WINDOWSIZE(680,500);
    const sf::Vector2f VIEWSIZE(680,500);
    
    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE.x, WINDOWSIZE.y), "Rad Tower Defense", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(25);
    
    Framework framework(window, VIEWSIZE);

    std::vector<Screens*> screens;

    MenuScreen screen0;
    screens.push_back(&screen0);

    GameScreen screen1;
    screens.push_back(&screen1);

	//GameOver 
	MenuScreen screen2;
	screens.push_back(&screen2);

    int screen = 0;
    
    sf::Event event;

    while (screen >= 0)
    {
        screen = screens[screen]->run(window, framework);
    }
    
    return EXIT_SUCCESS;

}
