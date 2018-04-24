#ifndef Mob_h
#define Mob_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "HealthBar.h"

<<<<<<< HEAD
#ifndef Mob_h
#define Mob_h

struct creep {
	std::string mobType;
	int count = 1;
	int millisecondsBetween = 200;
};

=======
>>>>>>> 02ecf2554b96c75229456a59fe9866733ad1a00e
struct coord {
	//stores an x,y coordinate from the game window
	int x;
	int y;
};

class Mob
{
public:
	Mob();
	Mob(const sf::Texture &,int health=5, int speed=5);
	virtual ~Mob();
	sf::Vector2f nextPosition(std::vector<coord> &);
	sf::Sprite &getSprite();
	HealthBar &getHealthBar();
	void virtual setPosition(const sf::Vector2f &moveTo);
	void setHealth(int health);
	coord getPosition() const;
	//coord getCenterPosition() const;
	int getHealth() const;
	bool getEscaped() const;
	int getMaxHealth() const;
	//std::unique_ptr<Explosion> getDeathAnimation(const sf::Texture &texture);
	//defaults declared here
	//static const int maxHealth;
	//static const int defaultSpeed;
	std::string virtual getType() const;
protected:
	int _health;
	int _maxHealth;
	int _speed;
	int _positionKey = 0;
	bool _escaped = false;
	coord _position;
	sf::Sprite _sprite;
	HealthBar _healthBar;
};

std::unique_ptr<Mob> mobFactory(char c,const sf::Texture &texture, int speed);

#endif
