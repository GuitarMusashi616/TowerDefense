
#ifndef clickable_hpp
#define clickable_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <memory>


class clickable {
public:
    clickable();
    virtual void onClick() =0;
    sf::CircleShape getGhost();
    void select();
    std::unique_ptr<clickable> getSelected();
    
private:
    static std::unique_ptr<clickable> _clicked;
    sf::CircleShape _ghost;
};

#endif /* clickable_hpp */
