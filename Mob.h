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
	int getHealth() const;

protected:
	int _health;
	int _speed;
	int _positionKey;
	coord _position;
	sf::Sprite _sprite;
};

class DynamicMob : public Mob {
	//only use with "new"
	//no longer needed
public:
	DynamicMob() = delete;
	DynamicMob(const sf::Texture &);
	~DynamicMob() override;
};

std::unique_ptr<Mob> mobFactory(char c,const sf::Texture &texture, int speed);

#endif