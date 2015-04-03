#include "DataFormat.hpp"
#include "../Resources/Utils.hpp"
#include <string>
#include <SFML/Graphics.hpp>
// So many magic numbers below, sorry...
// ...but is only GUI, ugly GUI :-)
EquipFormat::EquipFormat(MemoryManager* m)
{
    mmgr = m;
    descs["critical"]  = "Cios krytyczny";
    descs["hitpoints"] = "Punkty życia";
    descs["droprate"]  = "Drop przedmiotów";
    descs["unbelive"]  = "Cios niewiarygodny";
    descs["hpregeneration"] = "Regeneracja HP";
    descs["mpregeneration"] = "Regeneracja MP";
    descs["luma"] = "Księżycowy cios";
    descs["mort"] = "Smierć";
}
EquipFormat::~EquipFormat(){}
void EquipFormat::solveType(ITEM_TYPE t, sf::Text& tx)
{
    if(t == WEAPON) tx.setString(L"Typ:Broń");
    if(t == HELMET) tx.setString(L"Typ:Hełm");
    if(t == ARMOR ) tx.setString(L"Typ:Zbroja");
    if(t == PANTS ) tx.setString(L"Typ:Spodnie");
    if(t == BOOTS ) tx.setString(L"Typ:Buty");
    if(t == SHIELD) tx.setString(L"Typ:Tarcza");
    if(t == AMULET) tx.setString(L"Typ:Amulet");
    if(t == POTION) tx.setString(L"Typ:Mikstura");
}
void EquipFormat::transformToReadable(std::string name, std::string val, sf::Color& c)
{
    utf32.clear();
    if(name == "strength")
    {
        c = (mmgr->getStrength() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Siła:");
    }
    if(name == "wisdom")
    {
        c = (mmgr->getWisdom() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Inteligencja:");
    }
    if(name == "charisma")
    {
        c = (mmgr->getCharisma() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Charyzma:");
    }
    if(name == "agility")
    {
        c = (mmgr->getAgility() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Zręczność:");
    }
    if(name == "vital")
    {
        c = (mmgr->getVital() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Witalność:");
    }
    if(name == "energy")
    {
        c = (mmgr->getEnergy() >= std::stoul(val))?(sf::Color::Green):(sf::Color::Red);
        utf32 += to32UTF<std::string>("Energia:");
    }
    utf32 += to32UTF<std::string>(val);
}
void EquipFormat::transformProperties(std::string name, std::string sign, std::string val)
{
    utf32.clear();
    utf32 += to32UTF<std::string>(descs[name]);
    utf32 += to32UTF<std::string>("  ");
    utf32 += to32UTF<std::string>(sign);
    utf32 += to32UTF<std::string>(" ");
    utf32 += to32UTF<std::string>(val);
    utf32 += to32UTF<std::string>("%");
}
#include <iostream>
using namespace std;
void EquipFormat::drawProperties(std::vector<sf::Text>& desc, sf::Text& txt, const ItemData& it)
{
    utf32.clear();
    int hline = helper + 16;
    int i = 0;
    for(auto prop : it.properties)
    {
        std::string name, sign, value;
        sign  = std::get<1>(std::get<0>(prop));
        transformProperties(std::get<0>(std::get<0>(prop)), std::get<1>(std::get<0>(prop)), std::get<1>(prop));
        txt.setString(utf32);
        txt.setPosition(sf::Vector2f(cloud_pos.x + 5, cloud_pos.y + (hline)+(i) ) );
        if(sign == "+")txt.setColor(sf::Color::Green);
        else txt.setColor(sf::Color::Red);
        desc.push_back(txt);
        i+=14;
    }
    lastMohikanin1 = hline + i;
}
void EquipFormat::drawConditions(std::vector<sf::Text>& desc, sf::Text& some_name, const ItemData& it)
{
    int i=5;
    for(auto condition : it.conditions)
    {
        std::string name = std::get<0>(std::get<0>(condition));
        std::string val  = std::get<1>(condition);
        sf::Color c;
        transformToReadable(name, val, c);
        some_name.setString(utf32);
        some_name.setColor(c);
        some_name.setStyle(sf::Text::Style::Regular);
        some_name.setPosition(sf::Vector2f(cloud_pos.x + 5, cloud_pos.y + (16*i)));
        desc.push_back(some_name);
        i++;
    }
    lastCond = i;
}
void EquipFormat::format( const ItemData& itm, const sf::Vector2f& cloud_pos1,unsigned int &border1,
                          sf::Font& font,std::vector<sf::Text>& desc, sf::RectangleShape& cloud     )
{
    cloud_pos = cloud_pos1;
    border    = border1;
    margin    = 5;
    sf::Color col;
    utf32 = to32UTF<std::wstring>(itm.name);
    sf::Text some_name(utf32, font, 15);
    switch(itm.quality)
    {
        case 0: col = sf::Color::White;  break;
        case 1: col = sf::Color::Green;  break;
        case 2: col = sf::Color::Red;    break;
        case 3: col = sf::Color::Cyan;   break;
        case 4: col = sf::Color::Magenta;break;
        default: col = sf::Color::White; break;
    }
    some_name.setColor(col);
    some_name.setPosition(cloud_pos.x + 5, cloud_pos.y);
    some_name.setStyle(sf::Text::Style::Italic);
    desc.push_back(some_name);

    some_name.setPosition(cloud_pos.x + 5, cloud_pos.y+ 17);
    some_name.setString(L"Właściwości");
    some_name.setColor(color0);
    some_name.setCharacterSize(13);
    some_name.setStyle(sf::Text::Style::Italic);
    desc.push_back(some_name);

    some_name.setStyle(sf::Text::Style::Regular);
    solveType(itm.type, some_name);
    some_name.setPosition(cloud_pos.x + 7, cloud_pos.y + 47);
    some_name.setColor(color0);
    some_name.setCharacterSize(13);
    desc.push_back(some_name);
    switch(itm.type)
    {
        case WEAPON:
            formatWeapon(some_name, desc, itm);
        break;
        case ARMOR:
            formatArmor(some_name, desc, itm);
        break;
        case PANTS:
            formatPants(some_name, desc, itm);
        break;
        case BOOTS:
            formatBoots(some_name, desc, itm);
        break;
        case SHIELD:
            formatShield(some_name, desc, itm);
        break;
        case AMULET:
            formatAmulet(some_name, desc, itm);
        break;
        case POTION:
            formatPotion(some_name, desc, itm);
        break;
        case HELMET:
            formatHelmet(some_name, desc, itm);
        break;
        default:
        break;
    }
    some_name.setString(L"Wymagania");
    some_name.setColor(color0);
    some_name.setPosition(sf::Vector2f(cloud_pos.x + 5, cloud_pos.y + (16*4)));
    some_name.setStyle(sf::Text::Style::Italic);
    desc.push_back(some_name);
    drawConditions(desc, some_name, itm);

    some_name.setString(L"Opis");
    some_name.setCharacterSize(13);
    some_name.setColor(color0);
    some_name.setPosition(sf::Vector2f(cloud_pos.x + 5, cloud_pos.y + (16*lastCond)));
    some_name.setStyle(sf::Text::Style::Italic);
    desc.push_back(some_name);

    cndd = (std::count(itm.description.begin(), itm.description.end(), '\n') + 2) / 2;
    some_name.setStyle(sf::Text::Style::Regular);
    utf32.clear();
    utf32 = to32UTF<std::wstring>(itm.description);
    some_name.setString(utf32);
    some_name.setCharacterSize(13);
    some_name.setColor(color2);
    some_name.setPosition(cloud_pos.x + 5, cloud_pos.y+(16*lastCond) + 14);
    desc.push_back(some_name);
    int ix = 16;
    int fckng_offset = 0;
    if(cndd > 1) {ix = 13;fckng_offset = 3;}
    if(cndd > 4) {ix = 13;fckng_offset = 5;}
    if(cndd > 6) {ix = 13;fckng_offset = 7;}
    helper = ((16*lastCond)+14) + (ix*cndd) - fckng_offset;
    some_name.setStyle(sf::Text::Style::Italic);
    some_name.setColor(color0);
    some_name.setString(L"Bonusy");
    some_name.setPosition(cloud_pos.x + 5, cloud_pos.y+(((16*lastCond)+14) + (ix*cndd)) - fckng_offset);
    desc.push_back(some_name);
    drawProperties(desc,some_name, itm);
    cloud.setSize(sf::Vector2f(330,(lastMohikanin1 + 7)));
}
void EquipFormat::formatArmor(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Obrona:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+32);
   some_name.setColor(sf::Color::Green);
   desc.push_back(some_name);
}
void EquipFormat::formatShield(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Obrona:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+32);
   desc.push_back(some_name);
}
void EquipFormat::formatWeapon(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   int marginWep = 5;
   utf32.clear();
   utf32 = to32UTF<std::string>("Atak:");
   utf32 += to32UTF<std::string>(std::to_string(itm.attack));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+marginWep, cloud_pos.y + 32);
   some_name.setColor(sf::Color::Red);
   desc.push_back(some_name);
   utf32.clear();
   utf32 = to32UTF<std::string>("Obrona:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setColor(sf::Color::Yellow);
   some_name.setPosition(cloud_pos.x+border+marginWep+4*14, cloud_pos.y+32);
   desc.push_back(some_name);
   utf32.clear();
   utf32 = to32UTF<std::string>("Szybkość:");
   utf32 += to32UTF<std::string>(std::to_string((int)itm.speed));
   utf32 += to32UTF<std::string>("%");
   some_name.setString(utf32);
   some_name.setColor(sf::Color::Green);
   some_name.setPosition(cloud_pos.x+border+marginWep+9*13, cloud_pos.y+32);
   desc.push_back(some_name);
}
void EquipFormat::formatBoots(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Obrona:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+32);
   desc.push_back(some_name);
}
void EquipFormat::formatPants(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Obrona:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+32);
   desc.push_back(some_name);
}
void EquipFormat::formatHelmet(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
    utf32.clear();
    utf32 = to32UTF<std::string>("Obrona:");
    utf32 += to32UTF<std::string>(std::to_string(itm.defence));
    some_name.setString(utf32);
    some_name.setCharacterSize(13);
    some_name.setPosition(cloud_pos.x + border + margin, cloud_pos.y + 32);
    some_name.setColor(sf::Color::Green);
    desc.push_back(some_name);
}
void EquipFormat::formatAmulet(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Amulet:");
   utf32 += to32UTF<std::string>(std::to_string(itm.defence));
   some_name.setString(utf32);
   some_name.setCharacterSize(13);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+16);
   desc.push_back(some_name);
}
void EquipFormat::formatPotion(sf::Text& some_name, std::vector<sf::Text>& desc, const ItemData& itm)
{
   utf32.clear();
   utf32 = to32UTF<std::string>("Siła odnawiania:");
   utf32 += to32UTF<std::string>(std::to_string(itm.power));
   utf32 += to32UTF<std::string>("%");
   some_name.setString(utf32);
   some_name.setColor(sf::Color::Yellow);
   some_name.setCharacterSize(10);
   some_name.setPosition(cloud_pos.x+border+margin, cloud_pos.y+16);
   desc.push_back(some_name);
}
