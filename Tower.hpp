// Tower.hpp
// CS202 - Spring 2018
// Tower class header for tower defense game

#ifndef TOWER_HPP_
#define TOWER_HPP_

class Tower {
public:
	Tower();
	Tower(const sf::Texture &, const coord &);
	~Tower();
	sf::Sprite &getSprite();
	void setPosition();
private:
	coord _position;
	sf::Sprite _sprite;
};

class DynamicTower : public Tower {
public:
	DynamicTower(const sf::Texture &, const sf::Vector2i &);
	~DynamicTower();
};

Tower* towerFactory(const sf::Texture &texture, const sf::Vector2i &);

#endif // !TOWER_HPP
