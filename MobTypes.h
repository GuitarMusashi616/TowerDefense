#pragma once
#include "Mob.h"

class KnightMob :
	public Mob
{
public:
	//KnightMob();
	KnightMob(sf::Texture &);
	void setPosition(const sf::Vector2f &moveTo) override;
	//~KnightMob();
protected:
	sf::IntRect _intRect;
	sf::Clock _gallopTimer;
	int _boxHeight;
	int _lastBox;
	int _firstBox;
	int _millisecondsPerFrame;
};

class Footman : public Mob {
public:
	Footman(sf::Texture &);
	void setPosition(const sf::Vector2f &moveTo) override;
protected:
	sf::IntRect _intRect;
	sf::Clock _walkTimer;
	std::vector<coord> _spriteSheetCoordinates;
	int _boxHeight;
	int _boxWidth;
	int _millisecondsPerFrame;
	int _frame;
	bool _iterateDown;
};

class Gyrocopter : public Footman {
public:
	Gyrocopter(sf::Texture &);
};

class GriffonRider : public Footman {
public:
	GriffonRider(sf::Texture &);
};