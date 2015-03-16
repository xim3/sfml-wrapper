#pragma once
#include "GridWindow.hpp"
#include "../MapSystem/ItemManager.hpp"
#include "../MapSystem/Item.h"
#include "DataFormat.hpp"
class EquipmentWindow : public GridWindow
{
public:
    EquipmentWindow(sf::Texture*,sf::Font*, sf::Vector2f,unsigned int , unsigned int,
                    const ItemManager&,IDataFormat&, sf::Color = sf::Color(50,50,50,200), sf::Color = sf::Color(50,50,50,200)
                    ,unsigned int w_tile = 32, unsigned int h_tile = 32);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void controlCloud(sf::Vector2i);
    void setCloudSize(sf::Vector2f);
    void setBorderThick(unsigned int);
    void addString(const sf::Text);
    std::size_t getCapacity() const;
private:
    unsigned int cloud_border;
    bool hoover;
    const ItemManager& _imgr;
    IDataFormat&       formatter;
    sf::RectangleShape cloud;
    sf::Font            font;
    std::vector<sf::Text> descriptions;
};
