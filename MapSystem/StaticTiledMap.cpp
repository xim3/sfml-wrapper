#include "StaticTiledMap.hpp"
#include "Item.h"
#include "../Resources/Utils.cpp"
#include "../tinyxml/tinyxml.h"
/**
 * \brief Ładuje mape z pliku 
 * \details Niepowodzenia zapisuje do pliku z logiem
 * \param name nazwa mapy do załadowania
 * \return Powodzenie operacji
 **/
bool TileMap::loadMap(const std::string name){	
	std::chrono::time_point<std::chrono::system_clock> start,end;
	start = std::chrono::system_clock::now();
	TiXmlDocument mapFile(name.c_str());
	if(!mapFile.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku \"" << name << "\".";
		return false; 
	}
	LOG(INFO) << "Wczytano poprawnie plik \"" << name << "\".";
	TiXmlElement *map = mapFile.FirstChildElement("map");
	width_in_tiles 	  = atoi(map->Attribute("width"));
	height_in_tiles   = atoi(map->Attribute("height"));
	tile_width		  = atoi(map->Attribute("tilewidth"));
	tile_height       = atoi(map->Attribute("tileheight"));

	m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width_in_tiles * height_in_tiles * 4);   
    
    m_other_vertices.setPrimitiveType(sf::Quads);
    m_other_vertices.resize(width_in_tiles * height_in_tiles * 4);
    
    m_vertices_bg1.setPrimitiveType(sf::Quads);
    m_vertices_bg1.resize(width_in_tiles * height_in_tiles * 4);
    
    m_portals.setPrimitiveType(sf::Quads);
    m_portals.resize(width_in_tiles * height_in_tiles * 4);

	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	int firstTID = atoi(tilesetElement->Attribute("firstgid"));

	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imgpath = image->Attribute("source");
	LOG(INFO) << "Szerokość mapy:"   << width_in_tiles
			  << " Wysokość mapy:"   << height_in_tiles
			  << " Szerokość kafla:" << tile_width
			  << " Wysokość kafla:"  << tile_height
			  << " Pierwsze ID:"     << firstTID;
	if(!m_tileset.loadFromFile(imgpath)){
		LOG(ERROR) << "Nie udało sie wczytać tilemapki" << std::endl;
		return false;
	}
	TiXmlElement *layer = map->FirstChildElement("layer");
	std::string lName = layer->Attribute("name");
	if(loadTiles(layer, firstTID) == false)
		return false;
	TiXmlElement *objectsGroup;
	if(map->FirstChildElement("objectgroup") != NULL){
		objectsGroup = map->FirstChildElement("objectgroup");
		loadObjects(objectsGroup, firstTID);
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end-start;
	LOG(DEBUG) << "Załadowano mape, czas wykonania: " << elapsed.count();
	return true;
}
/**
 * \brief Ładuje statyczne kafle 
 * \param layer warstwa kafli
 * \return Powodzenie operacji
 * \details stan loguje do pliku
 **/
bool TileMap::loadTiles(TiXmlElement *layer, unsigned int firstTID){
	unsigned int layerNum, numz;
	unsigned int x,y;
	x=y=layerNum=numz=0;
	std::string lName;
	while(layer){	
		lName = layer->Attribute("name");	
		TiXmlElement* layerData = layer->FirstChildElement("data"); 
		if(layerData == NULL){
			LOG(ERROR) << "[loadTiles]Nie znaleziono <data>";
			return false;
		}
		TiXmlElement *tile = layerData->FirstChildElement("tile");
		if(tile == NULL){
			LOG(ERROR) << "[loadTiles]Nie znaleziono <tile>";
			return false;
		}	
		while(tile){
			int tileNumber = atoi(tile->Attribute("gid"))-firstTID;
			if(lName == "bg"){							
				appendTile(x,y,tileNumber, BG);
				backgroundTiles.push_back(BackgroundTile(x,y,tileNumber));
			}
			if(lName == "other"){
				appendTile(x,y,tileNumber, BG_DECORATION);
			}
			if(lName == "solid" && tileNumber != -1){	
														
				appendTile(x,y,tileNumber, ITEM);
				solidTiles.push_back(SolidTile(x,y,tileNumber));
			}
			tile = tile->NextSiblingElement("tile");    
			x++;
			if (x >= width_in_tiles){
				x = 0;
				y++;
				if (y >= height_in_tiles){
					y = 0;
				}
			}
			numz++;
			}
	layer = layer->NextSiblingElement("layer");
	layerNum++;
	}
	LOG(INFO) << "[loadTiles]Kafle załadowane poprawnie";
	return true;
}
/**
 * \brief Ładuje obiekty
 * \param objectsGroup obiekty w xmlu
 * \details Ładuje obiekty oraz rysuje je na mapie
 * 	(obiekty tj. wszystko co nie jest kafelkiem)
 * \return null
 **/
