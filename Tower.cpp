
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Tower.hpp"
#include <memory>

Tower::Tower() : _rect{ 275,100,82,119 }, _position{ sf::Vector2i{0,0} }, _lastTime{ sf::Time::Zero }, _collisionBounds{275,100,82,119} {
	setOrigin(41, 60);
}

Tower::Tower(const sf::Texture &texture, const sf::Vector2i &pos) : _position{ pos }, _texture{ texture }, _lastTime{ sf::Time::Zero }, _type{ 0 }, _towerTypes {
	{275,100,82,119},
	{353,101,76,119},
	{429,144,76,72},
	{502,134,76,83},
	{576,102,81,11},
	{279,221,73,100},
	{355,236,73,84},
	{431,216,73,101},
	{503,215,73,98},
	{581,215,71,104},
}
{
	setTexture(_texture);
	setPosition(_position);
	setTextureRect(_towerTypes[0]);
	setOrigin(_towerTypes[0].width/2, _towerTypes[0].height/2);
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

void Tower::onClick() {
    std::shared_ptr<Clickable> clicked = shared_from_this();
    Clickable::select(clicked);
    
};

sf::CircleShape Tower::getThisGhost() {
    int radius = 100;
    sf::CircleShape circle = getGhost();
    circle.setOrigin(radius, radius);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color(0,0,0,0));
    circle.setOutlineColor(sf::Color(191, 23, 214, 100));
    circle.setOutlineThickness(5);
    return circle;
    
}

void Tower::setActive() {
    Clickable::select(shared_from_this());
}

void Tower::setTowerType(int numType)
{
	setTextureRect(_towerTypes[numType]);
	_type = numType;
	//might need to update too
}

int Tower::getType() const
{
	return _type;
}

bool findTower(const std::vector<std::shared_ptr<Tower>> &towers, sf::Vector2i &position)
{
	for (auto i = 0; i < towers.size(); i++) {
		auto towerBounds = towers[i]->getGlobalBounds();
		if (towerBounds.left <= position.x && (towerBounds.left + towerBounds.width) >= position.x) {
			if (towerBounds.top <= position.y && (towerBounds.top + towerBounds.height) >= position.y) {
				return true;
			}
		}
	}
	return false;
}

ArcherTower::ArcherTower(const sf::Texture &texture, const sf::Vector2i &position) : Tower{texture,position}
{
	setTextureRect(_towerTypes[1]);
	_type = 1;
}

CannonTower::CannonTower(const sf::Texture &, const sf::Vector2i &)
{
	setTextureRect(_towerTypes[2]);
	_type = 2;
}

CrossbowTower::CrossbowTower(const sf::Texture &, const sf::Vector2i &)
{
	setTextureRect(_towerTypes[3]);
	_type = 3;
}
