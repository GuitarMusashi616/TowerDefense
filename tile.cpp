
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
    
	sf::RectangleShape rectangle{ sf::Vector2f{float(tileSize), float(tileSize)} };
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


void Tile::handleEvents(sf::RenderWindow & app, sf::Event & event, const Grid & grid, const Framework & framework)
{
    if(event.type == sf::Event::MouseMoved) {
        
        sf::Vector2f viewSize = framework.getViewSize();
        sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
        
        if(worldPos.x < viewSize.x && worldPos.y < viewSize.y) {
            shared_ptr<Tile> tileClicked = grid.getTile(worldPos);
            tileClicked->setActivated();
        }
    }
}
