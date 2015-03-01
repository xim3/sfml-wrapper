#pragma once
#include <chrono>
#include <ctime>
enum TILETYPE{BG, BG_DECORATION, ITEM, PORTAL, M_NPC};
class TileMap : public sf::Drawable, public sf::Transformable
{
	public:
		void       setItemManagerHandle(ItemManager* igr);		
		size_t     itemsOnMapCount() const {return itemsOnMap.size();}
		size_t     solidTilesCount() const {return solidTiles.size();}
		bool       loadMap(const std::string name);
		bool       isItem(sf::Vector2u, int & _id) const;
		bool 	   isPortal(sf::Vector2u);
		bool       pickItem(sf::Vector2u);
		bool       dropItem(const int);
		bool       isSolidTile(sf::Vector2u) const;
		sf::Vector2f 	   reload(sf::Vector2u&);
		int		   getGID(size_t) const;
		const sf::Texture& getTexture() const;
		void	   setTimeHandle(sf::Clock*);
		void	   refreshAnimations();
		void 	   setNPCManagerHandle(NpcManager *);
		// Tylko do debugowania //
		void printSolidTiles(){for(auto it = solidTiles.begin();it!=solidTiles.end();++it){printf("x:%i, y:%i gid:%i\n",it->x,it->y, it->gid);  }}
		void    printItems1(){int i=0;printf("==========MAPITEMS==========\n");if(itemsOnMapCount() == 0){	printf("No items On map\n");	printf("===============================\n");	return ;}for(auto item : itemsOnMap){printf("X:%i Y:%i \tGID:%i \tID:%i \tINDEX:%i\n", item.x,item.y,item.gid,item.id,i);i++;}printf("============================\n");}
		////////debugend/////////////		
	private:
		void            appendTile(const unsigned int, const unsigned int, const unsigned int, TILETYPE bgLayer);
		void            loadObjects(TiXmlElement*, unsigned int);
		virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool		    loadTiles(TiXmlElement*, unsigned int);
	    sf::VertexArray m_vertices;		
	    sf::VertexArray m_vertices_bg1; 
	    sf::VertexArray m_other_vertices;
	    sf::VertexArray m_portals;	
	    sf::VertexArray m_npc;	
		sf::Texture     m_tileset;
		unsigned int    width_in_tiles;
		unsigned int    height_in_tiles;
		unsigned int    tile_width;
		unsigned int    tile_height;	
		unsigned int 	max_item_id = 0;	
		std::vector<SolidTile> solidTiles;
		std::vector<BackgroundTile> backgroundTiles;
		std::vector<PortalTile> portals;
		std::vector<AnimatedTile> animated;
		std::vector<Item> itemsOnMap;
		sf::Clock *_thandle;
		NpcManager  *nmgr = nullptr;
		ItemManager *imgr = nullptr;		
};
#include "StaticTiledMap.cpp"
