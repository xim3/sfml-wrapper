#ifndef EQUIPMENTITEM_H
#define EQUIPMENTITEM_H
#include <SFML/Graphics.hpp>

class EquipmentItem
{
    public:
        EquipmentItem(sf::Texture &txt, std::string TEXT, int font_size, sf::Color font_color, sf::Vector2f box_size, sf::Color box_color, sf::Color outline_color, float thin_outline, sf::Font &font, uint8_t transparent);
        void setPosition(sf::Vector2f position, float margin_box, float text_margin_top, float text_margin_left);
        void showBox(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        bool click(sf::RenderWindow &window, sf::Event &event); //if mouse is on sprite return true, used to display box with parametres
        sf::Sprite getSprite();
    private:
        sf::Sprite sprite;
        sf::RectangleShape box; //display value of items and name
        sf::Text text; //text with item values - to create new line you should add '\n'

};

#endif // EQUIPMENTITEM_H
