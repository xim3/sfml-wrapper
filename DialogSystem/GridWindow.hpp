#pragma once
#include "ItemGrid.hpp"
#include "../MapSystem/Item.h"
#include <SFML/Graphics.hpp>
// TODO
// Zła architektura
class GridWindow : public sf::Drawable, public sf::Transformable
{
public:
    GridWindow(sf::Texture*,sf::Vector2f, unsigned int,unsigned int,
               unsigned int w_tile = 32, unsigned int h_tile = 32,
               sf::Color = sf::Color(50,50,50,200), sf::Color = sf::Color(50,50,50,200));
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void update(const std::vector<Item>&);
    void refresh(unsigned int);
    void move(const sf::Vector2f&);
    unsigned int getGID(sf::Vector2i);
    sf::Vector2i underSquare(sf::Vector2i&);
    bool intersects(const sf::Vector2i&);
protected:
    bool hoover;
    ItemGrid grid;
    bool in_area;
    sf::RectangleShape _backgrd;
    std::vector<Item> items_in_grid;
};
