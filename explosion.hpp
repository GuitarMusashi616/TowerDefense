#ifndef explosion_hpp
#define explosion_hpp

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

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

class KnightDeath : public Explosion {
public:
	KnightDeath();
	KnightDeath(const sf::Texture &texture, const sf::Vector2<int> &position);
	void update() override;
private:
	int _boxWidth;
	int _boxHeight;
	std::vector<sf::IntRect> _coordinatesForDeathFrames;
	sf::Clock _timer;
	int _i;
};

#endif
