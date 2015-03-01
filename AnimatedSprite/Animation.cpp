#include "Animation.hpp"
Animation::Animation() : m_texture(NULL){}
void Animation::addFrame(sf::IntRect rect){
    m_frames.push_back(rect);
}
void Animation::setTileset(const sf::Texture& texture){
    m_texture = &texture;
}
const sf::Texture* Animation::getSpriteSheet() const{
    return m_texture;
}
std::size_t Animation::getSize() const{
    return m_frames.size();
}
const sf::IntRect& Animation::getFrame(std::size_t n) const{
    return m_frames[n];
}
inline void Animation::setTileSize(unsigned int width, unsigned int height)
{
	tile_height = width;
	tile_height = height;
}
void Animation::addFrameGID(unsigned int GID){
	sf::Int32 tu = GID % (m_texture->getSize().x / tile_width);
	sf::Int32 tv = GID / (m_texture->getSize().x / tile_height);
	m_frames.push_back(sf::IntRect(tu * tile_width, tv * tile_height,tile_width,tile_height));
}
