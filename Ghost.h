#pragma once
#include <SFML/Graphics.hpp>
#include "framework.hpp"
#include "grid.hpp"

class Ghost : public sf::RectangleShape
{
public:
	Ghost(float,float);
    void setCollision(bool collides);
    bool isOverlapping() const;
    static void handleEvents(sf::RenderWindow & app, sf::Event & event, const Grid & grid, const Framework & framework);
    
private:
    bool _collides;
};

