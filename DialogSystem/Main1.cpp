#include "DialogSystem/Dialog.h"
#include "DialogSystem/Button.h"
#include "DialogSystem/Menu.h"
#include "DialogSystem/EquipmentItem.h"
#include "DialogSystem/Window.hpp"
#include "Resources/easylogging++.h"
#include "DialogSystem/GridWindow.hpp"
INITIALIZE_EASYLOGGINGPP
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Title");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Texture item_;
    item_.loadFromFile("DialogSystem/t.png");
    sf::Font arial;
    arial.loadFromFile("DialogSystem/arial.ttf");
    EquipmentItem item(item_, "\tGod gun II\nAmmo: infinity (that's God)\nColor: pink",
     14, sf::Color::Black, sf::Vector2f(175, 200), sf::Color::Red, sf::Color::Black, 3, arial, 128);
    item.setPosition(sf::Vector2f(100, 250), 4, 7, 7);

    sf::Texture shop;
    shop.loadFromFile("DialogSystem/converted.png");
	sf::Texture tex;
	tex.loadFromFile("tile.png");
    GridWindow win(&shop,&tex,sf::Vector2f(400,300),4,5);
    win.append(0,0,1807);
	win.append(0,1,1806);
	win.append(1,3,500);
	win.append(3,3,1800);
	win.append(3,2,1799);
	win.append(2,3,1798);
	win.append(0,4,1800);
	float i=0;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		win.setPosition(win.getPosition().x+1,win.getPosition().y);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		win.setPosition(win.getPosition().x-1,win.getPosition().y);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		win.setPosition(win.getPosition().x,win.getPosition().y-1);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		win.setPosition(win.getPosition().x,win.getPosition().y+1);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		win.rotate(i+=0.01);
        window.clear(sf::Color::White);
		window.draw(win);	
        window.display();
    }

    return 0;
}

