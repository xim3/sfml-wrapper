#pragma once
#include "../Resources/Utils.hpp"
#include "ItemGrid.hpp"
#include "../MapSystem/Item.h"
#include <SFML/Graphics.hpp>
class GridWindow : public IWindow
{
public:
    GridWindow(sf::Texture*,sf::Vector2f, unsigned int,unsigned int,
               unsigned int w_tile = 32, unsigned int h_tile = 32,
               sf::Color = sf::Color(50,50,50,200), sf::Color = sf::Color(50,50,50,200));
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void update(const std::vector<Item>&);
    void refresh(unsigned int);
    void move(const sf::Vector2f&);
    void appendBackground();
    void cleanBg();
    void resizeBg();
    void appendItem(const int,const int,const int,const int);
    void setVisible(bool);
    unsigned int getGID(sf::Vector2i);
    unsigned int getID(sf::Vector2i);
    bool intersects(sf::Vector2i&);
    bool isVisible() const;
    bool buttonHold(int);
    sf::Vector2i underSquare(sf::Vector2i&);
protected:
    ItemGrid grid;
    sf::RectangleShape _backgrd;
    std::vector<Item> items_in_grid;
};
