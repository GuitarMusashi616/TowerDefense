
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Tower.hpp"

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

void Tower::onClick() {
    std::cout << this << " Tower clicked!" << std::endl;
    
    std::cout << _position.x << ", " << _position.y << std::endl;
};


sf::CircleShape Tower::getThisGhost() {
   // cout << clickable::getGhost().
    int radius = 50;
    sf::CircleShape circle = getGhost();
    //circle.setPosition(_position.x, _position.y);
    circle.setOrigin(radius, radius);
    circle.setPosition(_position);
    circle.setFillColor(sf::Color(255,0,0,100));
    return circle;
    
}
sf::IntRect & Tower::getIntRect()
{
	return _rect;
}

bool findTower(const std::vector<std::unique_ptr<Tower>> &towers, sf::Vector2i &position)
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
