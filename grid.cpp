
#include "grid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

Tile* Tile::_activated;

Tile::Tile(int x, int y)
{
    _position.x = x;
    _position.y = y;
    
    sf::RectangleShape rectangle(sf::Vector2f(20, 20));
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

Grid::Grid(int xSize, int ySize, int tileSize) : _xSize(xSize), _ySize(ySize), _tileSize(tileSize)
{
    //Build Default row
    
    cout << "X: " << xSize << " Y: " << ySize << endl;
    
    for(auto y = 0; y < ySize; y++)
    {
        vector<shared_ptr<Tile>> row;

        //Build  row
        for(auto i = 0; i < xSize; i++)
        {
            shared_ptr<Tile> newTile = make_shared<Tile>(i * 20, 0);
            row.push_back(newTile);
        }
    
        _grid.push_back(row);

    }
 
    //For every row
    for(auto y = 0; y < ySize; y++)
    {
        //for every item in row adjust x positin
        for(auto x = 0; x < xSize ; x++)
        {
            (*_grid[y][x]).setPosition((*_grid[y][x]).getPosition().x, y * 20);
        }
    }
}

shared_ptr<Tile> Grid::getTile(int x, int y) {
    return _grid[y / _tileSize][x / _tileSize];
}

void Tile::setActivated() {
    _activated = this;
}

bool Tile::isActivated() {
    return this == _activated;
}

shared_ptr<Tile> Tile::getActivated() {
    return shared_from_this();
}

vector<vector<shared_ptr<Tile>>> Grid::getTiles() {
    return _grid;
}
