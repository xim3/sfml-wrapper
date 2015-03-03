#include "Button.h"

Button::Button(sf::Text new_text,sf::Texture &txt, sf::Vector2f postion)
{
    sprite.setTexture(txt);

    text = new_text;
    sprite.setPosition(postion);
    text.setPosition(postion.x + 1, postion.y + 1);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(text);
}

bool Button::click(sf::RenderWindow& window, sf::Sprite sprite, sf::Event &event)
{
    sf::Vector2f mouse(sf::Mouse::getPosition(window));
    // a co tu sie wyrabia panie kolego?
    // fixnij to.
    if( sprite.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left )
        return true;
    else
        return false;
}

sf::Sprite Button::getSprite()
{
    return sprite;
}

Button Button::create(sf::Text new_text, sf::Texture& txt, sf::Vector2f postion)
{
    Button toReturn(new_text, txt, postion);
    return toReturn;
}
