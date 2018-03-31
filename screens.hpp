#ifndef screens_hpp
#define screens_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Screens
{
    public :
    virtual int run(sf::RenderWindow &app) =0;
};


#endif /* screens_hpp */
