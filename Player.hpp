//
//  Player.hpp
//  TowerDefense projectcs202
//


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#ifndef Player_hpp
#define Player_hpp

class Player//player class stationary position on map
{
public:
    Player();
    ~Player();
    void setLife(int life);
    void setUpgrade(int upgrade);
    void setGold(int gold);//starting gold
    int getLife() const;
    int getGold() const;//might change this to Mobtype for gold drops
    int getUpgrade() const; // choices between upgrading towers or player defense. just an idea :)
    void death() const;
    
protected:
    int _life;
    int _gold;
    int _upgrade;
};


#endif

