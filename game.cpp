#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <tuple>

#include <cmath>
#include <memory>
#include <string>
#include <sstream>
 
#include "ResourcePath.hpp"
#include "MobTypes.h"
#include "game.hpp"
#include "grid.hpp"
#include "tile.hpp"
#include "framework.hpp"
#include "Wave.h"
#include "Player.hpp"
#include "Ghost.h"
#include "Towers.h"
#include "Tower.hpp"
#include "explosion.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::abs;
using std::tuple;

int GameScreen::run(sf::RenderWindow & app, const Framework & framework) {

    //Base window size:
    float xSize0 = framework.getWindowX();
    float ySize0 = framework.getWindowY();
    sf::Vector2<float> viewSize = framework.getViewSize();

    using std::string;
    using std::stringstream;

	//Initial game message
	cout << "Click to Explode" << endl;
	cout << "Press 1 - 5 to build basic towers" << endl;
	cout << "Mouse Over towers and Press U to upgrade" << endl;
	cout << "Mouse Over towers and Press S to sell" << endl;
	cout << "Press Space to send next Wave" << endl;
	cout << "Press Tab to send Knights" << endl;
	cout << "Press Q to send Footmen" << endl;
	cout << "Use Z and X to Zoom in/out" << endl;

	// Process events
	sf::Event event;
	bool running = true;

    //Highlight actiev tile?
    bool showTile = false;

    //Menu view:
    sf::View view1(sf::FloatRect(0.0f, 0.0f, xSize0, ySize0));
    view1.setViewport(sf::FloatRect(0, 0, viewSize.x / xSize0, viewSize.y / ySize0));
    view1.setSize(viewSize.x, viewSize.y);

    //Menu
    sf::View sideMenu(sf::FloatRect(0,0,xSize0,ySize0));
    sideMenu.setViewport(sf::FloatRect(0, 0, 1.5f, 1.5f));

    //Views
    app.setView(view1);
    view1.setCenter(viewSize.x/2, viewSize.y/2);

    //Grid
    Grid grid(app);
    
    //Random Circle
    sf::CircleShape circle(30);
    circle.setPosition(200 - circle.getRadius(), 300 - circle.getRadius());
    sf::Color transparentRed(255, 0, 0, 100);
    circle.setFillColor(transparentRed);
    
    //Load Textures
	sf::Texture t1, t2, t3, t4, t5, t6, t7;
	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	t3.loadFromFile(resourcePath() + "explosion.png");
	t4.loadFromFile(resourcePath() + "towers.png");
	t5.loadFromFile(resourcePath() + "arcaneBlast.png");
	t6.loadFromFile(resourcePath() + "knight.png");
	t7.loadFromFile(resourcePath() + "footman.png");
	sf::Sprite background{ t1 };

    //Font
    sf::Font font;
    font.loadFromFile(resourcePath() + "OpenSans-Regular.ttf");

    //Clickable Texts
    
    stringstream inGold, inLives;

    sf::Text sell{"Sell", font};
    sf::Text upgrade{"Upgrade", font};
    
    sell.setPosition(sf::Vector2f{ 0.f,320.f });
    upgrade.setPosition(sf::Vector2f{ 0.f,360.f });
    
    vector<sf::Text> menu {
        sell,
        upgrade
    };
    
 
	//stuff for keeping track of time
	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	auto lastMob = sf::Time::Zero;

	//changeable:
	static const int TPS = 60;
	const int defaultSpeed = 5;
    app.setFramerateLimit(30);
	sf::Time explosionCooldown = sf::Time::Zero;

    const int PATHWIDTH = 36;
    bool showCollisionBoxes = false;
    sf::RectangleShape box1(sf::Vector2f(190, PATHWIDTH));
    box1.setPosition(0, 54);
    
    sf::RectangleShape box2(sf::Vector2f(158, PATHWIDTH));
    box2.setPosition(268, 54);
    
    sf::RectangleShape box3(sf::Vector2f(PATHWIDTH, 122));
    box3.setPosition(155, 54);
    
    sf::RectangleShape box4(sf::Vector2f(148, PATHWIDTH));
    box4.setPosition(156, 140);
    
    sf::RectangleShape box5(sf::Vector2f(PATHWIDTH, 122));
    box5.setPosition(268, 54);
    
    sf::RectangleShape box6(sf::Vector2f(PATHWIDTH, 220));
    box6.setPosition(390, 54);
    
    sf::RectangleShape box7(sf::Vector2f(152, PATHWIDTH));
    box7.setPosition(274, 238);
    
    sf::RectangleShape box8(sf::Vector2f(PATHWIDTH, 222));
    box8.setPosition(274, 238);
    
    sf::RectangleShape box9(sf::Vector2f(157, PATHWIDTH));
    box9.setPosition(274, 424);
    
    sf::RectangleShape box10(sf::Vector2f(PATHWIDTH, 124));
    box10.setPosition(395, 337);
    
    sf::RectangleShape box11(sf::Vector2f(149, PATHWIDTH));
    box11.setPosition(395, 337);
    
    sf::RectangleShape box12(sf::Vector2f(PATHWIDTH, 124));
    box12.setPosition(508, 337);
    
    sf::RectangleShape box13(sf::Vector2f(200, PATHWIDTH));
    box13.setPosition(508, 425);
    
    vector<sf::RectangleShape> pathCollision{
        box1,
        box2,
        box3,
        box4,
        box5,
        box6,
        box7,
        box8,
        box9,
        box10,
        box11,
        box12,
        box13,
    };

	Player thePlayer;
	//SoundEffects soundEffects;

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

	vector<coord> mobOrder{
		{800, 3},
		{600, 3},
		{800, 5},
		{600, 10},
		{400, 15},
		{200,32},
		{50, 32},
		{400,10},
		{50, 50},
		{350, 10},
		{250, 15},
		{50, 100},
	};

	Wave mobsThisRound;

	vector< std::unique_ptr<Explosion> > animations{
	};

	//vector < std::unique_ptr<Tower> > towers {
	//};

	Towers towers;

	vector <std::unique_ptr <Ghost> > boo{

	};

    sf::CircleShape selectGhost;
    
	// List of towers added this round
	vector<Tower*> towersThisRound{};

    // Start the game loop
	while (app.isOpen())
	{
		//fixedTimerLoop
		auto time = timer.getElapsedTime();
        float framerate = 1.f / (time - lastTime).asSeconds();

		if ((time - lastTime).asMilliseconds() > (1. / TPS) * 1000) {
			lastTime = time;
			//add mobs
			if (thePlayer.roundHasStarted) {
				auto timeBetweenMobs = mobOrder[thePlayer.roundNum].x;
				if ((time - lastMob).asMilliseconds() >= timeBetweenMobs) {
					lastMob = time;
					auto mobsRemaining = mobOrder[thePlayer.roundNum].y;
					if (mobsRemaining > 0) {
						mobsThisRound.push_back(mobFactory('s', t2, defaultSpeed));
						mobOrder[thePlayer.roundNum].y = mobsRemaining - 1;
					}
					//try using references here
				}
			}

			//update mobs
			for (int i = 0; i < mobsThisRound.size(); i++) {
				auto moveTo = mobsThisRound[i]->nextPosition(shipAi);
				//cout << moveTo.x << ", " << moveTo.y << endl;
				mobsThisRound[i]->setPosition(moveTo);
				if (mobsThisRound[i]->getHealth() <= 0) {
					//explosion at deathPoint
					//animations.push_back(mobsThisRound[i]->getDeathAnimation(t3));
					//death animation handler
					if (mobsThisRound[i]->getType() == "KnightMob") {
						animations.push_back(std::make_unique<KnightDeath>(t6, sf::Vector2i{ mobsThisRound[i]->getPosition().x, mobsThisRound[i]->getPosition().y }));
					} else {
						animations.push_back(std::make_unique<Explosion>(t3, sf::Vector2i{ mobsThisRound[i]->getPosition().x, mobsThisRound[i]->getPosition().y }));
					}
					//lives lost or money gained
					if (mobsThisRound[i]->getEscaped()) {
						thePlayer.setLife(thePlayer.getLife() - 1);
					} else {
						thePlayer.setGold(thePlayer.getGold() + 10);
					}
					mobsThisRound[i].reset();
					mobsThisRound.erase(mobsThisRound.begin() + i);
					//check if end of round
					if (thePlayer.roundHasStarted && mobsThisRound.size() == 0) {
						thePlayer.roundHasStarted = false;
						thePlayer.roundNum++;
						cout << "You survived Round " << thePlayer.roundNum - 1 << endl;
						cout << "Press Space to start next round" << endl;
					}
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
					mobsThisRound.killCircle(m.x, m.y, 96.);
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
				//mobsThisRound.push_back( mobFactory('s',t2, defaultSpeed) );
				mobsThisRound.push_back(std::make_unique<KnightMob>(t6));
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
				mobsThisRound.push_back(std::make_unique<Footman>(t7));
			}
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                showTile = !showTile;
            }
            
            float scaleFactor = 1.5;
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
                if(view1.getSize().x * 1.5 >= viewSize.x || view1.getSize().y * scaleFactor >= viewSize.y) {
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

            
            if(event.type == sf::Event::MouseMoved) {
                for (auto &g:boo) {
                    sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                    bool collides = false;
                    
                    for(auto &t : towers) {
                        sf::Rect<float> bounds(t->getCollisionBox());
                        if(g->getGlobalBounds().intersects(bounds)) {
                            collides = true;
                        }
                    }
                    for(auto &collisionBox : pathCollision) {
                        sf::Rect<float> bounds(collisionBox.getGlobalBounds());
                        if(g->getGlobalBounds().intersects(bounds)) {
                            collides = true;
                        }
                    }
                    g->setPosition(sf::Vector2f{worldPos});
                    g->setCollision(collides);
                }
            }
            
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				if (!thePlayer.roundHasStarted) {
					thePlayer.roundHasStarted = true;
					cout << "Starting Round " << thePlayer.roundNum << endl;
				}
			}
            
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Equal) {
				static int tCount = 0;
				tCount++;
				cout << "Towers: " << tCount << endl;
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));

				towers.push_back(std::make_shared<Tower>(t4, sf::Vector2i{ (int) worldPos.x, (int) worldPos.y }));

			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                
				if (thePlayer.getGold() >= 150) {
					if (boo.size() < 1) {
						boo.push_back(std::make_unique<Ghost>(worldPos.x, worldPos.y));
                        boo[0]->setCollision(true);
					}
					else {
                        if(!boo[0]->isOverlapping()) {
                            boo.erase(boo.begin());
                            towers.push_back(std::make_shared<Tower>(t4, sf::Vector2i{ (int) worldPos.x, (int) worldPos.y - 20}));
                            
                            std::sort(towers.begin(), towers.end(), [](std::shared_ptr<Tower> a, std::shared_ptr<Tower> b) {
                                return a->getPosition().y < b->getPosition().y;
                            });
                            
                            thePlayer.setGold(thePlayer.getGold() - 150);
                        }
                    }
				} else {
					cout << "not enough gold, " << 150 - thePlayer.getGold() << " more gold required!"  << endl;
				}
			}
            
            if(event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
                bool clickedClickable = false;
                for(const auto &item : menu) {
                    if(item.getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                        if(selectGhost.getRadius()) {
                            if(item.getString() == "Sell") {
                                cout << "Sell Tower Here." << endl;
                                //Sell Tower Function
                                cout << "Tower: " << Clickable::getSelected() << endl;
                            }
                            if(item.getString() == "Upgrade") {
                                shared_ptr<Clickable> clickable = Clickable::getSelected();
                                shared_ptr<Tower> clickableTower = std::static_pointer_cast<Tower>(clickable);
                                //shared_ptr< Tower > pd = std::dynamic_pointer_cast< Tower >(pb);
                                clickableTower->upgrade();
                            }
                            clickedClickable = true;
                        }
                    }
                }
                for (const auto &t : towers) {
                    if(t->getGlobalBounds().contains(worldPos.x, worldPos.y)) {
                        t->onClick();
                        selectGhost = t->getThisGhost();
                        //selectGhost.setOrigin(t->getPosition().x, t->getPosition().y);
                        selectGhost.setRadius(100);
                        clickedClickable = true;
                    }
                }
                if(!clickedClickable) {
                    selectGhost.setRadius(0);
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) {
                showCollisionBoxes = !showCollisionBoxes;
            }

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
				//Sell Tower
				auto m = sf::Mouse::getPosition(app);
				//Check if a Tower has been clicked
				//bool ifFound = findTower(towers, m);
				int iterValue;
				bool ifFound = towers.findTower(m,iterValue);
				if (ifFound) {
					cout << "Tower Sold" << endl;
					towers.deleteTower(iterValue);
					thePlayer.setGold(thePlayer.getGold() + 60);
				}
				else {
					cout << "No Tower Selected" << endl;
				}
				
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U) {
				//Upgrade Tower
				auto m = sf::Mouse::getPosition(app);
				int iterValue;
				bool ifFound = towers.findTower(m, iterValue);
				if (ifFound) {
					cout << "Tower Upgraded" << endl;
					auto &intRect = towers[iterValue]->getIntRect();
					//275, 100 original position for default tower in towers.png image
					//size of all 10 towers fit in a 380 by 214 box
					if (intRect.left < 380 + 275) {
						intRect.left += 76;
					} else if (intRect.top < 100 + 107) {
						intRect.left = 275;
						intRect.top += 107;
					}
					//how many pixels over to the next tower in the towers.png image
					towers[iterValue]->setTextureRect(intRect);
				}
				else {
					cout << "No Tower Selected" << endl;
				}
			}
            
            
            
            //DEBUG: figure out pixel x,y location of click
            if (event.type == sf::Event::MouseButtonPressed) {
                
                sf::Vector2f worldPos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
				if ((timer.getElapsedTime() - explosionCooldown).asMilliseconds() >= 500) {
					explosionCooldown = timer.getElapsedTime();
					animations.push_back(std::make_unique<Explosion>(t3, sf::Vector2i{ (int)worldPos.x, (int)worldPos.y }));
					mobsThisRound.killBox(worldPos.x, worldPos.y, 128, 128);
				}
            }
        }
        
        // Clear screen
        app.clear();
        
        app.setView(sideMenu);
        app.draw(background);
        view1.setCenter(680/2, 500/2);
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

		for (int i = mobsThisRound.size()-1; i >= 0; i--) {
			//first mobs drawn on top
			app.draw(mobsThisRound[i]->getSprite());
			app.draw(mobsThisRound[i]->getHealthBar());
			app.draw(mobsThisRound[i]->getHealthBar().getRemaining());
			app.draw(mobsThisRound[i]->getHealthBar().getLost());
		}

        
        
        if(selectGhost.getRadius()) {
            for (auto & item : menu) {
                item.setFillColor(sf::Color::Blue);
            }
        } else {
            for (auto & item : menu) {
                item.setFillColor(sf::Color(0,0,0,40));
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
        for (const auto &item : menu) {
            app.draw(item);
            //Drawing item
        }
        
       

        
        
        if(showCollisionBoxes) {
            for (auto &b : pathCollision) {
                b.setFillColor(sf::Color(0,0,255,100));
                app.draw(b);
            }
        }
        app.draw(selectGhost);

		stringstream inGold, inLives;
		inGold << thePlayer.getGold();
		inLives << thePlayer.getLife();
		sf::Text goldText{ "Gold: " + inGold.str(), font }, livesText{ "Lives: " + inLives.str(),font };
		goldText.setPosition(sf::Vector2f{ 0.f,420.f });
		livesText.setPosition(sf::Vector2f{ 0.f,460.f });
       
        
		app.draw(goldText);
		app.draw(livesText);
        // Update the window
        app.display();
    }
    
    return (-1);
}
