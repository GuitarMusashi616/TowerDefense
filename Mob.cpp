#include "Mob.h"

//defaults defined here
//const int Mob::maxHealth = 5;
//const int Mob::defaultSpeed = 5;
const sf::Vector2f startPos{ -10,70 };

Mob::Mob() : _health{ 5 }, _maxHealth{ 5 }, _speed{ 5 }, _healthBar{ -10.f,70.f,108.f,10.f }
{
}

Mob::Mob(const sf::Texture &texture, int health, int speed) : _sprite{ texture }, _maxHealth{ health }, _health{ health },_speed { speed }, _healthBar{ -10.f,70.f,108.f,10.f }
{
	setPosition(startPos);
	auto spriteBounds = _sprite.getGlobalBounds();
	//defualt origin 74,64
	_sprite.setOrigin(spriteBounds.width/2, spriteBounds.height/2);
	//_healthBar.setSize(sf::Vector2f{spriteBounds.width,10});
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

HealthBar & Mob::getHealthBar()
{
	return _healthBar;
}

void Mob::setPosition(const sf::Vector2f &moveTo)
{
	//moves the sprite
	_sprite.setPosition(moveTo);
	_position.x = moveTo.x;
	_position.y = moveTo.y;
	//subtract by sprite dimensions
	_healthBar.setPosition3(moveTo.x - 37, moveTo.y - 54);
}

void Mob::setHealth(int health)
{
	_health = health;
	_healthBar.setHealth(health/double(getMaxHealth()));
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

int Mob::getMaxHealth() const
{
	return _maxHealth;
}

std::string Mob::getType() const
{
	return "Mob";
}

//std::unique_ptr<Explosion> Mob::getDeathAnimation(const sf::Texture &texture)
//{
//	return std::make_unique<Explosion>(texture, sf::Vector2i{ getPosition().x, getPosition().y });
//}

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
