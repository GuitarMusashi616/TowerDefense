#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <memory>
 
#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"
#include "Tower.hpp"

using std::vector;
using std::cout;
using std::endl;

int GameScreen::run(sf::RenderWindow &app) {

	// Process events
	sf::Event event;
	bool running = true;

	//load textures
	sf::Texture t1, t2;
	t1.loadFromFile(resourcePath() + "Resources/GrassTrack.png");
	t2.loadFromFile(resourcePath() + "Resources/ship.png");
	sf::Sprite background{ t1 };

	// goomba tower
	sf::Texture t4;
	t4.loadFromFile(resourcePath() + "Resources/goombaTower.png",sf::IntRect(5,7,32,80));

	//stuff for keeping track of time
	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	//changeable:
	static const int TPS = 60;
	const int defaultSpeed = 2;

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

	vector< std::unique_ptr<Mob> > mobsThisRound{
		//&shipMob,
		//&shipMob2,
	};

	// List of towers added this round
	vector<Tower*> towersThisRound{};

    // Start the game loop
	while (app.isOpen())
	{
		//fixedTimerLoop
		auto time = timer.getElapsedTime();
		if ((time - lastTime).asMilliseconds() > (1. / TPS)*1000) {
            lastTime = time;
            
			for (int i = 0; i < mobsThisRound.size();i++) {
				auto moveTo = mobsThisRound[i]->nextPosition(shipAi);
				//cout << moveTo.x << ", " << moveTo.y << endl;
				mobsThisRound[i]->setPosition(moveTo);
				if (mobsThisRound[i]->getHealth()==0) {
					//attempting to get mob out of scope and therefore out of memory by removing it from the vector
					//cout << mobsThisRound[i]->getPosition().x << ", " << mobsThisRound[i]->getPosition().y << endl;
					mobsThisRound[i].reset();
					mobsThisRound.erase(mobsThisRound.begin() + i);
				}
			}
            //updates ships' positions based on TPS value
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
				mobsThisRound.push_back( mobFactory('s',t2, defaultSpeed) );
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal) {
				//counter test for now, going to use for testing if resizing window affects track length for mobs
				//no purpose atm
				static int tCount = 0;
				tCount++;
				cout << tCount << endl;
			}


			// LShift pressed: place tower on mouse cursor
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift) {
				cout << sf::Mouse::getPosition(app).x << "," << sf::Mouse::getPosition(app).y << endl;
				towersThisRound.push_back(towerFactory(t4, { sf::Mouse::getPosition(app).x - 15 , sf::Mouse::getPosition(app).y - 40}));
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
		for (const auto &mob : mobsThisRound) {
			if (mob->getHealth() > 0) {
				app.draw(mob->getSprite());
			}
		}
        
		for (auto tower : towersThisRound) {
			tower->setPosition();
			app.draw(tower->getSprite());
		}
        // Update the window
        app.display();
    }
    
    return (-1);
}
