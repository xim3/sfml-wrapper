#pragma once
#include <chrono>
#include <ctime>
#include <queue>
#include <SFML/Graphics.hpp>
#include <stack>
#include "ItemManager.hpp"
#include "../NpcManager/NpcManager.hpp"
/**
 * \brief Typ kafla
 * \details BG - Tło BG_DECORATION - Dekoracja, wyświetlane na warstwie tła
 *   		ITEM - Przedmiot PORTAL - Portal, M_NPC - NPC
 */
enum TILETYPE {BG, BG_DECORATION, ITEM, PORTAL, M_NPC, SOLID};
/**
 * \brief Klasa renderująca mape
 *
 **/
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(ItemManager& , NpcManager & );
    /*** \brief Zwraca liczbe itemów na mapie**/
    size_t     	 itemsOnMapCount() const
    {
        return itemsOnMap.size();
    }
    bool       	 loadMap(const std::string);
    bool       	 isItem(const sf::Vector2u&, int&) const;
    bool 	   	 isPortal(const sf::Vector2u&) const ;
    bool       	 pickItem(const sf::Vector2u&);
    bool       	 dropItem(const int);
    bool       	 isSolidTile(sf::Vector2f) const;
    bool isPointOutOfMap(sf::Vector2u) const;
    sf::Vector2f reload(sf::Vector2u&);
    int          getGID(size_t) const;
    const sf::Texture& getTexture() const;
    void         refreshAnimations();
    void         setNPCManagerHandle(NpcManager*);
    void       	 setItemManagerHandle(ItemManager* igr);
    sf::Vector2u getSize() const;
    sf::Vector2f getSizeFloat() const;

    // Tylko do debugowania //
    /*** \brief Funkcja do debugowania**/
    void printSolidTiles()
    {
        for(auto it = solidTiles.begin(); it!=solidTiles.end(); ++it)
        {
            printf("x:%i, y:%i gid:%i\n",it->x,it->y, it->gid);
        }
    }
    /*** \brief Funkcja do debugowania**/

    ////////debugend/////////////
private:
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void            appendTile(const unsigned int, const unsigned int, const unsigned int, TILETYPE bgLayer);
    void            loadObjects(TiXmlElement*, unsigned int);
    void            cleanMap();
    bool            resizeVertexArrays(size_t, size_t);
    bool            loadTiles(TiXmlElement*, unsigned int);
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
    /** \brief Delegacja do NpcManagera */
    NpcManager  &nmgr;
    /** \brief Delegacja do ItemManagera */
    ItemManager &imgr;
};
