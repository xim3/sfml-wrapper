#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Resources/tinyxml/tinyxml.h"
#include "Resources/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
//
#include "AnimatedSprite/AnimatedTex.hpp"
#include "MapSystem/ItemManager.hpp"
#include "MapSystem/StaticTiledMap.hpp"
#include "Person/Entity.hpp"
#include "Person/Player.hpp"
#include "NpcManager/NpcManager.hpp"
#include "DialogSystem/EquipWindow.hpp"
#include "DialogSystem/TextWindow.hpp"
#include "DialogSystem/DataFormat.hpp"
#include "NpcManager/DataReader.hpp"
#include "DialogSystem/PlayerDataWindow.hpp"
#include "DialogSystem/PopupMenu.hpp"
#include "MapSystem/ItemLoader.hpp"
#include "Person/MemoryBridge.hpp"
//

int main()
{
	sf::Vector2u screenDimensions(800,800);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "mapka");
    sf::View cam=window.getDefaultView();
    el::Configurations conf("logger.conf");
    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);
    window.setFramerateLimit(60);
    sf::Texture l;l.loadFromFile("tile.png");
    sf::Font fon;
    ItemLoader iload;
    fon.loadFromFile("DialogSystem/arialuni.ttf");
    ItemManager imgr(iload);

    DataRead dataRead;
    MemoryManager mem;
    EquipFormat eqFormater(&mem);
    sf::Vector2i mysza;
    sf::Event event;
    imgr.setCapacity(5*5);
    TextWindow text(sf::Vector2f(0,800-200), sf::Vector2f(800,200),mysza,&fon,13);
    	sf::Vector2u pzz;
    NpcManager nmgr(dataRead, text, pzz, mysza);
    TileMap map(imgr, nmgr);
    Player gamer;
    Entity a;
    a.load("npc.xml");
    gamer.load("player.xml");
	map.loadMap("r.tmx");
    nmgr.loadDialogs("dialogs.xml");
    gamer.addStat("level", 30);
    gamer.addStat("exp", 1000);
    gamer.addStat("strength", 100);
    gamer.addStat("agility", 10);
    gamer.addStat("vital",5);
    gamer.addStat("energy",4);
    gamer.addStat("wisdom", 9);
    gamer.addStat("charisma", 30);
    gamer.addStat("freepoints", 300);
    gamer.addStat("weapon",0);
    gamer.addStat("pants", 0);
    gamer.addStat("armor", 0);
    gamer.addStat("boots", 0);
    gamer.addStat("helmet",0);
    gamer.addStat("shield",0);
    mem.set(gamer.getFullStats());

	imgr.loadItems("items.xml");
    nmgr.setPlayerStats(gamer.getFullStats());
	gamer.setPosition(10,10);
	a.setPosition(3,10);
	text.setVisible(false);
	sf::Vector2f aPos;
	unsigned int iid = 0;
	bool sol,por;
	sf::Vector2f x;
	DataWindow dw(sf::Vector2f(300,300), pzz, mysza, &fon, &l, imgr, map ,eqFormater, 12);
	dw.setMemoryManager(&mem);
    while (window.isOpen())
    {
    while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right )
							++iid;
				if(event.mouseButton.button == sf::Mouse::Left && iid > 0)
							--iid;
			}
            mysza = sf::Mouse::getPosition(window);
	}
    pzz = gamer.getPosition();
    sf::Vector2f pzz1 = gamer.getPositionFloat();
	sol = map.isSolidTile(pzz1);
	por = map.isPortal(pzz);
	nmgr.nearNPC(pzz);    //printf("under butt:%i\n",men.underButton(sf::Vector2f(mysza.x, mysza.y)));
    //text.intersects(mysza), mysza.x,mysza.y, text.selectAnwser());
	//printf("X:%f Y:%f, solid:%i item:%i itemId:%i playerit:%i items:%i iid:%i portal:%i near:%i \n",pzz1.x,pzz1.y, sol,isit, itemId, imgr.playerItemCount(), map.itemsOnMapCount(),iid,por, nmgr.nearNPC(pzz));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
	  	if(sol == false)
	    {
			if(map.dropItem(iid))
			{
				printf("Dropped!\n");
				dw.equipRefresh();
			}
			else
				printf("No Way\n");
		}
		else
			printf("Stoisz na itemie albo solidnej kratce\n");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if(map.pickItem(pzz)){
			printf("Picked!\n");
		}
		else
			printf("No Item\n");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
		imgr.printItems();

	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true && map.isSolidTile(gamer.getPositionFixed(D_UP, 0.3)) == false)
           gamer.move("up");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ==true && map.isSolidTile(gamer.getPositionFixed(D_DOWN, 0.1)) == false){
            gamer.move("down");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)==true && map.isSolidTile(gamer.getPositionFixed(D_LEFT, 0.1)) == false)
           gamer.move("left");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ==true&& map.isSolidTile(gamer.getPositionFixed(D_RIGHT,0.1))== false)
           gamer.move("right");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	    gamer.action("insane");

    a.update();
    nmgr.update();
    map.refreshAnimations();
	imgr.update(pzz);
    window.setView(cam);
    gamer.update();
    window.clear();
    window.draw(map);
    if(text.isVisible())
        window.draw(text);
    dw.update();
    window.draw(a);
    window.draw(gamer);
    window.draw(dw);
    window.display();
    }
    return 0;
}
