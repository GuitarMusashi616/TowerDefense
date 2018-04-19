#include "Ghost.h"
#include <iostream>

Ghost::Ghost(float x, float y) : RectangleShape{}
{
	//originally 41,60 -> 82,120
	setFillColor(sf::Color{255,0,0,100});
	setOrigin(41, 20); 
	auto m = sf::Mouse::getPosition();
	setPosition(x,y);
	setSize(sf::Vector2f{ 82,82 });
	//setOutlineThickness(5);
	//setOutlineColor(sf::Color::Black);
}

