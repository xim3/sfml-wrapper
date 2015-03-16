#pragma once
#include "../AnimatedSprite/AnimatedTex.hpp"
//
/**
 * \brief struktura bazowa kafla
 **/
struct Tile
{
	public:
	    Tile(unsigned int _x, unsigned int _y, unsigned int _gid)
	    : x(_x)
	    , y(_y)
	    , gid(_gid)
	    {
		}
		bool operator==(const Tile& rhs){
		    if ((this->x) == (rhs.x) && (this->y) == (rhs.y))
                return true;
            else return false;
		}
		unsigned int x;
		unsigned int y;
		unsigned int gid;
};
//
/**
 * \brief struktura solidnego kafla
 **/
struct SolidTile : Tile
{
	SolidTile(const sf::Uint32 _x, const sf::Uint32 _y, const sf::Uint32 _gid)
	: Tile(_x,_y,_gid)
	{
	};
};
//
/**
 * \brief struktura dekoracyjnego kafla
 **/
struct BackgroundTile : Tile
{
	BackgroundTile(const sf::Uint32 _x, const sf::Uint32 _y, const sf::Uint32 _gid)
    : Tile(_x,_y,_gid)
	{
	};
};
//
/**
 * \brief struktura portalu
 * \details rozszerza kafel o współrzędne spawnu, nazwe mapy, i informacje o tym czy została załadowana po raz pierwszy
 **/
struct PortalTile : Tile
{
	sf::Vector2u spawn;
	std::string file;
	bool first_load;
	PortalTile(unsigned int _x, unsigned int _y, unsigned int _gid, std::string &_file,sf::Vector2u _spawn)
    : Tile(_x,_y,_gid)
	, spawn(_spawn)
	{
		file = _file;
	};
};
//
/**
 * \brief struktura animowanego kafla
 * \details rozszerza kafel o możliwość animacji
 **/
struct AnimatedTile : Tile
{
	unsigned int steps;
	sf::Time	 speed;
	Animation anim;
	AnimatedTex txt;
	AnimatedTile(unsigned int _x,unsigned int _y,double _speed, Animation _an, unsigned int t_w,unsigned int t_h)
	: Tile(_x,_y,0)
	, speed(sf::seconds(_speed))
	, anim(_an)
	{
		txt.setPosition(sf::Vector2f((unsigned int)(x*t_w),(unsigned int)(y*t_h)));
		txt.setFrameTime(speed);
	}
};
//
