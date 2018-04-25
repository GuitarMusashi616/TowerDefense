#include <iostream>
#include "clickable.hpp"
using std::shared_ptr;

shared_ptr<Clickable> Clickable::_selected;

Clickable::Clickable() {
    sf::CircleShape circle(100);
    circle.setOutlineColor(sf::Color(0,255,0,20));
    _ghost = circle;
}

sf::CircleShape Clickable::getGhost() {
    return _ghost;
};

void Clickable::select(shared_ptr<Clickable> clicked) {
    _selected = clicked;
    std::cout << "Tower Clickable Clicked: " << clicked << std::endl;
}

shared_ptr<Clickable> Clickable::getSelected() {
    return _selected;
}

