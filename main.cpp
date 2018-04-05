
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Mob.h"

#include "Tower.hpp"
#include "ResourcePath.hpp"
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

//string resourcePath() {
//	//comment out if on mac!
//	return "";
//}

int main()
{

    sf::RenderWindow window(sf::VideoMode(680, 500), "Rad Tower Defense", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(25);
    
    Framework framework(window);

    std::vector<Screens*> screens;
    MenuScreen screen0;
    screens.push_back(&screen0);
    GameScreen screen1;
    screens.push_back(&screen1);
    int screen = 0;
    
    sf::Event event;

    while (screen >= 0)
    {
        screen = screens[screen]->run(window, framework);
    }
    
    return EXIT_SUCCESS;

}
