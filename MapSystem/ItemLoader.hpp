#pragma once
#include "../Resources/Utils.hpp"
class ItemLoader : public IItemRead
{
public:
    ItemLoader();
    bool read(TiXmlElement*, std::vector<ItemData>&) override;
    ~ItemLoader();
    bool loadBoots (TiXmlElement*);
    bool loadArmor (TiXmlElement*);
    bool loadPants (TiXmlElement*);
    bool loadHelmet(TiXmlElement*);
    bool loadWeapon(TiXmlElement*);
    bool loadShield(TiXmlElement*);
    bool loadAmulet(TiXmlElement*);
    bool loadCondit(TiXmlElement*);
    bool loadProper(TiXmlElement*);
    std::vector<std::string> splitString(std::string);
private:
    unsigned int _attack,_quality,_price,_defence,_power;
    double _speed;
    std::wstring name,desc;
    std::vector<std::pair<std::pair<std::string, std::string>, std::string>> cond;
    std::vector<std::pair<std::pair<std::string, std::string>, std::string>> prop;
};
