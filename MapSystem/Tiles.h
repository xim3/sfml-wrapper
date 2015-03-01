#pragma once
struct SolidTile
{
	unsigned int x;
	unsigned int y;
	unsigned int gid;
	SolidTile(const sf::Uint32 _x, const sf::Uint32 _y, const sf::Uint32 _gid) 
	: x(_x)
	, y(_y)
	, gid(_gid)
	{
	};
};
struct BackgroundTile
{
	unsigned int x;
	unsigned int y;
	unsigned int gid;
	BackgroundTile(const sf::Uint32 _x, const sf::Uint32 _y, const sf::Uint32 _gid) 
	: x(_x)
	, y(_y)
	, gid(_gid)
	{
	};
};
struct PortalTile
{
	unsigned int x;
	unsigned int y;
	unsigned int gid;
	sf::Vector2u spawn;
	std::string file;
	bool first_load;
	PortalTile(unsigned int _x, unsigned int _y, unsigned int _gid, std::string &_file,sf::Vector2u _spawn)
	: x(_x)
	, y(_y)
	, gid(_gid)
	, spawn(_spawn)
	{
		file = _file;
	};
};
struct AnimatedTile
{
	unsigned int x;
	unsigned int y;
	unsigned int gid;
	unsigned int steps;
	sf::Time	 speed;
	Animation anim;
	AnimatedTex txt;
	AnimatedTile(unsigned int _x,unsigned int _y,double _speed, Animation _an) 
	: x(_x)
	, y(_y)
	, speed(sf::seconds(_speed))
	, anim(_an)
	{
		txt.setPosition(sf::Vector2f((unsigned int)(x*32),(unsigned int)(y*32)));
		txt.setFrameTime(speed);
	} 
};
