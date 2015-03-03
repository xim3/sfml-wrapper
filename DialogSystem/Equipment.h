#pragma once
#include "EquipmentItem.h"
#include <SFML/Graphics.hpp>

class Equipment : public sf::Drawable, public sf::Transformable
{
    public:
        Equipment(std::string,std::string,sf::RenderWindow*,int,int,
        sf::Vector2f position, int tile_width , int tile_height );
        void addItem(EquipmentItem new_item);
        void removeItem(int id);
        void draw(sf::RenderTarget &, sf::RenderStates) const;
        void loadTextureBg(const std::string);
        void loadTextureItems(const std::string);
        void appendItem(unsigned int,unsigned int,unsigned int);
        void showBox() const; 
        void setPosition(sf::Vector2f);
    private:
        std::vector <EquipmentItem> items;
        sf::Sprite background; 
        sf::Texture _bg1;
        sf::Texture _it1;
        sf::RenderWindow* window;
        sf::VertexArray item_grid;
        int width_in_tiles;
        int height_in_tiles;
        int tile_width;
        int tile_height;

};

