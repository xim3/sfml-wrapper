#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "tinyxml/tinyxml.h"
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#include "AnimatedSprite/AnimatedTex.cpp"
#include "Person/Person.cpp"
#include "Person/Player.cpp"
#include "NpcManager/NpcManager.cpp"
#include "MapSystem/ItemManager.cpp"

#include "MapSystem/StaticTiledMap.cpp"
#include "DialogSystem/Dialog.h"
#include "DialogSystem/Button.h"
#include "DialogSystem/Menu.h"
#include "DialogSystem/EquipmentItem.h"
#include "DialogSystem/Equipment.h"
int main()
{
	sf::Vector2i screenDimensions(800,800);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "mapka");
    sf::View cam=window.getDefaultView();
    el::Configurations conf("logger.conf");
    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);
    window.setFramerateLimit(60);
    sf::Clock frameClock;
    sf::Clock i_clock;
    sf::Clock playerclock;
    ItemManager imgr;
    NpcManager nmgr;
    TileMap map;    
    Player gamer;
    gamer.setTimerHandle(&playerclock);
    gamer.load("player.xml");
    map.setItemManagerHandle(&imgr);
    map.setNPCManagerHandle(&nmgr);
    map.setTimeHandle(&i_clock);
	map.loadMap("r.tmx");
	imgr.loadItems("items.xml");
	
	gamer.setPosition(10,10);
	sf::Vector2f aPos;
	sf::Vector2u pzz;
	sf::Int32 itemId = 0;
	unsigned int iid = 0;
	bool isit,sol,por;
	sf::Vector2f mov1(0,0);
	gamer.setPositionHandle(&mov1);
	sf::Vector2f x;
    while (window.isOpen())
    {
    sf::Vector2f movement(0.f, 0.f);
    mov1 = sf::Vector2f(0.f,0.f);
    sf::Event event;
    while(window.pollEvent(event)){
		  if(event.type == sf::Event::Closed)
           window.close();
				if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right )
								++iid;
			if(event.mouseButton.button == sf::Mouse::Left && iid > 0)
				--iid;
		}
	}
    pzz = gamer.getPosition();
    aPos = gamer.getPosition1();
 
	isit = map.isItem(pzz,itemId);
	sol = map.isSolidTile(pzz);
	por = map.isPortal(pzz);
	printf("X:%f Y:%f X:%i Y:%i, solid:%i item:%i itemId:%i playerit:%i items:%i iid:%i portal:%i near:%i \n"
	,aPos.x,aPos.y,pzz.x,pzz.y, sol, 
	isit, itemId, imgr.playerItemCount(), map.itemsOnMapCount(),iid,por, nmgr.nearNPC(pzz));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
	  	if(isit == false && sol == false)
	    {
			if(map.dropItem(iid))
				printf("Dropped!\n");
			else 
				printf("No Way\n");
		}
		else
			printf("Stoisz na itemie albo solidnej kratce\n");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if(map.pickItem(pzz))
			printf("Picked!\n");				
		else 
			printf("No Item\n");				
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		map.printItems1();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		imgr.printItems();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
	if(iid < imgr.playerItemCount())
			iid++;
	else iid = 0;
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
    {
	 if(iid != 0)
			iid--;
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) )
		return 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) )
	{
		if(por == true)
		{
			sf::Vector2f x1 = map.reload(pzz);
			gamer.setPosition((unsigned int)(x1.x),(unsigned int)(x1.y));
		}	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map.isSolidTile(sf::Vector2u(pzz.x,pzz.y-1)) == false)
           gamer.walkUp();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map.isSolidTile(sf::Vector2u(pzz.x,pzz.y+1)) == false)
           gamer.walkDown();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && map.isSolidTile(sf::Vector2u(pzz.x-1,pzz.y)) == false)
           gamer.walkLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && map.isSolidTile(sf::Vector2u(pzz.x+1,pzz.y)) == false)
           gamer.walkRight();
    if(itemId != -1)
    {
		ItemData idat = imgr.getData(map.getGID(itemId));
		printf("Standing on item desc:%s info:%s\n",idat.description.c_str(),idat.name.c_str());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		ItemData idat = imgr.getData(imgr.getGID(iid));
		printf("Item %s %s\n", idat.description.c_str(),idat.name.c_str());
	}
    map.refreshAnimations();
	imgr.update(pzz);
    window.setView(cam);
    gamer.update();
    window.clear();
    window.draw(map);
    window.draw(gamer);
    window.display();
    }
    return 0;
}
