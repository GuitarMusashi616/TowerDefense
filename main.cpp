
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include <ResourcePath.hpp>

#include "screens.hpp"
#include "game.hpp"
#include "menu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(680, 500), "SFML window");
    
    std::vector<Screens*> screens;
    MenuScreen screen0;
    screens.push_back(&screen0);
    GameScreen screen1;
    screens.push_back(&screen1);
    int screen = 0;
    
    
    while (screen >= 0)
    {
        screen = screens[screen]->run(window);
    }
	return EXIT_SUCCESS;
}
