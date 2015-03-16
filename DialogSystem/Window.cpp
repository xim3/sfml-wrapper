#include "Window.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Resources/easylogging++.h"
Window::Window(sf::Texture* texi, sf::Vector2f pos)
:_bg1(texi)
,_background(*texi)
,size(_bg1->getSize())
,hoover(false)
{
    setPosition(pos);
}
void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = _bg1;
	target.draw(_background,states);
}
bool Window::intersects(sf::Vector2i& vct){
    if((vct.x >= getPosition().x && vct.x <= (getPosition().x + size.x))
    && (vct.y >= getPosition().y && vct.y <= (getPosition().y + size.y))){
        hoover = true;
        return true;
    }
    hoover = false;
    return false;
}

