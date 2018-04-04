#include "Mob.h"
#include "MobTypes.h"

Mob::Mob() : _health{ 1 }, _speed{ 1 }, _positionKey{ 0 }, _position{ 0,0 }
{
}

Mob::Mob(const sf::Texture &texture, int speed) : Mob{ texture, {0,0}, speed, speed }
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

int Mob::getHealth() const
{
	return _health;
}

//std::unique_ptr<Mob> mobFactory(char c, sf::Texture texture)
//{
//	//returns a pointer to new mob based on char
//	switch (c) {
//	case 's':
//		return std::make_unique<Ship>(texture);
//	}
//}

//Mob* mobFactory(char c, sf::Texture &texture)
//{
//	//returns a pointer to new mob based on char
//	switch (c) {
//	case 's':
//		return new DynamicMob{ texture };
//	}
//}

std::unique_ptr<Mob> mobFactory(char c, const sf::Texture &texture, int speed)
{
	//returns a pointer to new mob based on char
	switch (c) {
	case 's':
		return std::make_unique<Mob>(texture,speed);
	}
}

DynamicMob::DynamicMob(const sf::Texture &texture) :  Mob{ texture,{ 0,0 },2,2 }
{
}

DynamicMob::~DynamicMob()
{
	std::cout << "66" << std::endl;
	//delete this;
}