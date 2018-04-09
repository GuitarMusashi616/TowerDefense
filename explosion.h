#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "game.hpp"

class Explosion : public sf::Sprite {
public:
	Explosion();
	Explosion(const sf::Texture &texture, const sf::Vector2<int> &position);
	~Explosion();
	void virtual update();
	int getFrameCount() const;
protected:
	int _frameCount;
	sf::Texture _texture;
	sf::Vector2f _position;
	sf::IntRect _frame;
};

class ArcaneExplosion : public Explosion {
public:
	ArcaneExplosion();
	ArcaneExplosion(const sf::Texture &texture, const sf::Vector2<int> &position);
	void update() override;
};

