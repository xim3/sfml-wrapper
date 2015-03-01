#pragma once
enum ITEM_TYPE{WEAPON, ARMOR, RECOVERY};
struct ItemData
{
	ITEM_TYPE type;
	std::string description;
	std::string name;
	unsigned int attack;
	unsigned int defence;
	unsigned int quality;
	unsigned int price;
	unsigned int power;
	double 		 speed;
	unsigned int gid;
	ItemData(ITEM_TYPE _type,std::string _desc,std::string _nam,
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
			 , speed(_spe)
			 , gid(_gid)
			 {
			 };
	ItemData(const ItemData& rhs)
	: type(rhs.type)
	, description(rhs.description)
	, name(rhs.name)
	, attack(rhs.attack)
	, defence(rhs.defence)
	, quality(rhs.quality)
	, price(rhs.price)
	, power(rhs.power)
	, speed(rhs.speed)
	, gid(rhs.gid)
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
		return *this;
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
	bool	     valid;
	Item()
	    : x(0)
	    , y(0)
	    , gid(0)
	    , id(0)
	    , valid(0)
	    {
		};
	Item(unsigned int _x,unsigned int _y,unsigned int _gid,unsigned int _id, bool _v)
		: x(_x)
		, y(_y)
		, gid(_gid)
		, id(_id)
		, valid(_v)
		{
		};
	Item(const Item& tmp) 
	    : x(tmp.x)
	    , y(tmp.y)
	    , gid(tmp.gid)
	    , id(tmp.id)
	    , valid(tmp.valid)
	    {
	    };
	Item& operator=(const Item& rhs)
	{	
		this->x = rhs.x;
		this->y = rhs.y;
		this->gid = rhs.gid;
		this->id = rhs.id;
		this->valid = rhs.valid;
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
