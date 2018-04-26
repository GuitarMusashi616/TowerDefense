#pragma once
#ifndef Towers_h
#define Towers_h

#include <vector>
#include <memory>
#include "Tower.hpp"

class Towers : public std::vector <std::shared_ptr<Tower> >
{
public:
	bool findTower(const sf::Vector2i &position, int &iteratorValue) const;
	void deleteTower(const int iteratorValue);
};

#endif
