
#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

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
