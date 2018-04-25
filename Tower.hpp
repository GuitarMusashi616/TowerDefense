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
	sf::IntRect &getIntRect();
	//sf::Sprite &getSprite();
	//void setPosition();
    void onClick();
    void setActive();
    sf::Sprite _getSprite();
    sf::CircleShape getThisGhost();
    void upgrade();
    sf::FloatRect getCollisionBox();
    //void sell(Towers & towers, Player & thePlayer);
private:
	sf::Vector2f _position;
	sf::Sprite _sprite;
	sf::IntRect _rect;
    sf::FloatRect _collisionBounds;
	sf::Texture _texture;
	sf::Clock _timer;
	sf::Time _lastTime;
};

bool findTower(const std::vector<std::shared_ptr<Tower>> &towers,sf::Vector2i &position);

#endif // !TOWER_HPP
