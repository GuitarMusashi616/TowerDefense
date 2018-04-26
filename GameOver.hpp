#ifndef GameOver_hpp
#define GameOver_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "screens.hpp"
#include "framework.hpp"

class GameOver : public Screens
{
public:
    int run(sf::RenderWindow &app, const Framework & framework);
};

#endif
