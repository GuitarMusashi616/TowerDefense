#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 

#include <cmath>
#include <memory>
#include <string>
#include <sstream>
 
#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"
#include "grid.hpp"
#include "tile.hpp"
#include "Tower.hpp"
#include "framework.hpp"

#include "explosion.h"
#include "Tower.hpp"
#include "Wave.h"
#include "Player.hpp"
#include "Ghost.h"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::abs;

int GameScreen::run(sf::RenderWindow & app, const Framework & framework) {

    //Base window size:
    float xSize0 = framework.getWindowX();
    float ySize0 = framework.getWindowY();
    sf::Vector2<float> viewSize = framework.getViewSize();

    

using std::string;
using std::stringstream;

	//Initial game message
	cout << "Click to Explode" << endl;
	cout << "Press K to build towers" << endl;
	cout << "Press Tab to send mobs" << endl;

	// Process events
	sf::Event event;
	bool running = true;

    //Highlight actiev tile?
    bool showTile = false;

    //Menu view:
    sf::View view1(sf::FloatRect(0, 0, xSize0, ySize0));
    view1.setViewport(sf::FloatRect(0.005f, 0.005f, viewSize.x / xSize0, viewSize.y / ySize0));
    view1.setSize(viewSize.x, viewSize.y);

    app.setView(view1);

    Grid grid(app);
    
    sf::CircleShape circle(30);
    circle.setPosition(200 - circle.getRadius(), 300 - circle.getRadius());
    sf::Color transparentRed(255, 0, 0, 100);
    circle.setFillColor(transparentRed);
    
    //Load Textures
	sf::Texture t1, t2, t3, t4, t5;
	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	t3.loadFromFile(resourcePath() + "explosion.png");
	t4.loadFromFile(resourcePath() + "towers.png");
	t5.loadFromFile(resourcePath() + "arcaneBlast.png");
	sf::Sprite background{ t1 };

    //Font
    sf::Font font;
    font.loadFromFile("OpenSans-Regular.ttf");

	//stuff for keeping track of time
	sf::Clock timer;
	auto lastTime = sf::Time::Zero;

	//changeable:
	static const int TPS = 60;
	const int defaultSpeed = 5;

	//mobs to spawn
	//Mob shipMob{ t2,{0,0},1,1 };
	//Mob shipMob2{ t2,{ 500,200 },1,1 };
	//Ship shipMob{ t2 };
	//Ship shipMob2{t2};
	//Tower arcaneTower{ t4, sf::Vector2i{135,135} };

    //track for mobs to follow

  //  vector<coord> shipAiOld{
  //      {94,10},
  //      {106,92},
  //      {217,97},
  //      {226,19},
  //      {340,18},
  //      {336,195},
  //      {223,199},
  //      {220,380},
  //      {342,382},
  //      {350,302},
  //      {453,306},
  //      {462,375},
  //      {630,377},
		//{500,500},
  //  };

	Player thePlayer;

	vector<coord> shipAi{
		{ 170,74 },
		{ 177,155 },
		{ 283,157 },
		{ 288,77 },
		{ 402,74 },
		{ 406,251 },
		{ 295,258 },
		{ 294,439 },
		{ 410,439 },
		{ 413,355 },
		{ 525,356 },
		{ 531,442 },
		{ 695,444 },
		{ 500,500 },
	};

	Wave mobsThisRound;

	vector< std::unique_ptr<Explosion> > animations{
	};

	vector < std::unique_ptr<Tower> > towers {
	};

	vector <std::unique_ptr <Ghost> > boo{

	};

	// List of towers added this round
	vector<Tower*> towersThisRound{};

    // Start the game loop
	while (app.isOpen())
	{
		//fixedTimerLoop
		auto time = timer.getElapsedTime();
		if ((time - lastTime).asMilliseconds() > (1. / TPS) * 1000) {
			lastTime = time;
			
			//update mobs
			for (int i = 0; i < mobsThisRound.size(); i++) {
				auto moveTo = mobsThisRound[i]->nextPosition(shipAi);
				//cout << moveTo.x << ", " << moveTo.y << endl;
				mobsThisRound[i]->setPosition(moveTo);
				if (mobsThisRound[i]->getHealth() == 0) {
					//explosion at deathPoint
					animations.push_back(std::make_unique<Explosion>(t3, sf::Vector2i{ mobsThisRound[i]->getPosition().x, mobsThisRound[i]->getPosition().y }));
					//lives lost or money gained
					if (mobsThisRound[i]->getEscaped()) {
						thePlayer.setLife(thePlayer.getLife() - 1);
					} else {
						thePlayer.setGold(thePlayer.getGold() + 10);
					}
					mobsThisRound[i].reset();
					mobsThisRound.erase(mobsThisRound.begin() + i);
				}
			}
			for (int i = 0; i < animations.size(); i++) {
				animations[i]->update();
				if (animations[i]->getFrameCount() >= 16) {
					animations[i].reset();
					animations.erase(animations.begin() + i);
				}
			}
			for (auto &g:boo) {
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));

				g->setPosition(sf::Vector2f{worldPos});
			}

			bool ifNear;
			sf::Time timeDelay;
			for (int i = 0; i < towers.size(); i++) {
				auto m = towers[i]->getPosition();
				ifNear = mobsThisRound.detectBox(m.x,m.y, 192, 192);
				timeDelay = towers[i]->getClock();
				if (ifNear && (timeDelay.asSeconds() >= 2)) {
					//if mobs are nearby and it has been 2 seconds since the tower has fired
					towers[i]->restartClock();
					animations.push_back(std::make_unique<ArcaneExplosion>(t5, sf::Vector2i{ int(m.x),int(m.y) }));
					mobsThisRound.killBox(m.x, m.y, 192, 192);
				}
			}
			
			
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
				mobsThisRound.push_back( mobFactory('s',t2, defaultSpeed) );
			}
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                showTile = !showTile;
            }
            
            float scaleFactor = 1.5;
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
                if(view1.getSize().x * 1.5 > xSize0 || view1.getSize().y * scaleFactor > ySize0) {
                    view1.setSize(viewSize.x, viewSize.y);
                } else {
                    view1.zoom(1.5);

                }
                cout << "Zoom In" << endl;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X) {
                view1.zoom(0.75);
                cout << "Zoom Out" << endl;

            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
                
                float x = sf::Mouse::getPosition(app).x;
                float y = sf::Mouse::getPosition(app).y;
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                
                sf::Vector2<float> corrected = framework.getCorrectedMousePosition(app,x,y);
                if(circle.getGlobalBounds().contains(worldPos.x, worldPos.y))
                   {
                       sf::Vector2f initPosition = circle.getPosition();
                       circle.setRadius(circle.getRadius() + 2);
                       circle.setPosition(200 - circle.getRadius(), 300 - circle.getRadius());

                   }
            }
            
            
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal) {
				static int tCount = 0;
				tCount++;
				cout << "Towers: " << tCount << endl;
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));

				towers.push_back(std::make_unique<Tower>(t4, sf::Vector2i{ (int) worldPos.x, (int) worldPos.y }));

			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                
				if (thePlayer.getGold() >= 1000) {
					if (boo.size() < 1) {
						boo.push_back(std::make_unique<Ghost>(worldPos.x, worldPos.y));
					}
					else {
						boo.erase(boo.begin());
						towers.push_back(std::make_unique<Tower>(t4, sf::Vector2i{ (int) worldPos.x, (int) worldPos.y }));
						thePlayer.setGold(thePlayer.getGold() - 1000);
					}
				} else {
					cout << "not enough gold, " << 1000 - thePlayer.getGold() << " more gold required!"  << endl;
				}
			}

            //DEBUG: figure out pixel x,y location of click
            if (event.type == sf::Event::MouseButtonPressed) {
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
				animations.push_back(std::make_unique<Explosion>(t3, sf::Vector2i{ (int) worldPos.x, (int)worldPos.y }));
				//kills mobs on click in a 200 x 2 c00 box centered on mouse position
				//for (auto &mob: mobsThisRound) {
				//	if (mob->getPosition().x + 100  >= (x - 74) && mob->getPosition().x - 100 <= (x - 74)) {
				//		if (mob->getPosition().y +100 >= (y-64) && mob->getPosition().y - 100<= (y-64)) {
				//			mob->setHealth(0);
				//		}
				//	}
				//}
				mobsThisRound.killBox(worldPos.x, worldPos.y,128,128);
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
    
        app.draw(circle);

    for (const auto &mob : mobsThisRound) {
			if (mob->getHealth() > 0) {
				app.draw(mob->getSprite());
			}
		}

		for (const auto &a : animations) {
			app.draw(*a);
		}

		for (const auto &t : towers) {
			app.draw(*t);
		}

		for (const auto &g : boo) {
			app.draw(*g);
		}
		

		stringstream inGold, inLives;
		inGold << thePlayer.getGold();
		inLives << thePlayer.getLife();
		sf::Text goldText{ "Gold: " + inGold.str() ,font }, livesText{ "Lives: " + inLives.str(),font };
		goldText.setPosition(sf::Vector2f{ 0.f,520.f });
		livesText.setPosition(sf::Vector2f{ 0.f,560.f });
		app.draw(goldText);
		app.draw(livesText);
        // Update the window
        app.display();
    }
    
    return (-1);
}
