#pragma once
#include <SFML/Graphics.hpp>
class Window : public sf::Drawable, public sf::Transformable
{
public:
    Window(sf::Texture*, sf::Vector2f);
    bool intersects(sf::Vector2i&);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
protected:
    sf::Texture *_bg1 = nullptr;
    sf::Sprite _background;
    sf::Vector2f size;
    bool hoover;
};

