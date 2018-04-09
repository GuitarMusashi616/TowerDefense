#include "Mob.h"
#include "MobTypes.h"
#include "explosion.h"

Mob::Mob() : _health{ 1 }, _speed{ 1 }, _positionKey{ 0 }, _position{ -10,70 }, _escaped{false}
{
}

Mob::Mob(const sf::Texture &texture, int speed) : Mob{ texture, {-10,70}, speed, speed }
{
}

Mob::Mob(const sf::Texture &texture, const coord &position, int health, int speed) : _sprite{texture}, _health { health }, _speed{ speed }, _positionKey{ 0 }, _position{ position }, _escaped{ false }
{
	_sprite.setPosition(_position.x, _position.y);
	_sprite.setOrigin(74, 64);
}

Mob::~Mob()
{
}

sf::Vector2f Mob::nextPosition(std::vector<coord> &coords)
{
    int scaleFactor = 1;
	//finds next location to move to

	if (coords[_positionKey].x > _position.x+_speed) {
		_position.x += _speed;
	}
	else if (coords[_positionKey].x < _position.x-_speed) {
		_position.x -= _speed;
	}
	if (coords[_positionKey].y > _position.y+_speed) {
		_position.y += _speed;
	}
	else if (coords[_positionKey].y < _position.y-_speed) {
		_position.y -= _speed;
	}
	if (_positionKey == coords.size()-1) {
		this->setHealth(0);
		_escaped = true;
	}

	//if the position is within a box of coordinates from _speed by _speed, then target the next position
	else if ( (coords[_positionKey].x >= _position.x-_speed && coords[_positionKey].x <= _position.x+_speed) && (coords[_positionKey].y >= _position.y - _speed && coords[_positionKey].y <= _position.y + _speed) ) {
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

void Mob::setHealth(int health)
{
	_health = health;
}

coord Mob::getPosition() const
{
	return _position;
}

//coord Mob::getCenterPosition() const
//{
//	_sprite.
//	return ;
//}

int Mob::getHealth() const
{
	return _health;
}

bool Mob::getEscaped() const
{
	return _escaped;
}

std::unique_ptr<Mob> mobFactory(char c, const sf::Texture &texture, int speed)
{
	//returns a pointer to new mob based on char
	switch (c) {
	case 's':
		return std::make_unique<Mob>(texture, speed);
	//case 'x':
	//	return std::make_unique<Explosion>();
	}
}
