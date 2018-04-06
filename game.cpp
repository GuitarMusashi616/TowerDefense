#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <cmath>
#include <memory>

#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"
#include "grid.hpp"
#include "tile.hpp"
#include "Tower.hpp"
#include "framework.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::abs;

int GameScreen::run(sf::RenderWindow & app, const Framework & framework) {

    //Base window size:
    float xSize0 = framework.getWindowX();
    float ySize0 = framework.getWindowY();
    float xViewSize = xSize0 - 100;
    float yViewSize = ySize0;
    
	// Process events
	sf::Event event;
	bool running = true;

    //Highlight actiev tile?
    bool showTile = false;

    //Menu view:
    sf::View view1(sf::FloatRect(0, 0, xSize0, ySize0));
    view1.setViewport(sf::FloatRect(0, 0, xViewSize / xSize0, yViewSize / ySize0));
    view1.setSize(xViewSize, yViewSize);    

    app.setView(view1);
    
    //load textures
	sf::Texture t1, t2, t3;

	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	sf::Sprite background{ t1};

    Grid grid(app);
    
    sf::CircleShape circle(30);
    circle.setPosition(200 - circle.getRadius(), 300 - circle.getRadius());
    sf::Color transparentRed(255, 0, 0, 100);
    circle.setFillColor(transparentRed);
    
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
            //Core Events:
            
            framework.handleEvents(app, event);
            Tile::handleEvents(app, event, grid, framework);

			// Tab pressed: place mob
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
				mobsThisRound.push_back( mobFactory('s',t2) );
			}
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                showTile = !showTile;
            }
            
            float scaleFactor = 1.5;
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
                if(view1.getSize().x * 1.5 > xSize0 || view1.getSize().y * scaleFactor > ySize0) {
                    view1.setSize(xViewSize, yViewSize);
                } else {
                    view1.zoom(1.5);

                }
                cout << "Zoom In" << endl;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X) {
                view1.zoom(0.75);
                cout << "Zoom Out" << endl;

            }

        
			// LShift pressed: place tower on mouse cursor
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift) {
                cout << sf::Mouse::getPosition(app).x << "," << sf::Mouse::getPosition(app).y << endl;
                float x = sf::Mouse::getPosition(app).x;
                float y = sf::Mouse::getPosition(app).y;
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Vector2i(x - 15, y - 40));

                towersThisRound.push_back(towerFactory(t4, {(int) worldPos.x, (int) worldPos.y}));
			}
            
            
            
            if(event.type == sf::Event::MouseButtonPressed)
            {
                
                float x = sf::Mouse::getPosition(app).x;
                float y = sf::Mouse::getPosition(app).y;
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
//                cout << "Mouse Position: (" << x << ", " << y << ")" << endl;
//                cout << "World Position: (" << worldPos.x << ", " << worldPos.y << ")" << endl;
//
//                cout << "Circle Position: (" << circle.getPosition().x << ", " << circle.getPosition().y << ")" << endl;
//
                sf::Vector2<float> corrected = framework.getCorrectedMousePosition(app,x,y);
                if(circle.getGlobalBounds().contains(worldPos.x, worldPos.y))
                   {
                       sf::Vector2f initPosition = circle.getPosition();
                       circle.setRadius(circle.getRadius() + 2);
                       circle.setPosition(200 - circle.getRadius(), 300 - circle.getRadius());

                   }
            }
            
            
        }
        
        // Clear screen
        app.clear();
        
        view1.setCenter(xSize0/2, ySize0/2);
        app.setView(view1);
    
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
        
        app.draw(circle);
        // Update the window
        app.display();
    }
    
    return (-1);
}
