#include "PlayerEquip.hpp"
#include "../Resources/Utils.hpp"
Equip::Equip(unsigned int _wit, unsigned int _hit, unsigned int _th, unsigned int _tw,sf::Texture* _gtex, sf::Vector2f _position)
: GridWindow(_gtex, _position,_wit,_hit,_th,_tw)
{
}
void Equip::setBgTiles()
{
    appendItem(0, 1, 710, 1);
    appendItem(1, 0, 710, 1);
    appendItem(1, 1, 710, 1);
    appendItem(1, 2, 710, 1);
    appendItem(1, 3, 710, 1);
    appendItem(2, 1, 710, 1);
}
#include <iostream>
using namespace std;
int Equip::underPart(sf::Vector2i mouse)
{
    std::cout << "=========================BB===================\n";
    for(auto i : items_in_grid)
    {
        printf("Id:%i Gid:%i Size:%i\n", i.id, i.gid,items_in_grid.size());
    }
    std::cout << "=========================CC===================\n";
    sf::Vector2i sqr = underSquare(mouse);
    if(sqr.x == 0 && sqr.y == 1) return 0; // weapon
    if(sqr.x == 1 && sqr.y == 0) return 1; // helmet
    if(sqr.x == 1 && sqr.y == 1) return 2; // armor
    if(sqr.x == 1 && sqr.y == 2) return 3; // pants
    if(sqr.x == 1 && sqr.y == 3) return 4; // boots
    if(sqr.x == 2 && sqr.y == 1) return 5; // shield
    return -1;
}
bool Equip::setWeapon(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(0,1)));
    if(it == items_in_grid.end())
    {
        appendItem(0, 1, i.gid,0);
        items_in_grid.push_back(Item(0,1, i.gid,i.id));
        return true;
    }
    return false;
}
bool Equip::setHelmet(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,0)));
    if(it == items_in_grid.end())
    {
        appendItem(1,0, i.gid,0);
        items_in_grid.push_back(Item(1,0, i.gid,i.id));
        return true;
    }
    return false;
}
bool Equip::setArmor(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,1)));
    if(it == items_in_grid.end())
    {
        appendItem(1,1, i.gid,0);
        items_in_grid.push_back(Item(1,1, i.gid,i.id));
        return true;
    }
    return false;
}
bool Equip::setPants(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,2)));
    if(it == items_in_grid.end())
    {
        appendItem(1,2, i.gid, 0);
        items_in_grid.push_back(Item(1,2, i.gid,i.id));
        return true;
    }
    return false;
}
bool Equip::setBoots(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,3)));
    if(it == items_in_grid.end())
    {
        appendItem(1,3, i.gid, 0);
        items_in_grid.push_back(Item(1,3, i.gid,i.id));
        return true;
    }
    return false;
}
bool Equip::setShield(Item& i)
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(2,1)));
    if(it == items_in_grid.end())
    {
        appendItem(2, 1,i.gid,0);
        items_in_grid.push_back(Item(2,1, i.gid,i.id));
        return true;
    }
    return false;
}
Item Equip::unwearWeapon()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(0,1)));
    if(it != items_in_grid.end())
    {
        appendItem(0, 1, 0,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
Item Equip::unwearHelmet()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,0)));
    if(it != items_in_grid.end())
    {
        appendItem(1,0, 0 ,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
Item Equip::unwearArmor()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,1)));
    if(it != items_in_grid.end())
    {
        appendItem(1, 1, 0,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
Item Equip::unwearPants()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,2)));
    if(it != items_in_grid.end())
    {
        appendItem(1, 2, 0,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
Item Equip::unwearBoots()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(1,3)));
    if(it != items_in_grid.end())
    {
        appendItem(1, 3, 0,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
Item Equip::unwearShield()
{
    auto it = std::find_if(items_in_grid.begin(), items_in_grid.end(),
                           std::bind(xyCompare<Item, sf::Vector2u>, std::placeholders::_1, sf::Vector2u(2,1)));
    if(it != items_in_grid.end())
    {
        appendItem(2, 1, 0,0);
        Item buf = *it;
        items_in_grid.erase(it);
        return buf;
    }
    else return Item(0,0,0,-1);
}
void Equip::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(grid,states);
}
