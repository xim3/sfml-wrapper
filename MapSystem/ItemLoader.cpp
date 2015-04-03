#include "ItemLoader.hpp"
#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/easylogging++.h"
#include <iostream>
using namespace std;
ItemLoader::ItemLoader()
{

}
ItemLoader::~ItemLoader()
{

}
bool ItemLoader::read(TiXmlElement* item, std::vector<ItemData>& itemsinfo)
{
    std::wstring nline_pattern = L"\\n";
    while(item)
    {
        int gid = (atoi(item->Attribute("gid")) );
        name = wide_string<std::wstring>(item->Attribute("name"));
        TiXmlElement* descr = item->FirstChildElement("desc");
        desc = wide_string<std::wstring>(descr->GetText());
        size_t pos = 0;
        while ((pos = desc.find(L"\\n", pos)) != std::string::npos)
        {
            desc.replace(pos-nline_pattern.length(),4,L"\n\n");
        }
        TiXmlElement* data = descr->NextSiblingElement("data");
        TiXmlElement* properties = NULL;
        ITEM_TYPE typen = (ITEM_TYPE)atoi(item->Attribute("type"));
        switch(typen)
        {
           case WEAPON:
           loadCondit(data);
           if(!loadWeapon(data)) return false;
           break;
           case ARMOR:
           loadCondit(data);
           if(!loadArmor(data)) return false;
           break;
           case PANTS:
           loadCondit(data);
           if(!loadPants(data)) return false;
           break;
           case BOOTS:
           loadCondit(data);
           if(!loadBoots(data)) return false;
           break;
           case SHIELD:
           loadCondit(data);
           if(!loadShield(data)) return false;
           break;
           case HELMET:
           loadCondit(data);
           if(!loadHelmet(data)) return false;
           break;
           case AMULET:
           loadCondit(data);
           if(!loadAmulet(data)) return false;
           break;
           case POTION:
           break;
           case NOT_WEAR:
           break;
           default:
           _attack = _defence = _quality = _power = _price  = 0;
           _speed  = 0.0f;
       }
       ItemData buf(typen, desc, name,_attack,_defence,_quality,_price,_power,_speed,gid);
       if(data->NextSiblingElement("properties") != NULL)
       {
           prop.clear();
           properties = data->NextSiblingElement("properties");
           loadProper(properties);
           buf.setProperties(prop);
       }
       buf.setConditions(cond);
       itemsinfo.push_back(buf);
       item = item->NextSiblingElement("item");
    }
    return true;
}
std::vector<std::string> ItemLoader::splitString(std::string params)
{
    std::stringstream ss(params);
    std::string cond;
    std::vector<std::string> buf;
    while (std::getline(ss, cond, ','))
    {
        if(isspace(cond[0]))
            cond.erase(cond.begin());
        buf.push_back(cond);
    }
    return buf;
}
bool ItemLoader::loadCondit(TiXmlElement* data)
{
    cond.clear();
    std::string signs[] = {">","<","==","!=",">=", "<="};
    if(data->Attribute("conditions") == NULL)
        return false;
    std::vector<std::string> conditions = splitString(data->Attribute("conditions"));
    std::string first_arg;
    std::string comp_type;
    for(auto condition : conditions)
    {
        std::pair<std::pair<std::string, std::string>, std::string> cnd;
        size_t first_space = condition.find(" ");
        size_t sign_pos = std::string::npos;
        first_arg = condition.substr(0, first_space);
        for(auto sign : signs)
        {
            sign_pos = condition.find(sign);
            if(sign_pos != std::string::npos)
            {
                comp_type = condition.substr(sign_pos, 2);
                break;
            }
        }
        std::string s_value;
        auto second_argument = std::find_if(condition.begin() + sign_pos, condition.end(), [](char c)->bool{return isdigit(c);});
        if(second_argument != condition.end())
            s_value = std::string(second_argument, condition.end());
        else
        {
          auto s_second_argument = std::find_if(condition.begin() + sign_pos, condition.end(), [](char c)->bool{return isalpha(c);});
          s_value = std::string(s_second_argument, condition.end());
        }
        std::get<0>(std::get<0>(cnd)) = first_arg;
        std::get<1>(std::get<0>(cnd)) = comp_type;
        std::get<1>(cnd)              = s_value;
        cond.push_back(cnd);
    }
    return true;
}
bool ItemLoader::loadProper(TiXmlElement* proper)
{
    if(proper->FirstChildElement("attr") != NULL)
    {
        TiXmlElement* attr = proper->FirstChildElement("attr");
        std::string param, value, sign;
        while(attr)
        {
            std::pair<std::pair<std::string, std::string>,std::string> prop1;
            if(attr->Attribute("name") != NULL ) param = attr->Attribute("name");
            if(attr->Attribute("sign") != NULL ) sign = attr->Attribute("sign");
            if(attr->Attribute("value") != NULL) value = attr->Attribute("value");
            std::get<0>(std::get<0>(prop1)) = param;
            std::get<1>(std::get<0>(prop1)) = sign;
            std::get<1>(prop1)              = value;
            prop.push_back(prop1);
            attr = attr->NextSiblingElement("attr");
        }
    }
    else return false;
    return true;
}
bool ItemLoader::loadBoots (TiXmlElement* data)
{
     if(data->Attribute("power") == NULL || data->Attribute("price") == NULL || data->Attribute("defence") == NULL || data->Attribute("quality") == NULL)
     {
         LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
          return false;
     }
     _attack = _defence = _speed = _quality = 0;
     _speed = 0;
     _power = atoi(data->Attribute("power"));
     _price = atoi(data->Attribute("price"));
     _defence = atoi(data->Attribute("defence"));
     _quality = atoi(data->Attribute("quality"));
     return true;
}
bool ItemLoader::loadArmor (TiXmlElement* data)
{
     if(data->Attribute("defence") == NULL || data->Attribute("price") == NULL ||
        data->Attribute("quality") == NULL || data->Attribute("power") == NULL  )
       {
         LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
         return false;
       }
       _attack = _speed;
       _power = atoi(data->Attribute("power"));
       _defence = atoi(data->Attribute("defence"));
       _quality = atoi(data->Attribute("quality"));
       _price = atoi(data->Attribute("price"));
       return true;
}
bool ItemLoader::loadPants (TiXmlElement* data)
{
    if(data->Attribute("power") == NULL || data->Attribute("price") == NULL || data->Attribute("defence") == NULL
     || data->Attribute("quality") == NULL)
      {
          LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
         return false;
      }
      _attack = _defence = _speed = _quality = 0;
      _speed = 0;
      _power = atoi(data->Attribute("power"));
      _price = atoi(data->Attribute("price"));
      _defence = atoi(data->Attribute("defence"));
      _quality = atoi(data->Attribute("quality"));
      return true;
}
bool ItemLoader::loadHelmet(TiXmlElement* data)
{
     if(data->Attribute("power") == NULL || data->Attribute("price") == NULL || data->Attribute("defence") == NULL|| data->Attribute("quality") == NULL)
     {
         LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
          return false;
     }
     _attack = _defence = _speed = _quality = 0;
     _speed = 0;
     _power = atoi(data->Attribute("power"));
     _price = atoi(data->Attribute("price"));
     _defence = atoi(data->Attribute("defence"));
     _quality = atoi(data->Attribute("quality"));
     return true;
}
bool ItemLoader::loadWeapon(TiXmlElement* data)
{
    if(data->Attribute("attack")  == NULL || data->Attribute("speed") == NULL ||
       data->Attribute("defence") == NULL || data->Attribute("power") == NULL ||
       data->Attribute("quality") == NULL || data->Attribute("price") == NULL)
      {
          LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
        return false;
      }
      _attack = atoi(data->Attribute("attack"));
      _speed = atoi(data->Attribute("speed"));
      _power = atof(data->Attribute("power"));
      _quality = atoi(data->Attribute("quality"));
      _price = atoi(data->Attribute("price"));
      _defence = atoi(data->Attribute("defence"));
      return true;
}
bool ItemLoader::loadShield(TiXmlElement* data)
{
    if(data->Attribute("power") == NULL || data->Attribute("price") == NULL || data->Attribute("defence") == NULL|| data->Attribute("quality") == NULL)
    {
        LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
         return false;
    }
    _attack = _defence = _speed = _quality = 0;
    _speed = 0;
    _power = atoi(data->Attribute("power"));
    _price = atoi(data->Attribute("price"));
    _defence = atoi(data->Attribute("defence"));
    _quality = atoi(data->Attribute("quality"));
    return true;
}
bool ItemLoader::loadAmulet(TiXmlElement* data)
{
     if(data->Attribute("power") == NULL || data->Attribute("price") == NULL || data->Attribute("defence") == NULL || data->Attribute("quality") == NULL)
     {
         LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
          return false;
     }
     _attack = _defence = _speed = _quality = 0;
     _speed = 0;
     _power = atoi(data->Attribute("power"));
     _price = atoi(data->Attribute("price"));
     _defence = atoi(data->Attribute("defence"));
     _quality = atoi(data->Attribute("quality"));
     return true;
}
