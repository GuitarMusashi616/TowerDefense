#pragma once
#include "Mob.h"

class Ship :
	public Mob
{
public:
	Ship();
	Ship(sf::Texture &);
	~Ship();
};

