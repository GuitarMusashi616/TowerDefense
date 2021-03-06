

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "tile.hpp"


class Grid {
public:
    Grid(const sf::Window & app);
    std::vector<std::vector<std::shared_ptr<Tile>>> getTiles() const;
    std::shared_ptr<Tile> getTile(const sf::Vector2f & vector) const;
private:
    int _xSize;
    int _ySize;
    int _tileSize;
    std::vector<std::vector<std::shared_ptr<Tile>>> _grid;
    std::shared_ptr<Tile> _activated;
};


#endif /* grid_hpp */
