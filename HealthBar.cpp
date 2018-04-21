#include "HealthBar.h"

HealthBar::HealthBar(float left, float top, float width, float height) : RectangleShape{}, _healthRemaining{}, _healthLost{}
{
	//originally 41,60 -> 82,120
	//setFillColor(sf::Color{ 0,255,0,100 });
	setPosition3(left, top);

	setFillColor(sf::Color::Transparent);
	_healthRemaining.setFillColor(sf::Color{ 0,255,0,100 });
	_healthLost.setFillColor(sf::Color{255, 0, 0, 100});

	//setOrigin(width/2, height/2);
	//_healthRemaining.setOrigin(width / 2, height / 2);
	//_healthLost.setOrigin(width / 2, height / 2);

	setSize(sf::Vector2f{ width,height });
	_healthRemaining.setSize(sf::Vector2f{ width,height });
	_healthLost.setSize(sf::Vector2f{ 0,height });

	setOutlineThickness(1);
	setOutlineColor(sf::Color::Black);
}

void HealthBar::setSize3(float width, float height) {
	setSize(sf::Vector2f{ width,height });
	_healthRemaining.setSize(sf::Vector2f{ width,height });
	_healthLost.setSize(sf::Vector2f{ 0,height });
}

void HealthBar::setHealth(double fraction)
{
	//0.75
	int test = int(this->getLocalBounds().left);
	auto width = this->getLocalBounds().width;
	auto height = this->getLocalBounds().height;
	auto left = this->getLocalBounds().left;
	auto top = this->getLocalBounds().top;

	_healthRemaining.setSize(sf::Vector2f{ width*float(fraction), height });
	_healthLost.setSize(sf::Vector2f{ (float(1 - fraction)*width),height });
	//makes green rectangle shorter as mob loses health, fills the rest of the bar with red rectangle

}

sf::RectangleShape & HealthBar::getRemaining()
{
	return _healthRemaining;
}

sf::RectangleShape & HealthBar::getLost()
{
	return _healthLost;
}


void HealthBar::setPosition3(float x, float y)
{
	//set for all 3 rectangles
	setPosition(x, y);
	_healthRemaining.setPosition(x, y);
	_healthLost.setPosition(_healthRemaining.getPosition().x+_healthRemaining.getSize().x, y);
}



