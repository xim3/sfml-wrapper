#include "DialogSystem/Dialog.h"
#include "DialogSystem/Button.h"
#include "DialogSystem/Menu.h"
#include "DialogSystem/EquipmentItem.h"
#include "DialogSystem/Equipment.h"
#include "Resources/easylogging++.h"
INITIALIZE_EASYLOGGINGPP
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
    window.setFramerateLimit(60);

    sf::Event event;


    sf::Texture item_;
    item_.loadFromFile("DialogSystem/t.png");

    sf::Font arial;
    arial.loadFromFile("DialogSystem/arial.ttf");

	// Wczytujemy dane z 1 tileseta, `item_` ustaw tylko raz
	// podaj tylko GID, masz tu funkcje
	//  void appendTile(const unsigned int x,const unsigned int y, const unsigned int GID,TILETYPE bgLayer)
	// 	sf::Int32 tu = GID % (m_tileset.getSize().x / tile_width);
	//  sf::Int32 tv = GID / (m_tileset.getSize().x / tile_height);
	//  vector itemów w klasie Equipment.push_back(sf::IntRect(tu * tile_width, tv * tile_height,tile_width,tile_height));
    EquipmentItem item(item_, "\tGod gun II\nAmmo: infinity (that's God)\nColor: pink",
     14, sf::Color::Black, sf::Vector2f(175, 200), sf::Color::Red, sf::Color::Black, 3, arial, 128);
    item.setPosition(sf::Vector2f(100, 250), 4, 7, 7);

    sf::Texture shop;
    shop.loadFromFile("DialogSystem/converted.png");

	
    Equipment eq("DialogSystem/converted.png","tile.png", &window,4,4,sf::Vector2f(300, 100),32,32);
    eq.addItem(item);
    eq.addItem(item);
    eq.addItem(item);
	eq.appendItem(1,1,1806);
	//eq.setPosition(sf::Vector2f(10,10));

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        //window.clear(sf::Color::White);
       // if(item.onHoover(window, event))
        //    item.showBox(window);
        //item.draw(window);

        window.draw(eq);
        //eq.showBox(window, event);
        window.display();
    }

    return 0;
}

