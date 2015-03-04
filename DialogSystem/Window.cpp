#include "Window.hpp"
#include "../Resources/easylogging++.h"
Window::Window(sf::Texture* tex,sf::Vector2f _position) 
: _bg1(tex)
, _background(*tex)
, position(_position)
, size(tex->getSize().x, tex->getSize().y)
{
	setPosition(_position);
}
void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = _bg1;
	target.draw(_background,states);	
}
