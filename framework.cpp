
#include "framework.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

Framework::Framework(sf::Window &app, const sf::Vector2f & viewSize)
{
    float aspectRatio = (float) app.getSize().x / (float) app.getSize().y;
    _xSize = app.getSize().x;
    _ySize = app.getSize().y;
    _aspectRatio = aspectRatio;
    _viewSize = viewSize;
    _initialWindowSize = sf::Vector2f(app.getSize().x, app.getSize().y);
}

float Framework::getAspectRatio() const
{
    return _aspectRatio;
}

sf::Vector2f Framework::getCorrectedMousePosition(const sf::Window & app, const sf::Vector2f & vector) const {
    float fixedX = (float(vector.x) / app.getSize().x) * _xSize;
    float fixedY = (float(vector.y) / app.getSize().y) * _ySize;
    return sf::Vector2f(fixedX, fixedY);
}

sf::Vector2f Framework::getCorrectedMousePosition(const sf::Window & app, float x, float y) const
{
    float fixedX = (x / app.getSize().x) * _xSize;
    float fixedY = (y / app.getSize().y) * _ySize;
    return sf::Vector2f(fixedX, fixedY);
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

int Framework::getWindowX() const
{
    return _xSize;
}

int Framework::getWindowY() const
{
    return _ySize;
}

sf::Vector2f Framework::getViewSize() const {
    return _viewSize;
}

sf::Vector2f Framework::getInitialWindowSize() const {
    return _initialWindowSize;
}

