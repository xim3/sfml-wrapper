#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "EquipmentItem.h"

class Equipment
{
    public:
        Equipment(sf::Texture &txt, sf::Vector2f position);

        void addItem(EquipmentItem new_item);
        void removeItem(int id);
        void draw(sf::RenderWindow &window);
        void loadTexture(const std::string name);
        void showBox(sf::RenderWindow &window, sf::Event &event); //dziala prawie jak metoda click z klasy EquipmentItem tylko ze na wielu elementach
    private:
        std::vector <EquipmentItem> items;
        sf::Sprite background; //background, it's can be for example: shop, player equipment, trading with npc
        sf::Texture itemsTex;

};

#endif // EQUIPMENT_H
