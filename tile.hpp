//
//  tile.hpp
//  TDcs
//
//  Created by Rowan Biessel on 4/3/18.
//  Copyright © 2018 Rowan Biessel. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

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
    Tile(int x, int y, int tileSize);
    void setPosition(int x, int y);
    TileCoord getPosition();
    sf::RectangleShape getTile();
    void setActivated();
    bool isActivated();
    static std::shared_ptr<Tile> getActivated();
private:
    sf::RectangleShape _square;
    TileCoord _position;
    static std::shared_ptr<Tile> _activated;
};


#endif /* tile_hpp */
