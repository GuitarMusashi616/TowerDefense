#ifndef menu_hpp
#define menu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "screens.hpp"
#include "framework.hpp"

class MenuScreen : public Screens
{
    public:
    int run(sf::RenderWindow &app, const Framework & framework);
};

#endif /* screen_0_hpp */
