#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"
#include "menu.hpp"

using std::cout;



int MenuScreen::run(sf::RenderWindow &app) {

    // Process events
    sf::Event event;
    bool running = true;
    //load textures
    
    sf::Texture t1;
    t1.loadFromFile(resourcePath() + "MenuScreen.png");
    sf::Sprite background{ t1 };

    while(running) {
        while (app.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                app.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                app.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed)
            {
                    cout << "Mouse Clicked: Starting game!";
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

