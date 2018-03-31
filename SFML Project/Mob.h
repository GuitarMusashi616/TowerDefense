#pragma once

#ifndef Mob_h
#define Mob_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct coord {
	//stores an x,y coordinate from the game window
	int x;
	int y;
};

class Mob
{
public:
	Mob();
	Mob(const sf::Texture &,const coord &,int,int);
	~Mob();
	sf::Vector2f nextPosition(std::vector<coord> &);
	sf::Sprite &getSprite();
	void setPosition(const sf::Vector2f &moveTo);
protected:
	int _health;
	int _speed;
	int _positionKey;
	coord _position;
	sf::Sprite _sprite;
};


#endif