void TileMap::loadObjects(TiXmlElement *objectsGroup, unsigned int firstTID){
	unsigned int id,ix, iy, i_gid;
	id=ix=iy=i_gid=0;
	std::string name;
	while(objectsGroup){
		TiXmlElement *object = objectsGroup->FirstChildElement("object");
		while(object){
			id	  = atoi(object->Attribute("id"));
			name = objectsGroup->Attribute("name");
			i_gid = atoi(object->Attribute("gid")) - firstTID;
			ix    = (atoi(object->Attribute("x"))) / tile_width; 
			iy 	  = (atoi(object->Attribute("y"))) / tile_width;
			if(imgr != nullptr){
				if(name == "obj"){
					if(imgr->isPicked(id) == false){
						appendTile(ix,iy,i_gid,ITEM);
						itemsOnMap.push_back(Item(ix,iy,i_gid,id, true));
					}
				}
				if(name == "portal"){
					if(object->Attribute("src") == NULL || object->Attribute("spawnx") == NULL ||
					   object->Attribute("spawny") == NULL)
						LOG(ERROR) << "Brakuje atrybutu w portalu " << id <<" ";
					
				sf::Vector2u spaw((atoi(object->Attribute("spawnx")) / tile_height),
								  (atoi(object->Attribute("spawny")) / tile_height));
				appendTile(ix,iy,i_gid,PORTAL);
				std::string file = object->Attribute("src");
				portals.push_back(PortalTile(ix,iy,i_gid,file,spaw));
				}
				if(name == "anim"){
					if(object->Attribute("steps") == NULL ||
					   object->Attribute("speed") == NULL )
						   LOG(ERROR) << "Brakuje atrybutu w animacji " << id << " ";
					double speed = atof(object->Attribute("speed"));
					unsigned int steps = atoi(object->Attribute("steps"));
					Animation _ani;
					_ani.setTileset(m_tileset);
					for(size_t i = 0;i<steps;++i)
						_ani.addFrameGID(i_gid + i);// Magic number, wybaczcie(iy-1)
					animated.push_back(AnimatedTile(ix,iy-1,speed,_ani,tile_width,tile_height));
				}
				if(name == "npc"){
					if(object->Attribute("id") == NULL   || object->Attribute("gid") == NULL  ||
					   object->Attribute("x") == NULL    || object->Attribute("y") == NULL    || 
					   object->Attribute("name") == NULL || object->Attribute("file") == NULL  ){
					   LOG(ERROR) << "Brakuje atrybutu w NPC " << id << " ";
					   }
					   if(nmgr != nullptr){
						   nmgr->addNPC(NPC(object->Attribute("name"), 
							 atoi(object->Attribute("id")),
							 atoi(object->Attribute("gid")),
							 sf::Vector2u
							 (atoi(object->Attribute("x"))/tile_width,
							  atoi(object->Attribute("y"))/tile_height),
										  object->Attribute("file")));
						   appendTile(atoi(object->Attribute("x"))/ tile_width,
									  atoi(object->Attribute("y"))/ tile_height,
									  atoi(object->Attribute("gid")),
									  BG_DECORATION);
						}
				}
			}
			object = object->NextSiblingElement("object");
		}
		objectsGroup = objectsGroup->NextSiblingElement("objectgroup");			
	}
	LOG(INFO) << "Obiekty załadowane";
}
/**
 * \brief Odswieża animacje
 * \details Resetuje zegar i zmienia klatki animacji na mapie
 **/
void TileMap::refreshAnimations()
{
	sf::Time frameTime = _clock.restart();
	std::vector<AnimatedTile>::iterator it = animated.begin();
	for(;it!=animated.end();++it){
		it->txt.play(it->anim);
		it->txt.update(frameTime);
	}
}
//blend
/**
 * \brief Rysuje mape
 * \details Rysuje animacje i wszystko co jest na mapie
 **/
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
	target.draw(m_other_vertices, states);
	target.draw(m_vertices_bg1,states);
	target.draw(m_portals,states);
	std::vector<AnimatedTile>::const_iterator it = animated.begin();
	for(;it!=animated.end();++it)
		it->txt.draw(target,states);
}
/** \brief Usuwa item z mapy
 *  \details Wyszukuje w wektorze itemów na mapie itema o danym xy i usuwa go,
 *   dodaje item o danym id do ItemManagera i ustawia mu flage picked
 *   w klasie ItemManager (oznacza to że item został podniesiony z mapy raz
 *   i przy kolejnym załadowaniu mapy już nie zostanie wyrenderowany)
 *   docelowo flagi picked będą zapisywane w save (ale to jest TODO)
 *   \param xy wektor z pozycją gracza
 *   \return Jeśli item podniesiony true, jeśli pod współrzędnymi nie ma 
 *    itema to false
 **/
