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
    /* tu jest SIGSEGV ale nie wiem gdzie bo sie schował cwaniak
     CALL TRACE
     0x804ddeb Animation::getFrame(this=0xb7e14237,n=0)
     0x804d4e1 AnimatedTex::setFrame(this=0xbffff170, newFrame=0)
     0x804d54b AnimatedTex::setAnimation(this=0xbffff170, animation=...)
     0x804d53b AnimatedTex::play(this=0xbffff170, animation=...)
     0x8083b11 Entity::update(this=0xbffff0b8)
     0x80773d0 main()
     Kiedyś go znajde, znajde go, i go naprawie :D
    */
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
