
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ResourcePath.hpp>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(680, 500), "SFML window");

	//for fixedUpdates

	//load textures
	sf::Texture t1, t2;
	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	sf::Sprite background{ t1 }, ship{ t2 };
	

	//reposition mob
	//ship.setOrigin(143, 311);

	// Start the game loop
	while (window.isOpen())
	{
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

			//figure out pixel x,y,z location of click
			if (event.type == sf::Event::MouseButtonPressed) {
				
				int x{ sf::Mouse::getPosition(window).x }, y{sf::Mouse::getPosition(window).y };
				cout << x << ", " << y << endl;
				ship.setPosition(sf::Vector2f{float(x), float(y) });
				
			}

		}

		// Clear screen
		window.clear();

		//draw to buffer
		window.draw(background);
		window.draw(ship);

		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}
