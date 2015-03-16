#pragma once
#include "../MapSystem/Item.h"
#include "../Resources/Utils.hpp"
#include <SFML/Graphics.hpp>
class EquipFormat : public IDataFormat
{
public:
    EquipFormat();
    virtual void format(const ItemData, const sf::Vector2f&,unsigned int&, sf::Font&, std::vector<sf::Text>&);
    ~EquipFormat();
};
