#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "Mob.h"

class Wave : public std::vector< std::unique_ptr<Mob> >
{
public:
	//void killCircle(sf::Vector2i position, int radius);
	void killBox(int centerX, int centerY, int width, int height);
	bool detectBox(int centerX, int centerY, int width, int height);
	void killCircle(double centerX, double centerY, int radius);
	//void killNearest;
};

