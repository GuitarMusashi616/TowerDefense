#include "Mob.h"

Mob::Mob() : _health{ 1 }, _speed{ 1 }, _positionKey{ 0 }, _position{ 0,0 }
{
}

Mob::Mob(const sf::Texture &texture, const coord &position, int health, int speed) : _sprite{texture}, _health { health }, _speed{ speed }, _positionKey{ 0 }, _position{ position }
{
}

Mob::~Mob()
{
}

sf::Vector2f Mob::nextPosition(std::vector<coord> &coords)
{
	//finds next location to move to
	if (coords[_positionKey].x > _position.x) {
		_position.x += 1;
	}
	else if (coords[_positionKey].x < _position.x) {
		_position.x -= 1;
	}
	if (coords[_positionKey].y > _position.y) {
		_position.y += 1;
	}
	else if (coords[_positionKey].y < _position.y) {
		_position.y -= 1;
	}
	if (coords[_positionKey].x == _position.x && coords[_positionKey].y == _position.y) {
		_positionKey++;
	}
	return sf::Vector2f{ float(_position.x),float(_position.y) };
}

sf::Sprite & Mob::getSprite()
{
	//returns the sprite for rendering
	return _sprite;
}

void Mob::setPosition(const sf::Vector2f &moveTo)
{
	//moves the sprite
	_sprite.setPosition(moveTo);
}
