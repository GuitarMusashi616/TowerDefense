#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "screens.hpp"

class GameScreen : public Screens
{
public:
    int run(sf::RenderWindow &app);
    
};


#endif /* game_hpp */
