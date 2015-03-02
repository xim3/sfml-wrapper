#pragma once
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "ItemManager.hpp"
#include "../NpcManager/NpcManager.hpp"
enum TILETYPE{BG, BG_DECORATION, ITEM, PORTAL, M_NPC};
/**
 * \brief Klasa renderująca mape
 * 
 **/
class TileMap : public sf::Drawable, public sf::Transformable
{
	public:
		void       	 setItemManagerHandle(ItemManager* igr);
		/*** \brief Zwraca liczbe itemów na mapie**/		
		size_t     	 itemsOnMapCount() const {return itemsOnMap.size();}
		/*** \brief Zwraca liczbe solidnych kratek na mapie**/
		size_t     	 solidTilesCount() const {return solidTiles.size();}
		bool       	 loadMap(const std::string name);
		bool       	 isItem(sf::Vector2u, int & _id) const;
		bool 	   	 isPortal(sf::Vector2u);
		bool       	 pickItem(sf::Vector2u);
		bool       	 dropItem(const int);
		bool       	 isSolidTile(sf::Vector2u) const;
		sf::Vector2f reload(sf::Vector2u&);
		int		     getGID(size_t) const;
		const sf::Texture& getTexture() const;
		void	     refreshAnimations();
		void 	     setNPCManagerHandle(NpcManager *);
		// Tylko do debugowania //
		/*** \brief Funkcja do debugowania**/
		void printSolidTiles(){for(auto it = solidTiles.begin();it!=solidTiles.end();++it){printf("x:%i, y:%i gid:%i\n",it->x,it->y, it->gid);  }}
		/*** \brief Funkcja do debugowania**/
		void    printItems1(){int i=0;printf("==========MAPITEMS==========\n");if(itemsOnMapCount() == 0){	printf("No items On map\n");	printf("===============================\n");	return ;}for(auto item : itemsOnMap){printf("X:%i Y:%i \tGID:%i \tID:%i \tINDEX:%i\n", item.x,item.y,item.gid,item.id,i);i++;}printf("============================\n");}
		////////debugend/////////////		
	private:
		void            appendTile(const unsigned int, const unsigned int, const unsigned int, TILETYPE bgLayer);
		void            loadObjects(TiXmlElement*, unsigned int);
		virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool		    loadTiles(TiXmlElement*, unsigned int);
		/*** \brief Tablica vertexów tła*/
	    sf::VertexArray m_vertices;	
	    /*** \brief Tablica vertexów dekoracji oraz NPC*/	
	    sf::VertexArray m_vertices_bg1; 
	    /*** \brief Tablica vertexów itemów*/
	    sf::VertexArray m_other_vertices;
	    /*** \brief Tablica vertexów portali*/
	    sf::VertexArray m_portals;	
	    /*** \brief Tekstura kafli*/
		sf::Texture     m_tileset;
		unsigned int    width_in_tiles;
		unsigned int    height_in_tiles;
		unsigned int    tile_width;
		unsigned int    tile_height;	
		unsigned int 	max_item_id = 0;
		/*** \brief Solidne kafle*/	
		std::vector<SolidTile> solidTiles;
		/*** \brief Dekoracje */
		std::vector<BackgroundTile> backgroundTiles;
		/*** \brief Portale*/
		std::vector<PortalTile> portals;
		/*** \brief Animowane kafle*/
		std::vector<AnimatedTile> animated;
		/** \brief Itemy leżące na mapie*/
		std::vector<Item> itemsOnMap;
		/** \brief Zegar mapy (do animacji)*/
		sf::Clock _clock;
		NpcManager  *nmgr = nullptr;
		ItemManager *imgr = nullptr;		
};
