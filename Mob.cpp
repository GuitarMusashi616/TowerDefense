#include "Mob.h"
#include "MobTypes.h"

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
	if (_positionKey == coords.size()-1) {
		this->setHealth(0);
	}
	else if (coords[_positionKey].x == _position.x && coords[_positionKey].y == _position.y) {
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

Mob* mobFactory(char c, sf::Texture &texture)
{
	//returns a pointer to new mob based on char
	switch (c) {
	case 's':
		return new DynamicMob{ texture };
	}
}

DynamicMob::DynamicMob(const sf::Texture &texture) : Mob{ texture,{ 0,0 },1,1 }
{
}

DynamicMob::~DynamicMob()
{
	delete this;
}