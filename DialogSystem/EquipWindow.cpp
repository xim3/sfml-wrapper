#include "EquipWindow.hpp"
#include "../MapSystem/Item.h"
#include <string>
#include <locale>
#include <utility>
EquipmentWindow::EquipmentWindow
(sf::Texture* _tiles,sf::Font* _text, sf::Vector2f _pos,
 unsigned int w_tiles,unsigned int h_tiles,bool custom, const ItemManager& imgr,
 IDataFormat& _formater,sf::Color _coll,sf::Color _colf,unsigned int w_tile ,unsigned int h_tile
)
: GridWindow(_tiles,_pos,w_tiles,h_tiles,w_tile,h_tile,_coll,_colf)
, equipment(4,4,32,32, _tiles, _pos)
, cloud_border(1)
, _imgr(imgr)
, formatter(_formater)
, cloud(sf::Vector2f(330,320))
, font(*_text)
, menu(_text, sf::Vector2f(0,0), 12)
, menu1(_text, sf::Vector2f(0,0), 12)
{

    setVisible(true);
    cloud.setPosition(_pos);
    cloud.setFillColor(sf::Color::Black);
    cloud.setOutlineThickness(cloud_border);
    cloud.setOutlineColor(sf::Color::White);

    equipment.setPosition(_pos.x + w_tiles*w_tile + 60 ,_pos.y);

    equipment.cleanBg();
    equipment.resizeBg();
    equipment.setBgTiles();

    menu.addChoice(L"Załóż/Użyj"  );
	menu.addChoice(L"Wyrzuć" );
	menu.addChoice(L"Zniszcz");
	menu.addChoice(L"Zamknij" );

	menu1.addChoice(L"Zdejmij");
	menu1.addChoice(L"Zamknij");
}
std::pair<int,int> EquipmentWindow::selectedItem(sf::Vector2i& vct)
{
    if(visible)
    {
        static int lastID;
        int ID = getID(vct);
        int selectedOpt = menu.selectedOption(vct);
        menu.refresh(vct);
        if(selectedOpt != -1)
            return std::pair<int,int>(selectedOpt, lastID);
        if(ID && buttonHold(150))
        {
            lastID = ID;
            menu.setVisible(true);
            menu.setPosition(sf::Vector2f(vct.x,vct.y));
            return std::pair<int, int>(-1,-1);
        }
        else return std::pair<int, int>(-1,-1);
    }
    else return std::pair<int, int>(-1, -1);
}
std::pair<int,int> EquipmentWindow::getSelectedEq(sf::Vector2i& vct)
{
    static int lastID, lastPart;
    int ID = equipment.getID(vct);
    int selectedOpt = menu1.selectedOption(vct);
    int part = equipment.underPart(vct);
    menu1.refresh(vct);
    if(selectedOpt == 0)
       return std::pair<int,int>(lastPart, lastID);
    if(ID && buttonHold(150))
    {
        lastID   = ID;
        lastPart = part;
        menu1.setVisible(true);
        menu1.setPosition(sf::Vector2f(vct.x,vct.y));
        return std::pair<int, int>(-1,-1);
    }
    else return std::pair<int, int>(-1,-1);
}
void EquipmentWindow::setBorderThick(unsigned int thick)
{
    cloud_border = thick;
    cloud.setOutlineThickness(cloud_border);
}
void EquipmentWindow::hideMenu()
{
    menu.setVisible(false);
}
void EquipmentWindow::controlCloud(sf::Vector2i vct)
{
    if(visible)
    {
        unsigned int gid = getGID(vct);
        if(gid && menu.isVisible() == false)
        {
            descriptions.clear();
            formatter.format(_imgr.getData(gid), cloud.getPosition(),cloud_border,font,descriptions, cloud);
            hoover = true;
            cloud.setPosition(sf::Vector2f(vct.x+15, vct.y));
            return;
        }
        hoover = false;
    }
}
int EquipmentWindow::getSelected(sf::Vector2i& vct)
{
    if(menu.isVisible())
        return menu.selectedOption(vct);
    else return -1;
}
sf::Vector2f EquipmentWindow::getSize()
{
    return _backgrd.getSize();
}
void EquipmentWindow::setCloudSize(sf::Vector2f xxxsize){
    cloud.setSize(xxxsize);
}
void EquipmentWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(visible)
    {
        states.transform *= getTransform();
        if(!grid.getBgVisible())
            target.draw(_backgrd);
        grid.draw(target,states);
        target.draw(equipment);
        if(hoover)
        {
            target.draw(cloud);
            for(auto cloud_text : descriptions)
                target.draw(cloud_text);
        }
        if(menu.isVisible())
        target.draw(menu);
        if(menu1.isVisible())
        target.draw(menu1);
    }
}
std::size_t EquipmentWindow::getCapacity() const{
    return (grid.getSize().x*grid.getSize().y);
}
void EquipmentWindow::updateItems()
{
    update(_imgr.getItemsVector());
}
bool EquipmentWindow::setBoots(Item& i)
{
    return equipment.setBoots(i);
}
bool EquipmentWindow::setArmor(Item& i)
{
    return equipment.setArmor(i);
}
bool EquipmentWindow::setHelmet(Item& i)
{
    return equipment.setHelmet(i);
}
bool EquipmentWindow::setPants(Item& i)
{
    return equipment.setPants(i);
}
bool EquipmentWindow::setWeapon(Item& i)
{
    return equipment.setWeapon(i);
}
bool EquipmentWindow::setShield(Item& i)
{
    return equipment.setShield(i);
}
Item EquipmentWindow::unwearWeapon()
{
    return equipment.unwearWeapon();
}
Item EquipmentWindow::unwearHelmet()
{
    return equipment.unwearHelmet();
}
Item EquipmentWindow::unwearArmor()
{
    return equipment.unwearArmor();
}
Item EquipmentWindow::unwearPants()
{
    return equipment.unwearPants();
}
Item EquipmentWindow::unwearBoots()
{
    return equipment.unwearBoots();
}
Item EquipmentWindow::unwearShield()
{
    return equipment.unwearShield();
}
