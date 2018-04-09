#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#ifndef Mob_h
#define Mob_h

struct coord {
	//stores an x,y coordinate from the game window
	int x;
	int y;
};

class Mob
{
public:
	Mob();
	Mob(const sf::Texture &,int);
	Mob(const sf::Texture &,const coord &,int,int);
	virtual ~Mob();
	sf::Vector2f nextPosition(std::vector<coord> &);
	sf::Sprite &getSprite();
	void setPosition(const sf::Vector2f &moveTo);
	void setHealth(int health);
	coord getPosition() const;
	//coord getCenterPosition() const;
	int getHealth() const;
	bool getEscaped() const;

protected:
	int _health;
	int _speed;
	int _positionKey;
	bool _escaped;
	coord _position;
	sf::Sprite _sprite;
};

std::unique_ptr<Mob> mobFactory(char c,const sf::Texture &texture, int speed);

#endif