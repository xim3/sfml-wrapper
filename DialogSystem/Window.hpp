#pragma once
#include "ItemGrid.hpp"
#include <SFML/Graphics.hpp>
class Window : public sf::Drawable, public sf::Transformable
{
    public:
        Window(sf::Texture*,sf::Vector2f);
        virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
    protected:
        sf::Texture *_bg1;
        sf::Sprite _background;
        sf::RenderWindow* window;
        sf::Vector2f position;
        sf::Vector2f size;
};

