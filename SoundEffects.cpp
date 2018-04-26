// SoundEffects.cpp

#include "SoundEffects.hpp"
#include "ResourcePath.hpp"

SoundFx::SoundFx() {}

SoundFx::SoundFx(const sf::SoundBuffer & buffer) : _buffer(buffer) {}

void SoundFx::explosionFx(bool first) {
	if (first) {
		_buffer.loadFromFile(resourcePath() + "explosion.wav");
		_sound.setBuffer(_buffer);
		_sound.setVolume(50);
		_sound.play();
	}
	_sound.play();
}

void SoundFx::pulseFx(bool first) {
	if (first) {
		_buffer.loadFromFile(resourcePath() + "Pulse.wav");
		_sound.setBuffer(_buffer);
		_sound.setVolume(25);
		_sound.play();
	}
	_sound.play();
}

void SoundFx::uiEffect(bool first) {
	if (first) {
		_buffer.loadFromFile(resourcePath() + "buttonClick.wav");
		_sound.setBuffer(_buffer);
		_sound.setVolume(50);
		_sound.play();
	}
	_sound.play();
}

void SoundFx::sellTowerFx(bool first) {
	if (first) {
		_buffer.loadFromFile(resourcePath() + "cashRegister.wav");
		_sound.setBuffer(_buffer);
		_sound.setVolume(50);
		_sound.play();
	}
	_sound.play();
}

void SoundFx::marchingFx(bool first) {
	if (first) {
		_buffer.loadFromFile(resourcePath() + "marching.wav");
		_sound.setBuffer(_buffer);
		_sound.setVolume(20);
		_sound.play();
	}
	_sound.play();
}

void SoundFx::uiNopeFx(bool)
{
	_buffer.loadFromFile(resourcePath() + "notPossible.wav");
	_sound.setBuffer(_buffer);
	_sound.play();
}

void SoundFx::gameOverFx() {
	_buffer.loadFromFile(resourcePath() + "gameover.wav");
	_sound.setBuffer(_buffer);
	_sound.play();
}


