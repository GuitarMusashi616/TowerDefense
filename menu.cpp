#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"
#include "menu.hpp"
#include "framework.hpp"

using std::cout;
using std::endl;

int MenuScreen::run(sf::RenderWindow &app, const Framework & framework) {

    // Process events
    sf::Event event;
    bool running = true;
    //load textures
    
    sf::Texture t1;
    t1.loadFromFile(resourcePath() + "MenuScreen.png");
    

    sf::Sprite background{ t1 };
    //background.setScale(2, 2);

    while(running) {
        while (app.pollEvent(event))
        {
            framework.handleEvents(app, event);
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                    cout << "Mouse Clicked: Starting game!" << endl;
                    return 1;
            }
        }
        // Clear screen
        app.clear();
        
        //draw to buffer
        app.draw(background);
        
        // Update the window
        app.display();
    }
    return -1;
}

