#include "EquipmentItem.h"

EquipmentItem::EquipmentItem(sf::Texture &txt, std::string TEXT, int font_size, sf::Color font_color, sf::Vector2f box_size,
sf::Color box_color, sf::Color outline_color, float thin_outline, sf::Font &font, uint8_t transparent){
	
    sprite.setTexture(txt);

    text.setString(TEXT);
    text.setCharacterSize(font_size);
    text.setColor(font_color);
    text.setFont(font);

    box.setSize(box_size);
    box_color.a = transparent;
    box.setFillColor(box_color);
    box.setOutlineThickness(thin_outline);
    box.setOutlineColor(outline_color);
}

void EquipmentItem::setPosition(sf::Vector2f position, float margin_box, float text_margin_top, float text_margin_left){
    sprite.setPosition(position);
    box.setPosition(sprite.getPosition().x + sprite.getTexture()->getSize().x + margin_box, sprite.getPosition().y); //long but it probably working good ;) - set box position based on item position
    text.setPosition(box.getPosition().x + text_margin_left, box.getPosition().y + text_margin_top); //set text margins
}

void EquipmentItem::showBox(sf::RenderWindow& window){
    window.draw(box);
    window.draw(text);
}

void EquipmentItem::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

bool EquipmentItem::onHoover(sf::RenderWindow& window, sf::Event& event){
    sf::Vector2f mouse_position(sf::Mouse::getPosition(window));
    if(sprite.getGlobalBounds().contains(mouse_position))
        return true;
    else
        return false;
}
void setTexture(){
}
sf::Sprite EquipmentItem::getSprite(){
    return sprite;
}
