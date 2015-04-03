#pragma once
#include "../MapSystem/Item.h"
#include "../Resources/Utils.hpp"
#include "../Person/MemoryBridge.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
class EquipFormat : public IDataFormat
{
public:
    EquipFormat(MemoryManager*);
    virtual void format(const ItemData&, const sf::Vector2f&,unsigned int&, sf::Font&, std::vector<sf::Text>&, sf::RectangleShape&);
    ~EquipFormat();
    void formatHelmet(sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatPants (sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatShield(sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatBoots (sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatArmor (sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatWeapon(sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatAmulet(sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void formatPotion(sf::Text&, std::vector<sf::Text>&,   const ItemData&);
    void drawConditions(std::vector<sf::Text>&, sf::Text&, const ItemData&);
    void drawProperties(std::vector<sf::Text>&, sf::Text&, const ItemData&);
    void transformToReadable(std::string, std::string, sf::Color&);
    void transformProperties(std::string, std::string,std::string);
    void solveType(ITEM_TYPE, sf::Text&);
private:
    MemoryManager* mmgr;
    std::basic_string<sf::Uint32> utf32;
    std::unordered_map<std::string, std::string> descs;
    sf::Vector2f cloud_pos;
    int border, margin;
    int lastCond;
    int lastMohikanin1;
    int cndd;
    int helper;
    sf::Color color0 = sf::Color(255,128,0);
    sf::Color color1 = sf::Color(255, 51,153);
    sf::Color color2 = sf::Color(204,229,255);


};
