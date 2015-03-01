#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <cassert>
#include "Item.h"
#include "Tiles.h"
#include "Predicates.cpp"
class ItemManager
{
public:
	ItemManager()
	{
		picked.resize(1000);
	};
	~ItemManager(){};
	// Tylko do debugowania
	void    printItems(){int index=0;printf("==========PLAYERITEMS==========\n");if(playerItemCount() == 0){	printf("No items in vct\n");	printf("===============================\n");	return;	}	for(auto item : playerItems)	{	printf("X:%i Y:%i \tGID:%i \tID:%i \tINDEX:%i\n", item.x,item.y,item.gid,item.id,index);	index++;}printf("===============================\n");}
	///////////////
	
	void 	 update(const sf::Vector2u&);
	void 	 addItem(const Item);
	void     setPicked(size_t);
	bool 	 loadItems(const std::string);
	bool	 isPicked(size_t) const;
	bool	 deleteItem(const int);
	Item	 getItem(const int id) const;
	ItemData getData(size_t) const;
	int		 getGID(size_t)const;
	size_t   playerItemCount() const;
private:
	std::vector<Item> playerItems;
	std::vector<ItemData> itemsinfo;
	std::vector<bool> picked;
};
