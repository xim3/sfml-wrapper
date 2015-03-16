#include "DataFormat.hpp"
#include "../Resources/Utils.hpp"
#include <string>
#include <SFML/Graphics.hpp>
EquipFormat::EquipFormat() {}
EquipFormat::~EquipFormat(){}
void EquipFormat::format(const ItemData itm, const sf::Vector2f& cloud_pos,unsigned int &border,sf::Font& font,std::vector<sf::Text>& desc)
{
    std::basic_string<sf::Uint32> utf32;
    sf::Color col;
    sf::Utf8::toUtf32(itm.name.begin(), itm.name.end(), std::back_inserter(utf32));
    sf::Text some_name(utf32, font, 15);
    switch(itm.quality)
    {
        case 0: col = sf::Color::Blue; break;
        case 1: col = sf::Color::Black; break;
        case 2: col = sf::Color::Yellow; break;
        case 3: col = sf::Color::Red; break;
    }
    some_name.setColor(col);
    some_name.setPosition(cloud_pos.x, cloud_pos.y);
    desc.push_back(some_name);
    switch(itm.type)
    {
        case WEAPON:
        utf32.clear();
        utf32 = to32UTF<std::string>("Atak:");
        utf32 += to32UTF<std::string>(std::to_string(itm.attack));
        some_name.setString(utf32);
        some_name.setCharacterSize(13);
        some_name.setPosition(cloud_pos.x+border, cloud_pos.y+16);
        some_name.setColor(sf::Color::Red);
        desc.push_back(some_name);
        utf32.clear();
        utf32 = to32UTF<std::string>("Obrona:");
        utf32 += to32UTF<std::string>(std::to_string(itm.defence));
        some_name.setString(utf32);
        some_name.setColor(sf::Color::Green);
        some_name.setPosition(cloud_pos.x+border, cloud_pos.y+(14*2));
        desc.push_back(some_name);
        utf32.clear();
        utf32 = to32UTF<std::string>("Szybkość:");
        utf32 += to32UTF<std::string>(std::to_string((int)itm.speed));
        utf32 += to32UTF<std::string>("%");
        some_name.setString(utf32);
        some_name.setColor(sf::Color::Cyan);
        some_name.setPosition(cloud_pos.x+border, cloud_pos.y+(14*3));
        desc.push_back(some_name);
        break;
        case ARMOR:
        utf32.clear();
        utf32 = to32UTF<std::string>("Obrona:");
        utf32 += to32UTF<std::string>(std::to_string(itm.defence));
        some_name.setString(utf32);
        some_name.setCharacterSize(13);
        some_name.setPosition(cloud_pos.x+border, cloud_pos.y+16);
        some_name.setColor(sf::Color::Green);
        desc.push_back(some_name);
        break;
        case RECOVERY:
        utf32.clear();
        utf32 = to32UTF<std::string>("Siła odnawiania:");
        utf32 += to32UTF<std::string>(std::to_string(itm.power));
        utf32 += to32UTF<std::string>("%");
        some_name.setString(utf32);
        some_name.setColor(sf::Color::Yellow);
        some_name.setCharacterSize(10);
        some_name.setPosition(cloud_pos.x+border, cloud_pos.y+16);
        desc.push_back(some_name);
        break;
        default:
        break;
    }
    utf32.clear();
    utf32 = to32UTF<std::wstring>(itm.description);
    some_name.setString(utf32);
    some_name.setCharacterSize(13);
    some_name.setColor(sf::Color::Yellow);
    some_name.setPosition(cloud_pos.x, cloud_pos.y+(16*4));
    desc.push_back(some_name);
}
