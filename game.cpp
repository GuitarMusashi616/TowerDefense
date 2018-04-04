#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 

#include <memory>

#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"
#include "grid.hpp"
#include "tile.hpp"
#include "Tower.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;


void resizeView(const sf::RenderWindow& window, sf::View & view) {
    float aspectRatio = ((float) window.getSize().x) / ((float) window.getSize().y);
    view.setSize(1000 * aspectRatio, 1000);
}


int GameScreen::run(sf::RenderWindow &app) {

	// Process events
	sf::Event event;
	bool running = true;

    //Highlight actiev tile?
    bool showTile = false;
    
	//load textures
	sf::Texture t1, t2, t3;

	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	sf::Sprite background{ t1};
    background.setScale(2, 2);
    
    //Create a View
    //    sf::View view(sf::Vector2f(0,0), sf::Vector2f(app.getSize().x, app.getSize().y));
    
    Grid grid(app);
    
    sf::RectangleShape rectangle(sf::Vector2f(50, 50));
    sf::Color transparentRed(255, 0, 0, 100);
    rectangle.setFillColor(transparentRed);
    
	// goomba tower
	sf::Texture t4;
	t4.loadFromFile(resourcePath() + "goombaTower.png",sf::IntRect(5,7,32,80));

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

	// List of mobs this round both alive and dead (cleared every round)
	vector<Mob*> mobsThisRound{
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

			// Tab pressed: place mob
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
				mobsThisRound.push_back( mobFactory('s',t2) );
			}
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                showTile = !showTile;
            }
            
            if(event.type == sf::Event::Resized)
            {
                //resizeView(app, view);
                cout << "Resized" << endl;
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
            
            if(event.type == sf::Event::MouseMoved) {
                int x{ sf::Mouse::getPosition(app).x }, y{ sf::Mouse::getPosition(app).y };
                
                shared_ptr<Tile> tileClicked = grid.getTile(x, y);
                tileClicked->setActivated();
            }
        }
        
        //view.setCenter(680,500);
        
        // Clear screen
        app.clear();
        
        //Set View
        //app.setView(view);
        
        //draw Background
        app.draw(background);
    
        if(showTile) {
            //Draw active tile
            std::vector<std::vector<shared_ptr<Tile>>> tileGrid = grid.getTiles();
            for(auto y = 0; y < tileGrid.size(); y++) {
                for(auto x = 0; x < tileGrid[y].size(); x++)
                {
                    shared_ptr<Tile> toDraw = grid.getTiles()[y][x];
                    sf::RectangleShape rect = toDraw->getTile();
                    rect.setPosition((float) toDraw->getPosition().x, (float) toDraw->getPosition().y);
                    if(toDraw->isActivated()) app.draw(rect);
                }
            }
        }
        // Draw Mobs
        for (auto mob : mobsThisRound) {
            if (mob->getHealth() > 0) {
                app.draw(mob->getSprite());
            }
        }
        
		// draw towers
		for (auto tower : towersThisRound) {
			tower->setPosition();
			app.draw(tower->getSprite());
		}
        // Update the window
        app.display();
    }
    
    return (-1);
}
