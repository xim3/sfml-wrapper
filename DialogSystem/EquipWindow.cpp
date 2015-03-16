#include "EquipWindow.hpp"
#include "../MapSystem/Item.h"
#include <string>
#include <locale>
EquipmentWindow::EquipmentWindow
(sf::Texture* _tiles,sf::Font* _text,
 sf::Vector2f _pos,unsigned int w_tiles,unsigned int h_tiles
  ,const ItemManager& imgr, IDataFormat& _formater,sf::Color _coll,sf::Color _colf,unsigned int w_tile ,unsigned int h_tile  )
: GridWindow(_tiles,_pos,w_tiles,h_tiles,w_tile,h_tile,_coll,_colf)
, cloud_border(1)
, _imgr(imgr)
, formatter(_formater)
, cloud(sf::Vector2f(323,200))
, font(*_text)
{
    cloud.setPosition(_pos);
    cloud.setFillColor(sf::Color(50,50,50,200));
    cloud.setOutlineThickness(cloud_border);
    cloud.setOutlineColor(sf::Color::Blue);
}
void EquipmentWindow::setBorderThick(unsigned int thick){
    cloud_border = thick;
    cloud.setOutlineThickness(cloud_border);
}
void EquipmentWindow::controlCloud(sf::Vector2i vct){
    unsigned int gid = getGID(vct);
    if(gid){
        descriptions.clear();
        formatter.format(_imgr.getData(gid), cloud.getPosition(),cloud_border,font,descriptions);
        hoover = true;
        cloud.setPosition(sf::Vector2f(vct.x+15, vct.y));
        return;
    }
    hoover = false;
}
void EquipmentWindow::setCloudSize(sf::Vector2f xxxsize){
    cloud.setSize(xxxsize);
}
void EquipmentWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(_backgrd);
	grid.draw(target,states);
	if(hoover)
	{
        target.draw(cloud);
        for(auto cloud_text : descriptions)
            target.draw(cloud_text);
	}
}
std::size_t EquipmentWindow::getCapacity() const{
    return (grid.getSize().x*grid.getSize().y);
}
