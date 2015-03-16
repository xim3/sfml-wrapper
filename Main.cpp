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
#include "DialogSystem/Window.hpp"
#include "DialogSystem/GridWindow.hpp"
#include "DialogSystem/EquipWindow.hpp"
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
	sf::Texture t;
	(t.loadFromFile("eq.png"));
    sf::Texture l;l.loadFromFile("tile.png");
    sf::Font fon;
    fon.loadFromFile("DialogSystem/arialuni.ttf");
    ItemManager imgr;
    EquipFormat eqFormater;
    EquipmentWindow eqw(&l,&fon,sf::Vector2f(30,300),5,5,imgr,eqFormater,sf::Color(30,30,30,200), sf::Color(30,50,30,200));
    imgr.setCapacity(eqw.getCapacity());
    NpcManager nmgr;
    TileMap map(imgr, nmgr);
    Player gamer;
    Entity a;
    a.load("npc.xml");
    gamer.load("player.xml");
	map.loadMap("r.tmx");
	imgr.loadItems("items.xml");

	gamer.setPosition(10,10);
	a.setPosition(3,10);
	sf::Vector2f aPos;
	sf::Vector2u pzz;
	sf::Int32 itemId = 0;
	unsigned int iid = 0;
	bool isit,sol,por;
	sf::Vector2f x;
	sf::Vector2i mysza;
	float f = 0;
    while (window.isOpen())
    {
    sf::Event event;
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
	isit = map.isItem(pzz,itemId);
    sf::Vector2f pzz1 = gamer.getPositionFloat();
	sol = map.isSolidTile(pzz1);
	por = map.isPortal(pzz);
	nmgr.nearNPC(pzz);
	//printf("intersect:%i x:%i y:%i x1:%i y1:%i under:%i\n",
    //    gr.intersects(mysza), mysza.x,mysza.y, eqw.underSquare(mysza).x, eqw.underSquare(mysza).y, eqw.getGID(mysza));
	//printf("X:%f Y:%f, solid:%i item:%i itemId:%i playerit:%i items:%i iid:%i portal:%i near:%i \n",pzz1.x,pzz1.y, sol,isit, itemId, imgr.playerItemCount(), map.itemsOnMapCount(),iid,por, nmgr.nearNPC(pzz));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        eqw.update(imgr.getItemsVector());
	  	if(isit == false && sol == false)
	    {
			if(map.dropItem(iid)){
				printf("Dropped!\n");
				eqw.refresh(0);
			}
			else
				printf("No Way\n");
		}
		else
			printf("Stoisz na itemie albo solidnej kratce\n");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
        eqw.update(imgr.getItemsVector());
		if(map.pickItem(pzz)){
			printf("Picked!\n");
		}
		else
			printf("No Item\n");
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
	    eqw.move(sf::Vector2f(eqw.getPosition().x-1,eqw.getPosition().y));
		map.printItems1();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
	    eqw.move(sf::Vector2f(eqw.getPosition().x+1,eqw.getPosition().y));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true && map.isSolidTile(gamer.getPositionFixed(D_UP, 0.1)) == false)
           gamer.move("up");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ==true && map.isSolidTile(gamer.getPositionFixed(D_DOWN, 0.1)) == false){
            gamer.move("down");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)==true && map.isSolidTile(gamer.getPositionFixed(D_LEFT, 0.1)) == false)
           gamer.move("left");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ==true&& map.isSolidTile(gamer.getPositionFixed(D_RIGHT,0.1))== false)
           gamer.move("right");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	    gamer.action("insane");
    a.update();
    map.refreshAnimations();
	imgr.update(pzz);
    window.setView(cam);

    eqw.controlCloud(mysza);
    gamer.update();
    window.clear();
    window.draw(map);
    window.draw(a);
       window.draw(gamer);
    window.draw(eqw);

    //window.draw(win);

    window.display();
    }
    return 0;
}