bool TileMap::pickItem(sf::Vector2u xy){
	std::vector<Item>::iterator it = 
	std::find_if(itemsOnMap.begin(),itemsOnMap.end(),std::bind(xyCompare<Item>, std::placeholders::_1,xy));
	if(it != itemsOnMap.end()){
		imgr->addItem(*it);
		appendTile(it->x,it->y,0,ITEM);
		imgr->setPicked(it->id);
		itemsOnMap.erase(it);
		return true;
	}
	else
		return false;
}
/**
 * \brief Dodaje item do mapy
 * \details Wyszukuje item o danym id (id są unikalne) w itemach gracza (Klasie 
 *  ItemManager) i usuwa ją z vectora w tej klasie, a następnie dodaje 
 * do itemków na mapie
 * \param id id itemu
 * \return Jeśli istnieje item o takim id true w przeciwnym wypadku false
 **/
bool TileMap::dropItem(const int id){
	Item i = imgr->getItem(id);
	if((i.x != 0 && i.y != 0 && i.valid != 0)){
		itemsOnMap.push_back(i);
		appendTile(i.x,i.y,i.gid,ITEM);
		imgr->deleteItem(id);
		return true;
	}
	return false;
}
/**
 * \brief Dodaje kratke do mapy na podstawie GID
 * \details Dodaje do tablicy vertexów kafelek (item,obiekt - dla każdego typu
 * osobna tablica vertexów)
 * \param x,y współrzędne (po przeliczeniu na normalne współrzędne tj. podawane w kaflach)
 * gid numer kafelka w tilemapce
 * TILETYPE rodzaj 
 *  \return null
 **/
void TileMap::appendTile(const unsigned int x,const unsigned int y, const unsigned int GID,TILETYPE bgLayer){
	sf::Int32 tu = GID % (m_tileset.getSize().x / tile_width);
	sf::Int32 tv = GID / (m_tileset.getSize().x / tile_height);
	sf::Vertex* quad;
	switch(bgLayer)
	{
		case BG: 
			quad = &m_vertices[(x + y * width_in_tiles) * 4];	
			break;
		case BG_DECORATION:
			quad = &m_vertices_bg1[(x + y * width_in_tiles) * 4];
			break;
		case ITEM: 
			quad = &m_other_vertices[(x + y * width_in_tiles) * 4];	
			break;
		case PORTAL:
			quad = &m_portals[(x + y * width_in_tiles) * 4];
			break;
		default:
			quad = &m_vertices_bg1[(x + y * width_in_tiles) * 4];
			break;
	}		
	quad[0].position = sf::Vector2f(x * tile_width, y * tile_height);
	quad[1].position = sf::Vector2f((x + 1) * tile_width, y * tile_height);
	quad[2].position = sf::Vector2f((x + 1) * tile_width, (y + 1) * tile_height);
	quad[3].position = sf::Vector2f(x * tile_width, (y + 1) * tile_height);
			
	quad[0].texCoords = sf::Vector2f(tu * tile_width, tv * tile_height);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tile_width, tv * tile_height);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tile_width, (tv + 1) * tile_height);
	quad[3].texCoords = sf::Vector2f(tu * tile_width, (tv + 1) * tile_height);
}
/**
 * \brief Zwraca boola czy pod danym xy jest item
 * \details Zwraca boola czy pod danym xy jest item, i jeśli tak
 * ustawia przez referencje jego id, jeśli nie to przez referencje 
 * zosanie ustawione -1
 * \param vct współrzędne _id referencja do inta
 * \return true i id w referencji jeśli xy to item
 *         false i -1 w referencji jeśli xy nie jest itemem
 **/
