#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
 
#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"

using std::vector;
using std::cout;
using std::endl;



int GameScreen::run(sf::RenderWindow &app) {

	// Process events
	sf::Event event;
	bool running = true;

	//load textures
	sf::Texture t1, t2, t3;
<<<<<<< HEAD
	t1.loadFromFile(resourcePath() + "Resources/GrassTrack.png");
	t2.loadFromFile(resourcePath() + "Resources/ship.png");
=======
	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
>>>>>>> a9fcd4d419b2aeedce3b0b6514585e52a93f963b
	sf::Sprite background{ t1 };

	//stuff for keeping track of time
	sf::Clock timer;
	auto lastTime = sf::Time::Zero;

	//mobs to spawn
	//Mob shipMob{ t2,{0,0},1,1 };
	//Mob shipMob2{ t2,{ 500,200 },1,1 };
	Ship shipMob{ t2 };
	Ship shipMob2{t2};

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
		{500,500},
    };

	vector<Mob*> mobsThisRound{
		//&shipMob,
		//&shipMob2,
	};

	//List of mobs this round both alive and dead (cleared every round)
    // Start the game loop
    while (app.isOpen())
    {
        //fixedTimerLoop
        auto time = timer.getElapsedTime();
        if ( (time - lastTime).asMilliseconds() > 10) {
            lastTime = time;
            
			for (auto mob : mobsThisRound ) {
				auto moveTo = mob->nextPosition(shipAi);
				//cout << moveTo.x << ", " << moveTo.y << endl;
				mob->setPosition(moveTo);
			}
            //updates ships' positions every 10 milliseconds
        }
        
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                app.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                app.close();
            }

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
				mobsThisRound.push_back( mobFactory('s',t2) );
			}
            
            //DEBUG: figure out pixel x,y,z location of click
            if (event.type == sf::Event::MouseButtonPressed) {
                
                int x{ sf::Mouse::getPosition(app).x }, y{ sf::Mouse::getPosition(app).y };
                cout << x << ", " << y << endl;
                shipMob.setPosition(sf::Vector2f{ float(x), float(y) });
            }
            
        }
        // Clear screen
        app.clear();
        
        //draw to buffer
        app.draw(background);
		for (auto mob : mobsThisRound) {
			if (mob->getHealth() > 0) {
				app.draw(mob->getSprite());
			}
		}
        
        // Update the window
        app.display();
    }
    
    return (-1);
}
