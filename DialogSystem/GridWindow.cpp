#include "GridWindow.hpp"
GridWindow::GridWindow
(sf::Texture* _tex,sf::Texture* _gtex, sf::Vector2f _position,
 unsigned int w_tiles, unsigned int h_tiles,
 unsigned int w_tile, unsigned int h_tile)
:Window(_tex,position)
,grid(w_tiles,h_tiles,w_tile,h_tile)
{
	grid.loadTex(_gtex);
	setPosition(_position);
}
void GridWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = _bg1;
	target.draw(_background,states);
	grid.draw(target,states);
}
void GridWindow::append(const unsigned int x,const unsigned int y, const unsigned int GID){
	grid.appendItem(x,y,GID);
}
