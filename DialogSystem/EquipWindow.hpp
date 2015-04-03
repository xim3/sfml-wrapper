#pragma once
#include "GridWindow.hpp"
#include "PopupMenu.hpp"
#include "PlayerEquip.hpp"
#include "../MapSystem/ItemManager.hpp"
#include "../MapSystem/Item.h"
#include "DataFormat.hpp"
#include <utility>
class EquipmentWindow : public GridWindow
{
public:
    EquipmentWindow(sf::Texture*,sf::Font*, sf::Vector2f,unsigned int, unsigned int,
                    bool custom, const ItemManager&,IDataFormat&, sf::Color = sf::Color(50,50,50,200), sf::Color = sf::Color(50,50,50,200)
                   ,unsigned int w_tile = 32, unsigned int h_tile = 32);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void controlCloud(sf::Vector2i);
    void setCloudSize(sf::Vector2f);
    void setBorderThick(unsigned int);
    void addString(const sf::Text);
    void hideMenu();
    void updateItems();
    bool setHelmet(Item&);
    bool setBoots (Item&);
    bool setPants (Item&);
    bool setArmor (Item&);
    bool setShield(Item&);
    bool setWeapon(Item&);
    Item unwearArmor ();
    Item unwearBoots ();
    Item unwearHelmet();
    Item unwearPants ();
    Item unwearWeapon();
    Item unwearShield();
    std::size_t getCapacity() const;
    sf::Vector2f getSize();
    int  getSelected(sf::Vector2i&);
    std::pair<int,int>getSelectedEq(sf::Vector2i&);
    std::pair<int,int>selectedItem (sf::Vector2i&);
private:
    Equip               equipment;
    unsigned int        cloud_border;
    const ItemManager&  _imgr;
    IDataFormat&        formatter;
    sf::RectangleShape  cloud;
    sf::Font            font;
    std::vector<sf::Text> descriptions;
    sf::Clock           click_clock;
    PopupMenu           menu;
    PopupMenu           menu1;
};
