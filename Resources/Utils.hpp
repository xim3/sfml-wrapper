#pragma once
#include <SFML/Graphics.hpp>
#include "../MapSystem/Item.h"
class TiXmlElement;
enum ATYPE
{
   NPC_ONLY_TALK, NPC_GIVE_ITEM, NPC_GET_ITEM, NPC_GIVE_QUEST,
   NPC_VALID_QUEST, NPC_FIGHT, NPC_TRADE, NPC_RESERVED_FIELD_0, NPC_RESERVED_FIELD_1,
   PLAYER_RESPONSE, ACTION_NOT_VALID=64
};
struct HelpInfo
{
	HelpInfo()
	{}
	HelpInfo(std::string _cond)
	: helpstring(_cond)
	{}
	HelpInfo(const HelpInfo& r)
	{
		this->additdata = r.additdata;
		this->helpstring = r.helpstring;
	}
	HelpInfo& operator=(const HelpInfo& rhs)
	{
		this->additdata = rhs.additdata;
		this->helpstring = rhs.helpstring;
		return *this;
	}
	std::vector<int> additdata;
	std::string 	 helpstring;
};
struct Action
{
	Action()
	: type_action(NPC_ONLY_TALK)
	, ad_info(){}
	Action(std::wstring t, ATYPE at, HelpInfo hi){
		text = t;
		type_action = at;
		ad_info = hi;
	}
	Action(const Action& r){
		this->type_action = r.type_action;
		this->ad_info = r.ad_info;
		this->text = r.text;
	}
	void clean(){
	    type_action = NPC_ONLY_TALK;
	    ad_info.helpstring.clear();
	    ad_info.additdata.clear();
	}
	ATYPE 		 type_action;
	HelpInfo 	 ad_info;
	std::wstring text;
};
class IDataFormat
{
public:
    IDataFormat(){};
    virtual void format(const ItemData, const sf::Vector2f&,unsigned int&, sf::Font&, std::vector<sf::Text>&) = 0;
    virtual ~IDataFormat(){};
};
class IDataRead
{
public:
    IDataRead(){};
    virtual void read(TiXmlElement*) = 0;
    virtual Action get() = 0;
    virtual ~IDataRead(){};
};
struct TextData
{
    sf::Text text;
    int      height;
};
template<class T>
bool xyCompare(const T& first, const sf::Vector2u &vct)
{
    if(first.x == vct.x && first.y == vct.y)
        return true;
    else
        return false;
}
template<class T, class T1>
bool xyCompare(const T& first, const T1& second)
{
    if(first.x == second.x && first.y == second.y)
        return true;
    else
        return false;
}
template<class T>
bool xyCompareUnsigned(const T& first, const sf::Vector2i &vct)
{
    sf::Vector2i buf(first.x,first.y);
    if(buf.x == vct.x && buf.y == vct.y)
        return true;
    else
        return false;
}
template<class T>
bool xyCompareFloat(const T& first, const sf::Vector2f vct)
{
    if(static_cast<unsigned int>(vct.x) == first.x && static_cast<unsigned int>(vct.y) == first.y)
        return true;
    else
        return false;
}
template<class T>
bool _near(const T& obj, const sf::Vector2u &vct)
{
    if( (obj.x == vct.x 	&& obj.y == vct.y    ) ||
        (obj.x == vct.x     && obj.y == vct.y - 1) ||
        (obj.x == vct.x - 1 && obj.y == vct.y - 1) ||
        (obj.x == vct.x - 1 && obj.y == vct.y    ) ||
        (obj.x == vct.x - 1 && obj.y == vct.y + 1) ||
        (obj.x == vct.x     && obj.y == vct.y + 1) ||
        (obj.x == vct.x + 1 && obj.y == vct.y - 1) ||
        (obj.x == vct.x + 1 && obj.y == vct.y    ) ||
        (obj.x == vct.x + 1 && obj.y == vct.y + 1)  )
        return true;
    else
        return false;
}
template<class T>
T wide_string(const std::string& s)
{
    T temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}
template<class T>
std::basic_string<sf::Uint32>to32UTF(T str)
{
    std::basic_string<sf::Uint32> utf32;
    sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(utf32));
    return utf32;
}
