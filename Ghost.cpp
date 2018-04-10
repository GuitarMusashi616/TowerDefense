#include "Ghost.h"
#include <iostream>

Ghost::Ghost(float x, float y) : RectangleShape{}
{
	setFillColor(sf::Color{0,255,0,100});
	setOrigin(41, 60); 
	auto m = sf::Mouse::getPosition();
	setPosition(x,y);
	setSize(sf::Vector2f{ 82,120 });
	//setOutlineThickness(5);
	//setOutlineColor(sf::Color::Black);
}


bool Ghost::isOverlapping() const{
    return _collides;
}

void Ghost::setCollision(bool collides) {
    _collides = collides;
    if(_collides) {
        this->setFillColor(sf::Color{255,0,0,100});
    } else {
        this->setFillColor(sf::Color{0,255,0,100});
    }

}


