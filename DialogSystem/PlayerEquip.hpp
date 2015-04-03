#pragma once
#include "GridWindow.hpp"
class Equip : public GridWindow
{
public:
    Equip(unsigned int, unsigned int, unsigned int ,unsigned int,sf::Texture*, sf::Vector2f);
    bool setHelmet (Item&);
    bool setWeapon (Item&);
    bool setArmor  (Item&);
    bool setShield (Item&);
    bool setPants  (Item&);
    bool setBoots  (Item&);
    Item unwearArmor();
    Item unwearBoots();
    Item unwearHelmet();
    Item unwearPants();
    Item unwearWeapon();
    Item unwearShield();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setBgTiles();
    int  underPart(sf::Vector2i);
};
