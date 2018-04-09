#include "explosion.h"
#include <iostream>


Explosion::Explosion() : _frameCount{ 0 }, _position{ 0,0 }, _frame{0,0,128,128}
{
	setOrigin(64, 64);
} 

Explosion::Explosion(const sf::Texture &texture, const sf::Vector2<int> &position) : _frameCount{ 0 }, _position{ position }, _frame{ 0,0,128,128 }, _texture{texture}
{
	setTexture(_texture);
	setTextureRect(_frame);
	setPosition( _position );
	setOrigin(64, 64);
}

Explosion::~Explosion()
{
}

void Explosion::update()
{
	if (_frame.left < 512) {
		_frame.left += 128;
		_frameCount++;
	} else if (_frame.top < 512) {
		_frame.top += 128;
		_frame.left = 0;
		_frameCount++;
	}
	setTextureRect(_frame);
}

int Explosion::getFrameCount() const
{
	return _frameCount;
}

ArcaneExplosion::ArcaneExplosion() : Explosion{}
{
	setOrigin(96, 96);
}

ArcaneExplosion::ArcaneExplosion(const sf::Texture & texture, const sf::Vector2<int>& position) : Explosion{ texture,position }
{
	_frame = sf::IntRect{0,0,192,192};
	setTextureRect(_frame);
	setOrigin(96, 96);
}

void ArcaneExplosion::update()
{
	if (_frame.left < 960) {
		_frame.left += 192;
		_frameCount++;
	}
	else if (_frame.top < 960) {
		_frame.top += 192;
		_frame.left = 0;
		_frameCount++;
	}
	setTextureRect(_frame);
}
