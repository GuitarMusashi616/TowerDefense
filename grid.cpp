
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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

Grid::Grid(sf::Window const & app)
{
//    int xWindow = app.getSize().x;
//    int yWindow = app.getSize().y;
    int xWindow = 680;
    int yWindow = 500;
    
    _tileSize = gcd(xWindow,yWindow);

    _ySize = yWindow / _tileSize;
    _xSize = xWindow / _tileSize;

    
    cout << "X: " << _xSize << " Y: " << _ySize << endl;
    
    for(auto y = 0; y < _ySize; y++)
    {
        vector<shared_ptr<Tile>> row;

        //Build  row
        for(auto i = 0; i < _xSize; i++)
        {
            shared_ptr<Tile> newTile = make_shared<Tile>(i * _tileSize, 0, _tileSize);
            row.push_back(newTile);
        }
    
        _grid.push_back(row);

    }
 
    //For every row
    for(auto y = 0; y < _ySize; y++)
    {
        //for every item in row adjust x positin
        for(auto x = 0; x < _xSize ; x++)
        {
            (*_grid[y][x]).setPosition((*_grid[y][x]).getPosition().x, y * _tileSize);
        }
    }
}

shared_ptr<Tile> Grid::getTile(const sf::Vector2f & vector) const {
    return _grid[vector.y / _tileSize][vector.x / _tileSize];
}

vector<vector<shared_ptr<Tile>>> Grid::getTiles() const{
    return _grid;
}
