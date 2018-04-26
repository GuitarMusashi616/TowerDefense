// SoundEffects.hpp
#include <SFML/Audio.hpp>
#include <string>
using std::string;

#ifndef SOUNDEFFECTS_HPP_
#define SOUNDEFFECTS_HPP_

class SoundFx {
public:
	SoundFx();
	SoundFx(const sf::SoundBuffer &);
	void explosion(bool);
	void pulse(bool);
	void uiEffect(bool);
	void sellTower(bool);
	void marching(bool);
	void gameOver();
private:
	sf::Sound _sound;
	sf::SoundBuffer _buffer;
};
#endif // !SOUNDEFFECTS_HPP_
