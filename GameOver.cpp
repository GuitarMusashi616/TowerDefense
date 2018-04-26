#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"
#include "GameOver.hpp"
#include "framework.hpp"

using std::cout;
using std::endl;

int GameOver::run(sf::RenderWindow &app, const Framework & framework) {
    
    // Process events
    sf::Event event;
    bool running = true;
    //load textures
    
    sf::Texture t1;
    t1.loadFromFile(resourcePath() + "Gameover.png");
    
    sf::Sprite background{ t1 };
    
    while(running) {
        while (app.pollEvent(event))
        {
            framework.handleEvents(app, event);
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

