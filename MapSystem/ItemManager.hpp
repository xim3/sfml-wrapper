#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include "Item.h"
#include "Tiles.h"
#include "../Resources/Utils.hpp"
/**
 * \brief Manager itemów gracza
**/
class ItemManager
{
public:
    ItemManager(IItemRead&);
    virtual ~ItemManager();
    /** \brief Tylko do debugowania */
    void     printItems()
    {
        int index=0;
        printf("==========PLAYERITEMS==========\n");
        if(playerItemCount() == 0)
        {
            printf("No items in vct\n");
            printf("===============================\n");
            return;
        }
for(auto item : playerItems)
        {
            printf("X:%i Y:%i \tGID:%i \tID:%i \tINDEX:%i\n", item.x,item.y,item.gid,item.id,index);
            index++;
        }
        printf("===============================\n");
    }
    void 	 update(const sf::Vector2u&);
    void 	 addItem(const Item);
    void     setPicked(size_t);
    bool	 isPicked(size_t) const;
    bool	 deleteItem(const int);
    Item	 getItem(const int id) const;
    bool     loadItems(const std::string);
    const    ItemData& getData(size_t) const;
    int		 getGID(size_t)const;
    void     setCapacity(size_t);
    size_t   getCapacity();
    const std::vector<Item>& getItemsVector() const;
    size_t   playerItemCount() const;
protected:
    /** \brief itemy w plecaku */
    IItemRead             &loader;
    std::vector<ItemData> itemsinfo;
    std::vector<Item> playerItems;
    /** \brief flagi podniesienia */
    std::vector<bool> picked;
    /** \brief ilość pól w plecaku*/
    size_t           capacity;
    ItemData         undef;
};
