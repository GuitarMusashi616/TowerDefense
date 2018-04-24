#pragma once
#include <SFML/Graphics.hpp>


class HealthBar : public sf::RectangleShape
{
public:
	HealthBar(float left, float top, float width, float height);
	void setHealth(double fraction);
	sf::RectangleShape &getRemaining();
	sf::RectangleShape &getLost();
	void setPosition3(float x, float y);
	void setSize3(float width, float height);
private:
	sf::RectangleShape _healthRemaining;
	sf::RectangleShape _healthLost;
};

