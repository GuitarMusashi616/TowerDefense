
#include "framework.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

Framework::Framework(sf::Window &app)
{
    float aspectRatio = (float) app.getSize().x / (float) app.getSize().y;
    _xSize = app.getSize().x;
    _ySize = app.getSize().y;
    _aspectRatio = aspectRatio;
}

void Framework::handleEvents(sf::Window & app, sf::Event & event) const
{
    if(event.type == sf::Event::Resized)
    {
        //Keep game to scale
        sf::Vector2u newSize(app.getSize().y * _aspectRatio, app.getSize().y);
        
        app.setSize(newSize);
    }
    
    // Close window: exit
    if (event.type == sf::Event::Closed) {
        app.close();
    }
    
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        app.close();
    }
    
    
}

float Framework::getAspectRatio() const
{
    return _aspectRatio;
}
