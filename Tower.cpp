
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Tower.hpp"
#include <memory>
#include "Player.hpp"

Tower::Tower() : _rect{ 275,100,82,119 }, _position{ sf::Vector2i{0,0} }, _lastTime{ sf::Time::Zero }, _collisionBounds{275,100,82,119} {
	setOrigin(41, 60);
}

Tower::Tower(const sf::Texture &texture, const sf::Vector2i &pos) : _rect{ 275,100,82,119 }, _position{ pos }, _texture{texture}, _lastTime{ sf::Time::Zero }, _collisionBounds{275,100,82,119}
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

sf::FloatRect Tower::getCollisionBox() {
    _collisionBounds = this->getGlobalBounds();
    _collisionBounds.height = 80;
    _collisionBounds.width = 75;
    _collisionBounds.top = _collisionBounds.top + 40;
    return _collisionBounds;
}


sf::IntRect & Tower::getIntRect()
{
	return _rect;
}

void Tower::upgrade() {
    std::cout << "Tower Upgraded" << std::endl;
    auto &intRect = this->getIntRect();
    //275, 100 original position for default tower in towers.png image
    //size of all 10 towers fit in a 380 by 214 box
    if (intRect.left < 380 + 275) {
        intRect.left += 76;
    } else if (intRect.top < 100 + 107) {
        intRect.left = 275;
        intRect.top += 107;
    }
    //how many pixels over to the next tower in the towers.png image
    this->setTextureRect(intRect);
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
