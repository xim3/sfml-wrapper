#include "Dialog.h"
#include "Button.h"
#include "Menu.h"
#include "EquipmentItem.h"
#include "Equipment.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
    window.setFramerateLimit(60);

    sf::Event event;


    sf::Texture item_;
    item_.loadFromFile("t.png");

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

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
    shop.loadFromFile("converted.png");

    Equipment eq(shop, sf::Vector2f(300, 100));
    eq.addItem(item);
    eq.addItem(item);
    eq.addItem(item);



    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        if(item.click(window, event))
            item.showBox(window);
        item.draw(window);
        eq.draw(window);
        eq.showBox(window, event);
        window.display();
    }

    return 0;
}

