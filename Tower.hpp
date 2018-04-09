// Tower.hpp
// CS202 - Spring 2018
// Tower class header for tower defense game

#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Wave.h"

class Tower : public sf::Sprite {
public:
	Tower();
	Tower(const sf::Texture &, const sf::Vector2i &);
	~Tower();
	int update(Wave &);
	sf::Time getClock() const;
	void restartClock();
	//sf::Sprite &getSprite();
	//void setPosition();
private:
	sf::Vector2f _position;
	sf::Sprite _sprite;
	sf::IntRect _rect;
	sf::Texture _texture;
	sf::Clock _timer;
	sf::Time _lastTime;
};

#endif // !TOWER_HPP
