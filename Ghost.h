
#pragma once
#include <SFML/Graphics.hpp>

class Ghost : public sf::RectangleShape
{
public:
    Ghost(float,float);
    void setCollision(bool collides);
    bool isOverlapping() const;
    
private:
    bool _collides;
};
