
#ifndef clickable_hpp
#define clickable_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <memory>


class Clickable : public std::enable_shared_from_this<Clickable> {
public:
    Clickable();
    virtual void onClick() =0;
    sf::CircleShape getGhost();
    static void select(std::shared_ptr<Clickable> clicked);
    static std::shared_ptr<Clickable> getSelected();
private:
    static std::shared_ptr<Clickable> _selected;
    sf::CircleShape _ghost;
protected:
    template <typename Derived>
    std::shared_ptr<Derived> shared_from_base()
    {
        return std::static_pointer_cast<Derived>(shared_from_this());
    }
};

#endif /* clickable_hpp */
