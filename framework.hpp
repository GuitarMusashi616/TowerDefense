

#ifndef framework_hpp
#define framework_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Framework {
public:
    Framework(sf::Window & app, const sf::Vector2f & viewSize);
    void handleEvents(sf::Window & app, sf::Event & event) const;
    float getAspectRatio() const;
    sf::Vector2f getCorrectedMousePosition(const sf::Window & app, const sf::Vector2f & vector) const;
    sf::Vector2f getCorrectedMousePosition(const sf::Window & app, float x, float y) const;
    int getWindowX() const;
    int getWindowY() const;
    sf::Vector2f getViewSize() const;
    sf::Vector2f getInitialWindowSize() const;

private:
    int _xSize;
    int _ySize;
    sf::Vector2f _viewSize;
    sf::Vector2f _initialWindowSize;
    float _aspectRatio;
};


#endif /* framework_hpp */
