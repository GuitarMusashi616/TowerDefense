
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include <ResourcePath.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(680, 500), "SFML window");

	//load textures
	sf::Texture t1, t2, t3;
	t1.loadFromFile(resourcePath() + "/Resources/GrassTrack.png");
	t2.loadFromFile(resourcePath() + "/Resources/ship.png");
	sf::Sprite background{ t1 };

	//stuff for keeping track of time
	sf::Clock timer;    
	auto lastTime = sf::Time::Zero;

	//mobs to spawn
	Mob shipMob{ t2,{0,0},1,1 };
	Mob shipMob2{ t2,{ 500,200 },1,1 };
	
	//track for mobs to follow
	vector<coord> shipAi{
		{94,10},
		{106,92},
		{217,97},
		{226,19},
		{340,18},
		{336,195},
		{223,199},
		{220,380},
		{342,382},
		{350,302},
		{453,306},
		{462,375},
		{630,377},
	};

	// Start the game loop
	while (window.isOpen())
	{
		//fixedTimerLoop
		auto time = timer.getElapsedTime();
		if ( (time - lastTime).asMilliseconds() > 10) {
			lastTime = time;

			auto moveTo = shipMob.nextPosition(shipAi);
			auto moveTo2 = shipMob2.nextPosition(shipAi);
			cout << moveTo.x << ", " << moveTo.y << endl;
			shipMob.setPosition(moveTo);
			shipMob2.setPosition(moveTo2);
			//updates ships' positions every 10 milliseconds
		}

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}

			//DEBUG: figure out pixel x,y,z location of click
			if (event.type == sf::Event::MouseButtonPressed) {

				int x{ sf::Mouse::getPosition(window).x }, y{ sf::Mouse::getPosition(window).y };
				cout << x << ", " << y << endl;
				shipMob.setPosition(sf::Vector2f{ float(x), float(y) });

			}

		}

		// Clear screen
		window.clear();

		//draw to buffer
		window.draw(background);
		window.draw(shipMob.getSprite());
		window.draw(shipMob2.getSprite());

		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
