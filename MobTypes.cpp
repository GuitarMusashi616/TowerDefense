#include "MobTypes.h"

KnightMob::KnightMob(sf::Texture &texture) : Mob{ texture }
{
	_intRect = { 222,0,74,74 };
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(37, 37);
	_healthBar.setSize3(60, 5);
	_maxHealth = 3;
	_health = 3;
	_speed = 5;
	_boxHeight = 73;
	_lastBox = 73 * (5 - 1);
	_firstBox = 0;
	_millisecondsPerFrame = 200;
	_type = "KnightMob";
}

void KnightMob::setPosition(const sf::Vector2f &moveTo)
{
	//moves the sprite
	Mob::setPosition(moveTo);

	//animation loop here
	if (_gallopTimer.getElapsedTime().asMilliseconds() >= _millisecondsPerFrame) {
		//looping forwards as to have horses running backwards
		//if (_intRect.top <= finalBox) {
		//	_intRect.top += boxHeight;
		//	_gallopTimer.restart();
		//} else {
		//	_intRect.top = 0;
		//}
		//looping backwards so horses are running forward
		//if (_intRect.top > firstBox) {
		//	_intRect.top -= boxHeight;
		//	_gallopTimer.restart();
		//}
		//else {
		//	_intRect.top = lastBox;
		//}
		//looping forwards and back
		static bool loopForward = false;

		if (loopForward) {
			if (_intRect.top < _lastBox) {
				_intRect.top += _boxHeight;
				_gallopTimer.restart();
			}
			else {
				loopForward = false;
			}
		}
		else {
			if (_intRect.top > _firstBox) {
				_intRect.top -= _boxHeight;
				_gallopTimer.restart();
			}
			else {
				loopForward = true;
			}
		}
	}
	_sprite.setTextureRect(_intRect);
}

//Footman::Footman(sf::Texture &texture) : KnightMob{ texture }, _spriteSheetCoordinates{
//}
//{
//	//370 x 624
//	//5 x 11
//	double boxWidth = 73;
//	double boxHeight = 57;
//	_intRect = { int((4-1)*boxWidth+0.5) ,0,int(boxWidth+0.5),int(boxHeight+0.5) };
//	_sprite.setTextureRect(_intRect);
//	_sprite.setOrigin(boxWidth/2, boxHeight/2);
//	_healthBar.setSize3(50, 4);
//	_maxHealth = 2;
//	_health = 2;
//	_speed = 4;
//	_boxHeight = int(boxHeight+0.5);
//	_lastBox = int(boxHeight * (5 - 1)+0.5);
//	_firstBox = 0;
//	_millisecondsPerFrame = 200;
//	
//}

Footman::Footman(sf::Texture &texture) : Mob{ texture }, _boxWidth{ 81 }, _boxHeight{ 61 }, _millisecondsPerFrame{ 200 }, _frame{ 0 }, _iterateDown{ true },
_spriteSheetCoordinates{
	{222,0},
	{222,62},
	{222,116},
	{222,165},
	{222,212},
	//56, 58, 55, 50
}
{
	//370 x 624
	//5 x 11
	//_boxHeight = 61;
	//_boxWidth = 81;
	_intRect = {_spriteSheetCoordinates[0].x,_spriteSheetCoordinates[0].y,_boxWidth,_boxHeight};
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(_boxWidth / 2, _boxHeight / 2);
	_healthBar.setSize3(50, 4);
	_maxHealth = 2;
	_health = 2;
	_speed = 4;
	_type = "Footman";
	//_millisecondsPerFrame = 200;
}

void Footman::setPosition(const sf::Vector2f & moveTo)
{
	Mob::setPosition(moveTo);
	if (_walkTimer.getElapsedTime().asMilliseconds() >= _millisecondsPerFrame) { //every 200 milliseconds
		_walkTimer.restart();
		//check if going down or going up
		if (_iterateDown) {
			//go down 1 in vector
			//set intRect to those coordinates
			//update intRect
			
			_frame++;
			coord nextCoords = _spriteSheetCoordinates.at(_frame);
			_intRect.left = nextCoords.x;
			_intRect.top = nextCoords.y;
			_sprite.setTextureRect(_intRect);
			//check if last element in vector
			if (_frame >= _spriteSheetCoordinates.size() - 1) {
				_iterateDown = false;
			}
		} else {
			//go up 1 in vector
			//set intRect to those coordinates
			//update intRect

			_frame--;
			coord nextCoords = _spriteSheetCoordinates.at(_frame);
			_intRect.left = nextCoords.x;
			_intRect.top = nextCoords.y;
			_sprite.setTextureRect(_intRect);
			//check if last element in vector
			if (_frame <= 0) {
				_iterateDown = true;
			}
		}
	}

}

Gyrocopter::Gyrocopter(sf::Texture &texture) : Footman{texture}
{
	_boxHeight = 79;
	_boxWidth = 74;
	_spriteSheetCoordinates = std::vector<coord>{
		{227,7},
		{227,84},
	};
	_type = "Gyrocopter";
	_intRect = { _spriteSheetCoordinates[0].x,_spriteSheetCoordinates[0].y,_boxWidth,_boxHeight };
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(_boxWidth / 2, _boxHeight / 2);
	_healthBar.setSize3(80, 10);
	_maxHealth = 7;
	_health = 7;
	_speed = 6;
}

GriffonRider::GriffonRider(sf::Texture &texture) : Footman{ texture }
{
	_boxHeight = 81;
	_boxWidth = 82;
	_spriteSheetCoordinates = std::vector<coord>{
		{ 251,6 },
		{ 251,87 },
		{ 251,253 },
	};
	_type = "GriffonRider";
	_intRect = { _spriteSheetCoordinates[0].x,_spriteSheetCoordinates[0].y,_boxWidth,_boxHeight };
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(_boxWidth / 2, _boxHeight / 2);
	_healthBar.setSize3(90, 12);
	_maxHealth = 10;
	_health = 10;
	_speed = 4;
}

Dragon::Dragon(sf::Texture &texture) : Footman{ texture }
{
	_boxHeight = 80;
	_boxWidth = 81;
	_spriteSheetCoordinates = std::vector<coord>{
		{ 276, 3 },
		{ 276, 87 },
		{ 276, 182 },
		{ 276, 255},
	};
	_type = "Dragon";
	_intRect = { _spriteSheetCoordinates[0].x,_spriteSheetCoordinates[0].y,_boxWidth,_boxHeight };
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(_boxWidth / 2, _boxHeight / 2);
	_healthBar.setSize3(90, 12);
	_maxHealth = 10;
	_health = 10;
	_speed = 4;
}

Devourer::Devourer(sf::Texture &texture) : Footman{ texture }
{
	_boxWidth = 58;
	_boxHeight = 67;
	_spriteSheetCoordinates = std::vector<coord>{
		{ 450, 100 },
		{ 450, 185 },
		{ 450, 273 },
		{ 450, 356 },
		{ 450, 443 },
		{ 450, 529 },
	};
	_type = "Devourer";
	_intRect = { _spriteSheetCoordinates[0].x,_spriteSheetCoordinates[0].y,_boxWidth,_boxHeight };
	_sprite.setTextureRect(_intRect);
	_sprite.setOrigin(_boxWidth / 2, _boxHeight / 2);
	_healthBar.setSize3(90, 12);
	_maxHealth = 10;
	_health = 10;
	_speed = 4;
}
