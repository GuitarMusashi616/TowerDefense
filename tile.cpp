
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "grid.hpp"
#include "framework.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

shared_ptr<Tile> Tile::_activated;


Tile::Tile(int x, int y, int tileSize)
{
    _position.x = x;
    _position.y = y;
    
    sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize));
    sf::Color transparentRed(255, 0, 0, 100);
    rectangle.setFillColor(transparentRed);
    _square = rectangle;
}

void Tile::setPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

TileCoord Tile::getPosition() {
    return _position;
}

sf::RectangleShape Tile::getTile() {
    return _square;
}


void Tile::setActivated() {
    _activated = shared_from_this();
}

bool Tile::isActivated() {
    return shared_from_this() == _activated;
}

shared_ptr<Tile> Tile::getActivated() {
    return _activated;
}


void Tile::handleEvents(sf::Window & app, sf::Event & event, const Grid & grid, const Framework & framework)
{
    if(event.type == sf::Event::MouseMoved) {
        int x{ sf::Mouse::getPosition(app).x }, y{ sf::Mouse::getPosition(app).y };
        
        // to Prevent crashing (sometimes the mouse reads the value before
        sf::Vector2<float> corrected = framework.getCorrectedMousePosition(app, sf::Vector2f(x,y));
        
        if(corrected.x <= 680 && corrected.y <= 500) {
            shared_ptr<Tile> tileClicked = grid.getTile(corrected);
            tileClicked->setActivated();
        } else {
            cout << "Would have crashed here!" << endl;
        }
    }
}
