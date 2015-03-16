#include "ItemGrid.hpp"
ItemGrid::ItemGrid(unsigned int _wit, unsigned int _hit, unsigned int _th, unsigned int _tw )
: width_in_tiles(_wit)
, height_in_tiles(_hit)
, tile_height(_th)
, tile_width(_tw)
, lastX(0)
, lastY(0)
{
	grid.setPrimitiveType(sf::Quads);
    grid.resize(width_in_tiles * height_in_tiles * 4);
}
void ItemGrid::loadTex(sf::Texture* tex){
	_tex = tex;
}
void ItemGrid::appendItem(const int _x, const int _y, const unsigned int GID){
    lastX = _x;
    lastY = _y;
	if((lastX >= width_in_tiles || lastY >= height_in_tiles) || (lastX < 0 || lastY < 0))
		return;
	sf::Int32 tu = GID  % (_tex->getSize().x / tile_width);
	sf::Int32 tv = GID  / (_tex->getSize().x / tile_height);
	sf::Vertex* quad;
	quad = &grid[(lastX + lastY * width_in_tiles) * 4];
	quad[0].position  = sf::Vector2f(lastX * tile_width, lastY * tile_height);
	quad[1].position  = sf::Vector2f((lastX + 1) * tile_width, lastY * tile_height);
	quad[2].position  = sf::Vector2f((lastX + 1) * tile_width, (lastY + 1) * tile_height);
	quad[3].position  = sf::Vector2f(lastX * tile_width, (lastY + 1) * tile_height);
	quad[0].texCoords = sf::Vector2f(tu * tile_width, tv * tile_height);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tile_width, tv * tile_height);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tile_width, (tv + 1) * tile_height);
	quad[3].texCoords = sf::Vector2f(tu * tile_width, (tv + 1) * tile_height);
}
void ItemGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = _tex;
	target.draw(grid,states);
}
void ItemGrid::cleanLastSquare(unsigned int transp_square){
    appendItem(lastX,lastY,0);
}
sf::Vector2u ItemGrid::getSize() const{
    return sf::Vector2u(width_in_tiles, height_in_tiles);
}
sf::Vector2u ItemGrid::getTileSize() const{
    return sf::Vector2u(tile_width, tile_height);
}
