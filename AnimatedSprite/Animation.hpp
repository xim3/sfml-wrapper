#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
/**
 * \brief Klasa przechowująca klatki animacji i ich teksture
 *
 **/
class Animation
{
public:
    Animation();
    void setTileSize(unsigned int width, unsigned int height);
    void addFrame(sf::IntRect rect);
    void addFrameGID(unsigned int i);
    void setTileset(const sf::Texture& texture);
    const sf::Texture* getSpriteSheet() const;
    std::size_t getSize() const;
    const sf::IntRect& getFrame(std::size_t n) const;
private:
    std::vector<sf::IntRect> m_frames;
    const sf::Texture* m_texture;
    unsigned int tile_width = 32;
    unsigned int tile_height= 32;
};
