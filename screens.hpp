#ifndef screens_hpp
#define screens_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "framework.hpp"

class Screens
{
    public :
    virtual int run(sf::RenderWindow &app, const Framework & framework) =0;
};


#endif /* screens_hpp */
