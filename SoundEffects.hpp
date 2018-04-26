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
	void explosionFx(bool);
	void pulseFx(bool);
	void uiEffect(bool);
	void sellTowerFx(bool);
	void marchingFx(bool);
	void uiNopeFx(bool);
	void gameOverFx();
private:
	sf::Sound _sound;
	sf::SoundBuffer _buffer;
};
#endif // !SOUNDEFFECTS_HPP_
