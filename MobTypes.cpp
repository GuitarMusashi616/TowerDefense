#include "MobTypes.h"

Ship::Ship() : Mob{}
{
}

Ship::Ship(sf::Texture &texture) : Mob{ texture,{0,0},1,1 }
{
}

Ship::~Ship() 
{
}
