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

KnightDeath::KnightDeath() : Explosion{}, _i{ 0 }
{
	setOrigin(_boxWidth/2, _boxHeight/2);
}

//KnightDeath::KnightDeath(const sf::Texture & texture, const sf::Vector2<int>& position) : Explosion{ texture,position }, _i{ 0 }, _boxWidth{ 66 }, _boxHeight{ 66 }, _coordinatesForDeathFrames{
//	{ 84,674 },
//	{ 229,674 },
//	{ 6,674 + 63 },
//	{ 161,674 + 63 },
//	{ 283,674 + 63 },
//}
//{
//	int imageWidth = 370;
//	int imageHeight = 800;
//	int boxWidth = 73.8;
//	int boxHeight = 72.73;
//	_frame = sf::IntRect{_coordinatesForDeathFrames[0].x,_coordinatesForDeathFrames[0].y,_boxWidth,_boxHeight };
//	setTextureRect(_frame);
//	setOrigin(_boxWidth / 2, _boxHeight / 2);
//}

KnightDeath::KnightDeath(const sf::Texture & texture, const sf::Vector2<int>& position) : Explosion{ texture,position }, _i{ 0 }, _coordinatesForDeathFrames{
	{ 84,668,70,72 },
	{ 230,668,70,72 },
	{ 5,739,70,54 },
	{ 159,739,70,54 },
	{ 284,739,70,54 },
}
{
	_frame = sf::IntRect{ _coordinatesForDeathFrames[0] };
	setTextureRect(_frame);
	setOrigin(_coordinatesForDeathFrames[0].width/2, _coordinatesForDeathFrames[0].height / 2);
}

void KnightDeath::update()
{
	if (_timer.getElapsedTime().asMilliseconds() >= 150) {
		//static bool forwards = true;
		_timer.restart();
		if (_i <_coordinatesForDeathFrames.size() - 1) {
			_i++;
			_frame = _coordinatesForDeathFrames[_i];
			setTextureRect(_frame);
			setOrigin(_coordinatesForDeathFrames[_i].width / 2, _coordinatesForDeathFrames[_i].height / 2);
			//std::cout << "top, left: " << _frame.top << ", " << _frame.left << std::endl;
		}
		else {
			_frameCount=17;
			//delete
		}
		//if (forwards) {
		//	i++;
		//	if (i >= _coordinatesForDeathFrames.size()) {
		//		forwards = false;
		//	}
		//} else {
		//	i--;
		//	if (i <= 0) {
		//		forwards = true;
		//	}
		//}
	}
}
