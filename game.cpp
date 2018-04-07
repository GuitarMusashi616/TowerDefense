#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <memory>
#include <string>
#include <sstream>
 
#include "ResourcePath.hpp"
#include "Mob.h"
#include "MobTypes.h"
#include "game.hpp"
#include "explosion.h"
#include "Tower.hpp"
#include "Wave.h"
#include "Player.hpp"
#include "Ghost.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

int GameScreen::run(sf::RenderWindow &app) {

	//Initial game message
	cout << "Click to Explode" << endl;
	cout << "Press K to build towers" << endl;
	cout << "Press Tab to send mobs" << endl;

	// Process events
	sf::Event event;
	bool running = true;

	//load textures
	sf::Texture t1, t2, t3, t4, t5;
	t1.loadFromFile(resourcePath() + "GrassTrack.png");
	t2.loadFromFile(resourcePath() + "ship.png");
	t3.loadFromFile(resourcePath() + "explosion.png");
	t4.loadFromFile(resourcePath() + "towers.png");
	t5.loadFromFile(resourcePath() + "arcaneBlast.png");
	sf::Sprite background{ t1 };

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

	//List of mobs this round both alive and dead (cleared every round)
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
				g->setPosition(sf::Vector2f{ sf::Mouse::getPosition(app) });
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
				static int tCount = 0;
				tCount++;
				cout << "Towers: " << tCount << endl;
				towers.push_back(std::make_unique<Tower>(t4, sf::Vector2i{ sf::Mouse::getPosition(app).x,sf::Mouse::getPosition(app).y }));

			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
				if (thePlayer.getGold() >= 1000) {
					if (boo.size() < 1) {
						boo.push_back(std::make_unique<Ghost>(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y));
					}
					else {
						boo.erase(boo.begin());
						towers.push_back(std::make_unique<Tower>(t4, sf::Vector2i{ sf::Mouse::getPosition(app).x,sf::Mouse::getPosition(app).y }));
						thePlayer.setGold(thePlayer.getGold() - 1000);
					}
				} else {
					cout << "not enough gold, " << 1000 - thePlayer.getGold() << " more gold required!"  << endl;
				}
			}

            //DEBUG: figure out pixel x,y location of click
            if (event.type == sf::Event::MouseButtonPressed) {
                
                int x{ sf::Mouse::getPosition(app).x }, y{ sf::Mouse::getPosition(app).y };
				cout << x << ", " << y << endl;
				animations.push_back(std::make_unique<Explosion>(t3, sf::Vector2i{ x,y }));
				//kills mobs on click in a 200 x 2 c00 box centered on mouse position
				//for (auto &mob: mobsThisRound) {
				//	if (mob->getPosition().x + 100  >= (x - 74) && mob->getPosition().x - 100 <= (x - 74)) {
				//		if (mob->getPosition().y +100 >= (y-64) && mob->getPosition().y - 100<= (y-64)) {
				//			mob->setHealth(0);
				//		}
				//	}
				//}
				mobsThisRound.killBox(x,y,128,128);
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

		for (const auto &a : animations) {
			app.draw(*a);
		}

		for (const auto &t : towers) {
			app.draw(*t);
		}

		for (const auto &g : boo) {
			app.draw(*g);
		}
		
		sf::Font font;
		font.loadFromFile(resourcePath() + "OpenSans-Regular.ttf");
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
