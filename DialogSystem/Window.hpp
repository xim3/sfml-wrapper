#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class IWindow : public sf::Transformable, public sf::Drawable
{
public:
    IWindow();
    virtual bool intersects(sf::Vector2i&) = 0;
    virtual bool isVisible() = 0;
    virtual void setVisible(bool) = 0;
    virtual bool buttonHold(int) = 0;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
protected:
    bool                  hoover;
    bool                  visible;
    sf::Clock             click_clock;
};
