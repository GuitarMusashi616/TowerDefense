#ifndef Mob_h
#define Mob_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "HealthBar.h"

struct creep {
	std::string mobType;
	int count = 1;
	int millisecondsBetween = 200;
};

struct coord {
	//stores an x,y coordinate from the game window
	int x;
	int y;
};

class Mob
{
public:
	Mob();
	Mob(const sf::Texture &,int health=5, int speed=8);
	virtual ~Mob();
	sf::Vector2f nextPosition(std::vector<coord> &);
	sf::Sprite &getSprite();
	HealthBar &getHealthBar();
	void virtual setPosition(const sf::Vector2f &moveTo);
	void setHealth(int health);
	coord getPosition() const;
	int getHealth() const;
	bool getEscaped() const;
	int getMaxHealth() const;
	std::string getType() const;
protected:
	int _health;
	int _maxHealth;
	int _speed;
	int _positionKey = 0;
	bool _escaped = false;
	coord _position;
	sf::Sprite _sprite;
	HealthBar _healthBar;
	std::string _type;
};

std::unique_ptr<Mob> mobFactory(char c,const sf::Texture &texture, int speed);

#endif
