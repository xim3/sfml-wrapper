#include "ItemManager.hpp"

#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/easylogging++.h"

ItemManager::ItemManager(IItemRead& iLoader)
: loader(iLoader)
, capacity(0)
{
    // 1024 - for data align.
    picked.resize(1024);
}
ItemManager::~ItemManager() {}
/**
 * \brief zwraca liczbe itemów w plecaku
 *
 **/
std::size_t ItemManager::playerItemCount() const
{
    return playerItems.size();
}
/**
 * \brief dodaje item do plecaka
 * \details wyszukuje w itema o danym id w vectorze, i jeśli item o takim
 * id nie istnieje - dodaje go
 * \param itm Itemek
 */
void ItemManager::addItem(Item itm)
{
    std::vector<Item>::iterator it =
        std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,itm.id));
    if(it == playerItems.end() && playerItems.size() < capacity)
        playerItems.push_back(itm);
    else return;
}
/**
 * \brief usuwa item z plecaka
 * \details wyszukuje item o danym id w vectorze, i jeśli istnieje - usuwa go
 * \param id id przedmiotu
 * \return jeśli usunięty true, w przeciwnym wypadku false
 */
bool ItemManager::deleteItem(const int id)
{
    std::vector<Item>::iterator it
    = std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,id));
    if(it != playerItems.end())
    {
        playerItems.erase(it);
        return true;
    }
    else return false;
}
/**
 * \brief wyszukuje item o danym id
 * \details wyszukuje item o danym id i jeśli istnieje to zwraca go
 *  jeśli nie istnieje zwraca domyślny item
 * \param id id przedmiotu
 * \return przedmiot
 **/
Item ItemManager::getItem(const int id) const
{
    std::vector<Item>::const_iterator it
    = std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,id));
    if(it != playerItems.end())
        return Item(*it);
    else return Item();
}
/**
 * \brief aktualizuje współrzędne itemów
 * \details aktualizuje współrzędne itemów tj.
 * itemy "chodzą" za graczem, są im przypisywane współrzędne gracza
 * \param vct współrzędne
 * \return null
 */
void ItemManager::update(const sf::Vector2u &vct)
{
    for(auto &item : playerItems)
    {
        item.x = vct.x;
        item.y = vct.y;
    }
}
/**
 * \brief ładuje dane itemów z pliku
 * \details ładuje dane itemów z pliku oraz loguje informacje do pliku
 * \param nazwa pliku XML z danymi itemów
 * \return powodzenie operacji
 */
bool ItemManager::loadItems(std::string name)
{
    TiXmlDocument doc(name.c_str());
    if(!doc.LoadFile())
    {
        LOG(ERROR) << "Nie udało sie wczytać pliku \"" << name << "\".";
        return false;
    }
    TiXmlElement *items = doc.FirstChildElement("items");
    TiXmlElement *item = items->FirstChildElement("item");
    loader.read(item, itemsinfo);
    LOG(DEBUG) << "Załadowano dane " << itemsinfo.size() << " itemów.";
    return true;
}
/**
 * \brief zwraca strukture ItemData zawierającą dane o przedmiocie
 * \details wyszukuje itema o danym GID (do jednej teksturki może być
 * przypisana tylko jedna specyfikacja)
 * \param gid gid przedmiotu
 * \return jeśli znaleziono to ItemData z danymi, jeśli nie to ItemData
 * z wyzerowanymi polami i nazwą "undefined"
 */
const ItemData& ItemManager::getData(size_t gid) const
{
    std::vector<ItemData>::const_iterator it =
        std::find(itemsinfo.begin(), itemsinfo.end(), ItemData(WEAPON,L"",L"",0,0,0,0,0,0,gid));
    if(it != itemsinfo.end())
        return *it;
    return undef;
}
/**
 * \brief zwraca GID itemu na podstawie ID
 */
int ItemManager::getGID(size_t id) const
{
    return getItem(id).gid;
}
/**
 * \brief ustawia flage picked dla danego ID
 * \details ustawia bool picked w wektorze 'picked'
 * picked domyślnie ma 1000 slotów a pojedyńczy indeks odpowiada danemu id
 * ma to na celu zablokowania istnienia przedmiotu który został wpisany do pliku mapy
 * przy następnych ładowaniach mapy
 * \param id id przedmiotu
 * \return null
 */
void ItemManager::setPicked(size_t id)
{
    picked[id] = true;
}
/**
 * \brief zwraca wartość czy dany item został już podniesiony
 */
bool ItemManager::isPicked(size_t id) const
{
    return picked[id];
}
const std::vector<Item>& ItemManager::getItemsVector() const
{
    return playerItems;
}
void ItemManager::setCapacity(size_t cap)
{
    if(cap < 0) return;
    capacity = cap;
}
std::size_t ItemManager::getCapacity()
{
    return capacity;
}
