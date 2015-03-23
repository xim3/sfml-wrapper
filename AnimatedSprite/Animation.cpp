#include "Animation.hpp"
Animation::Animation() : m_texture(NULL){}
/**
 * \brief dodaje klatke animacji
 * \param rect klatka animacji
 * \return null
 */
void Animation::addFrame(sf::IntRect rect){
    m_frames.push_back(rect);
}
/**
 * \brief ustawia tileset z animacjami
 * \param texture tileset
 */
void Animation::setTileset(const sf::Texture& texture){
    m_texture = &texture;
}
/**
 * \brief zwraca tileset
 * \return wskaźnik do tileseta
 */
const sf::Texture* Animation::getSpriteSheet() const{
    return m_texture;
}
/**
 * \brief zwraca ilość klatek w animacji
 * \return ilość klatek
 */
std::size_t Animation::getSize() const{
    return m_frames.size();
}
/**
 * \brief zwraca klatke
 * \details zwraca klatke z vectora klatek
 * \param numer klatki
 * \return referencja do klatki animacji
 */
const sf::IntRect& Animation::getFrame(std::size_t n) const{
    return m_frames.at(n);
}
/**
 * \brief ustawia wiekość kafla
 */
inline void Animation::setTileSize(unsigned int width, unsigned int height)
{
	tile_height = width;
	tile_height = height;
}
/**
 * \brief dodaje klatke
 * \details dodaje klatke na podstawie GID(przeliczonych współrzędnych na wielkość w kaflach) a nie współrzędnych całej tekstury
 * \param GID gid klatki
 * \return null
 */
void Animation::addFrameGID(unsigned int GID){
	sf::Int32 tu = GID % (m_texture->getSize().x / tile_width);
	sf::Int32 tv = GID / (m_texture->getSize().x / tile_height);
	m_frames.push_back(sf::IntRect(tu * tile_width, tv * tile_height,tile_width,tile_height));
}
