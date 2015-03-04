#include "ItemGrid.hpp"
ItemGrid::ItemGrid(unsigned int _wit, unsigned int _hit, unsigned int _th, unsigned int _tw ) 
: width_in_tiles(_wit)
, height_in_tiles(_hit)
, tile_height(_th)
, tile_width(_tw)
{
	grid.setPrimitiveType(sf::Quads);
    grid.resize(width_in_tiles * height_in_tiles * 4); 
}
void ItemGrid::loadTex(sf::Texture* tex){
	_tex = tex;
}
void ItemGrid::appendItem(const unsigned int x,const unsigned int y, const unsigned int GID){
	if(x >= width_in_tiles || y>= height_in_tiles)
		return;
	sf::Int32 tu = GID  % (_tex->getSize().x / tile_width);
	sf::Int32 tv = GID / (_tex->getSize().x / tile_height);
	sf::Vertex* quad;
	quad = &grid[(x + y * width_in_tiles) * 4];	
	quad[0].position = sf::Vector2f(x * tile_width, y * tile_height);
	quad[1].position = sf::Vector2f((x + 1) * tile_width, y * tile_height);
	quad[2].position = sf::Vector2f((x + 1) * tile_width, (y + 1) * tile_height);
	quad[3].position = sf::Vector2f(x * tile_width, (y + 1) * tile_height);
			
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
