#include "Equipment.h"

Equipment::Equipment(sf::Texture &txt, sf::Vector2f position)
{
    background.setTexture(txt);
    background.setPosition(position);
}

void Equipment::addItem(EquipmentItem new_item)
{
    items.push_back(new_item);
}

void Equipment::removeItem(int id)
{
    items.erase(items.begin() + id);
}

void Equipment::draw(sf::RenderWindow& window)
{
    window.draw(background);
    items[0].setPosition(background.getPosition(), 0, 0, 0);
    window.draw(items[0].getSprite());
    for(size_t x = 1; x < items.size(); x++)
    {
        items[x].setPosition(sf::Vector2f(background.getPosition().x + 1, background.getPosition().y + 1), 0, 0, 0); //TODO
        window.draw(items[x].getSprite());
    }
}

void Equipment::showBox(sf::RenderWindow& window, sf::Event& event)
{
    sf::Vector2f mouse_position(sf::Mouse::getPosition(window));
    for(size_t x = 0; x < items.size(); x++)
    {
        if(items[x].getSprite().getGlobalBounds().contains(mouse_position))
            items[x].showBox(window);
    }
}
void Equipment::loadTexture(const std::string name)
{
	if(itemsTex.loadFromFile(name) == false){
		
		return;
	}
}
