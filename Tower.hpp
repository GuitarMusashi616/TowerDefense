// Tower.hpp
// CS202 - Spring 2018
// Tower class header for tower defense game

#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Wave.h"
#include "clickable.hpp"
#include "Player.hpp"
#include <memory>
#include <vector>


class Tower : public sf::Sprite, public Clickable {
public:
	Tower();
	Tower(const sf::Texture &, const sf::Vector2i &);
	~Tower();
	int update(Wave &);
	sf::Time getClock() const;
	void restartClock();
    void onClick();
    void setActive();
	void setTowerType(int);
	int getType() const;
    sf::Sprite _getSprite();
    sf::CircleShape getThisGhost();
    void upgrade();
    sf::FloatRect getCollisionBox();
    void sell(const std::vector<std::shared_ptr<Tower>> &towers);

private:
protected:
	sf::Vector2f _position;
	sf::Sprite _sprite;
	sf::IntRect _rect;
    sf::FloatRect _collisionBounds;
	sf::Texture _texture;
	sf::Clock _timer;
	sf::Time _lastTime;
	std::vector<sf::IntRect> _towerTypes;
	int _type;
};

class ArcherTower : public Tower {
	ArcherTower(const sf::Texture &, const sf::Vector2i &);
};

class CannonTower : public Tower {
	CannonTower(const sf::Texture &, const sf::Vector2i &);
};

class CrossbowTower : public Tower {
	CrossbowTower(const sf::Texture &, const sf::Vector2i &);
};



bool findTower(const std::vector<std::shared_ptr<Tower>> &towers,sf::Vector2i &position);

#endif // !TOWER_HPP
