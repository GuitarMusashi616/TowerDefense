//
//  clickable.cpp
//  csTD2
//
//  Created by Rowan Biessel on 4/19/18.
//  Copyright © 2018 Rowan Biessel. All rights reserved.
//
#include <iostream>
#include "clickable.hpp"

clickable::clickable() {
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color(0,255,0,20));
    _ghost = circle;
    std::cout << "Created Clickable! R: " << circle.getRadius()  << std::endl;
}

sf::CircleShape clickable::getGhost() {
    return _ghost;
};

