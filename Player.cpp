//
//  Player.cpp
//  TowerDefense projectcs202
//

#include "Player.hpp"
Player::Player() : _life{ 100 }, _gold{ 1 } , _upgrade{ 1 }
{
}
void Player::setLife(int Life)
{
    _life = Life; // might add hp regen later
}
int Player::getLife() const
{
    return _life;
}
void Player::setGold(int gold)
{
    _gold = gold;
}
int Player::getGold() const
{
    return _gold;//maby Mobtype dropping gold when killed ?
}
void Player::setUpgrade(int upgrade)
{
    _upgrade = upgrade;
}
int Player::getUpgrade() const
{
    return _upgrade;
}
void Player::death() const
{
    if(_life >= 0)
    {
        // Player still alive
    }
    else if(_life <= 0)
    {
        std::cout<<"Game Over"<<std::endl;//adding a gameover screen sometime later
    }
}
