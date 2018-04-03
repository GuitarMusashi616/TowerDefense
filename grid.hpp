

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

struct TileCoord
{
    int x;
    int y;
};

class Tile : public std::enable_shared_from_this<Tile> {
public:
    Tile(int x, int y);
    void setPosition(int x, int y);
    TileCoord getPosition();
    sf::RectangleShape getTile();
    void setActivated();
    bool isActivated();
    std::shared_ptr<Tile> getActivated();
private:
    sf::RectangleShape _square;
    TileCoord _position;
    static Tile* _activated;
};

class Grid {
public:
    Grid(int xSize, int ySize, int tileSize);
    std::vector<std::vector<std::shared_ptr<Tile>>> getTiles();
    std::shared_ptr<Tile> getTile(int x, int y);
private:
    int _xSize;
    int _ySize;
    int _tileSize;
    std::vector<std::vector<std::shared_ptr<Tile>>> _grid;
    std::shared_ptr<Tile> _activated;
};


#endif /* grid_hpp */
