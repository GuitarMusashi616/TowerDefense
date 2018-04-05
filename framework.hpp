

#ifndef framework_hpp
#define framework_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Framework {
public:
    Framework(sf::Window & app);
    void handleEvents(sf::Window & app, sf::Event & event) const;
    float getAspectRatio() const;
    sf::Vector2f getCorrectedMousePosition(const sf::Window & app, const sf::Vector2f & vector) const;
private:
    int _xSize;
    int _ySize;
    float _aspectRatio;
};


#endif /* framework_hpp */
