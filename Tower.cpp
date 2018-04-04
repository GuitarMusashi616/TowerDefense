// Tower.cpp
// CS202 - Spring 2018
// Tower class for Tower Defense game

#include<SFML/Graphics.hpp>
#include "Mob.h"
#include "Tower.hpp"

Tower::Tower() :_position{ 0,0 } {}

Tower::Tower(const sf::Texture &texture, const coord &pos) : _sprite{ texture }, _position{ pos } { 
}

Tower::~Tower(){}


sf::Sprite & Tower::getSprite() {
	return _sprite;
}


void Tower::setPosition() {
	_sprite.setPosition(sf::Vector2f{ float(_position.x),float(_position.y) });
}

DynamicTower::DynamicTower(const sf::Texture &texture, const sf::Vector2i & pos) : Tower{ texture, {pos.x,pos.y} } {
}

DynamicTower::~DynamicTower()
{
	delete this;
}

Tower* towerFactory(const sf::Texture &texture, const sf::Vector2i &mousePos ) {
		return new DynamicTower{ texture, mousePos };
}