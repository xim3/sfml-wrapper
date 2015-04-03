#pragma once
#include <string>
#include <vector>
#include <utility>
enum ITEM_TYPE{WEAPON = 0, HELMET = 1, ARMOR = 2, PANTS = 3, BOOTS = 4, SHIELD = 5, AMULET = 6, POTION = 7, NOT_WEAR = 8};
class ItemData
{
public:
	ITEM_TYPE    type;
	std::wstring description;
	std::wstring name;
	unsigned int attack;
	unsigned int defence;
	unsigned int quality;
	unsigned int price;
	unsigned int power;
    unsigned int gid;
	double 		 speed;
	std::vector<std::pair<std::string, int>>  addit_data;
	std::vector<std::pair<std::pair<std::string, std::string>, std::string>> conditions;
	std::vector<std::pair<std::pair<std::string, std::string>, std::string>> properties;
	ItemData
	(ITEM_TYPE _type,std::wstring _desc,std::wstring _nam,
	 unsigned int _att, unsigned int _def, unsigned int _qua,
	 unsigned int _pri, unsigned int _pow, unsigned int _spe,
	 unsigned int _gid)
	 : type(_type)
	 , description(_desc)
	 , name(_nam)
	 , attack(_att)
	 , defence(_def)
	 , quality(_qua)
	 , price(_pri)
	 , power(_pow)
	 , gid(_gid)
	 , speed(_spe)
	 {
	 };
    ItemData()
     : type(WEAPON)
	 , description(L"undefined")
	 , name(L"undefined")
	 , attack(0)
	 , defence(0)
	 , quality(0)
	 , price(0)
	 , power(0)
	 , gid(0)
     , speed(0)
    {

    }
	ItemData(const ItemData& rhs)
	: type(rhs.type)
	, description(rhs.description)
	, name(rhs.name)
	, attack(rhs.attack)
	, defence(rhs.defence)
	, quality(rhs.quality)
	, price(rhs.price)
	, power(rhs.power)
	, gid(rhs.gid)
	, speed(rhs.speed)
	, addit_data(rhs.addit_data)
	, conditions(rhs.conditions)
	, properties(rhs.properties)
	{
	}
	ItemData& operator=(const ItemData& rhs)
	{
		this->type 		  = rhs.type;
		this->description = rhs.description;
		this->name 		  = rhs.name;
		this->attack 	  = rhs.attack;
		this->defence 	  = rhs.defence;
		this->quality 	  = rhs.quality;
		this->price 	  = rhs.price;
		this->power 	  = rhs.power;
		this->speed 	  = rhs.speed;
		this->gid 	      = rhs.gid;
		this->addit_data  = rhs.addit_data;
		this->conditions  = rhs.conditions;
		this->properties  = rhs.properties;
		return *this;
	}
	void setConditions(std::vector<std::pair<std::pair<std::string, std::string>, std::string>> c)
	{
	    conditions = c;
	}
	void setProperties(std::vector<std::pair<std::pair<std::string, std::string>, std::string>> p)
	{
	    properties = p;
	}
	bool operator==(const ItemData& rhs) const
	{
		if(this->gid == rhs.gid)
			return true;
		else
			return false;
	}
};
//
struct Item
{
	unsigned int x;
	unsigned int y;
	unsigned int gid;
	int  		 id;
	Item()
    : x(0)
	, y(0)
	, gid(0)
	, id(0)
	{
	};
	Item(unsigned int _x,unsigned int _y,unsigned int _gid,unsigned int _id)
	: x(_x)
	, y(_y)
	, gid(_gid)
	, id(_id)
	{
	};
	Item(const Item& tmp)
	: x(tmp.x)
	, y(tmp.y)
	, gid(tmp.gid)
	, id(tmp.id)
	{
	};
	Item& operator=(const Item& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->gid = rhs.gid;
		this->id = rhs.id;
		return *this;
	}
	bool operator==(const Item& rhs) const
	{
		if(this->id == rhs.id)
			return true;
		else
			return false;
	}
};