bool TileMap::isItem(const sf::Vector2u vct, int& _id) const{
	std::vector<Item>::const_iterator it = 
	std::find_if(itemsOnMap.begin(), itemsOnMap.end(), std::bind(xyCompare<Item>, std::placeholders::_1,vct));
	if(it != itemsOnMap.end()){
		_id = it->id;
		return true;
	}
	else{
	_id = -1;
	return false;
	}
}
/**
 * \brief Zwraca bool czy xy jest solidną kratka
 * \details Zwraca bool czy xy jest solidna kratka (taka na którą nie można wejść)
 * \param vct współrzędne
 * \return Jeśli xy solidne true, w przeciwnym wypadku false
 **/
bool TileMap::isSolidTile(sf::Vector2u vct) const{
	std::vector<SolidTile>::const_iterator it = 
	std::find_if(solidTiles.begin(), solidTiles.end(), std::bind(xyCompare<SolidTile>, std::placeholders::_1, vct));
	if(it != solidTiles.end()){
		return true;
	}
	else 
		return false;
}
/**
 * \brief Zwraca bool czy xy jest portalem
 * \details Zwraca bool czy xy jest portalem ( linkiem do innej mapy )
 * \param vct współrzędne
 * \return true jeśli portal, w przeciwnym wypadku false
 **/
bool TileMap::isPortal(sf::Vector2u vct){
	std::vector<PortalTile>::iterator it=
	std::find_if(portals.begin(), portals.end(), std::bind(xyCompare<PortalTile>, std::placeholders::_1, vct));
	if(it!=portals.end()){
		LOG(DEBUG) << "Portal to \""<< it->file <<"\".";
		return true;
	}
	else return false;
}
/**
 * \brief Przeładowywuje mapke jeśli dane xy jest portalem(linkiem)
 * \details Przeładowywuje mapke (czyści tablice vertexów, oraz itemy na mapie)
 *  ustawia współrzędne gracza i wywołuje metode loadMap()
 * \param vct Współrzędne
 * \return Nowe współrzędne w których ma pojawić sie gracz lub wektor(0,0) jeśli błąd
 **/
sf::Vector2f TileMap::reload(sf::Vector2u &vct){
	std::string name;
	std::vector<PortalTile>::iterator it=
	std::find_if(portals.begin(), portals.end(), std::bind(xyCompare<PortalTile>, std::placeholders::_1,vct));
	if(it!=portals.end()){
		m_vertices.clear();
		m_other_vertices.clear();
		m_vertices_bg1.clear();
		m_portals.clear();
		solidTiles.clear();
		backgroundTiles.clear();
		itemsOnMap.clear();
		animated.clear();
		nmgr->clean();
		std::string f = it->file;
		sf::Vector2f spawnn(it->spawn.x,it->spawn.y);
		vct.x = it->spawn.x;
		vct.y = it->spawn.y;
		portals.clear();
		loadMap(f);
		return spawnn;
	}
	return sf::Vector2f(0,0);
}
/**
 * \brief Zwraca GID itemu na podstawie ID
 * \details Wyszukuje w vectorze itemów na mapie itemu o danym id
 * i zwraca jego GID
 * \param id id przedmiotu
 * \return GID przedmiotu jeśli istnieje item o takim id na mapie, w przeciwnym wypadku -1
 **/
int TileMap::getGID(size_t id) const{
	std::vector<Item>::const_iterator it=
	std::find(itemsOnMap.begin(),itemsOnMap.end(),Item(0,0,0,id,0));
	if(it!=itemsOnMap.end()){
		return it->gid;
	}
	else return -1;
}
/**
 * \brief Zwraca rozmiary mapy w kaflach
 * \return Rozmiary mapy
 */
sf::Vector2u TileMap::getSize() const{
	return sf::Vector2u(width_in_tiles,height_in_tiles);
}
/**
 * \brief Zwraca rozmiary mapy w floacie
 * \return Rozmiary w float
 */
sf::Vector2f TileMap::getSizeFloat()const{
	return sf::Vector2f(width_in_tiles*tile_width,height_in_tiles*tile_height);
}
/**
 * \brief Zwraca referencje do tilesetu
 * \return sf::Texture&
 **/
const sf::Texture& TileMap::getTexture() const{
	return m_tileset;
}
/**
 * \brief Ustawia uchwyt do klasy NpcManager
 * \details Ustawia uchwyt do klasy NpcManager
 **/
void TileMap::setNPCManagerHandle(NpcManager * _hnd){
	nmgr = _hnd;
}
/**
 * \brief Ustawia uchwyt do klasy ItemManager
 * \details Klasa mapy potrzebuje informacji o itemach
 * i dlatego potrzebny jest tu uchwyt
 **/
void TileMap::setItemManagerHandle(ItemManager*  igr){
	imgr = igr;
}
