// Tower.cpp
// CS202 - Spring 2018
// Tower class for Tower Defense game

#include<SFML/Graphics.hpp>
#include <iostream>
#include "Mob.h"
#include "Tower.hpp"
#include "explosion.h"

Tower::Tower() : _rect{ 275,100,82,119 }, _position{ sf::Vector2i{0,0} }, _lastTime{ sf::Time::Zero } {
	setOrigin(41, 60);
}

Tower::Tower(const sf::Texture &texture, const sf::Vector2i &pos) : _rect{ 275,100,82,119 }, _position{ pos }, _texture{texture}, _lastTime{ sf::Time::Zero }
{
	setTexture(_texture);
	setPosition(_position);
	setTextureRect(_rect);
	setOrigin(41, 60);
}

Tower::~Tower(){
}

int Tower::update(Wave &detect)
{
	auto time = _timer.getElapsedTime();
	if ( time.asSeconds() >= 5 ) {
		_timer.restart();
		return 1;
	}
	return 0;
}

sf::Time Tower::getClock() const
{
	return _timer.getElapsedTime();
}

void Tower::restartClock()
{
	_timer.restart();
}

