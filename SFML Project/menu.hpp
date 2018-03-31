#ifndef menu_hpp
#define menu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "screens.hpp"

class MenuScreen : public Screens
{
    public:
    int run(sf::RenderWindow &app);
};


#endif /* screen_0_hpp */
