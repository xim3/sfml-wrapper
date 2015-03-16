#include "Entity.hpp"
#include "../Resources/easylogging++.h"
#include "../Resources/tinyxml/tinyxml.h"
#include <stdexcept>
/**
 * \brief Konstruktor
 * \param x,y współrzędne
 */
Entity::Entity(unsigned int x, unsigned int y)
{
	tile_height = x;
	tile_width = y;
	anitex.setOrigin(tile_width/2,tile_height);
	nokeypressed = true;
}
/**
 * \brief Ładuje animacje z pliku
 * \details Możliwe dwa formaty plików, informacje logowane do pliku.
 * \param path - ścieżka do pliku XML
 * \return Powodzenie operacji
 */
sf::Vector2f Entity::getPositionFixed(DIR UanDirekszyn, float fix) const{
    switch(UanDirekszyn){
        case D_LEFT:  return sf::Vector2f(getPositionFloat().x-fix, getPositionFloat().y);
        case D_RIGHT: return sf::Vector2f(getPositionFloat().x+fix, getPositionFloat().y);
        case D_UP:    return sf::Vector2f(getPositionFloat().x, getPositionFloat().y-fix);
        case D_DOWN:  return sf::Vector2f(getPositionFloat().x, getPositionFloat().y+fix);
        default:      return sf::Vector2f(0,0);
    }
}
bool Entity::load(const std::string path)
{
	TiXmlDocument doc(path.c_str());
	if(!doc.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku bytu \"" << path << "\".";
		return false;
	}
	TiXmlElement *pla = doc.FirstChildElement("player");
	if(pla->Attribute("file") == NULL || pla->Attribute("width") == NULL ||
	   pla->Attribute("height") == NULL  ||  pla->Attribute("speed") == NULL ||
	   pla->Attribute("datatype") == NULL || pla->Attribute("frametime") == NULL){
		   LOG(ERROR) << "Brakuje atrybutu w pliku bytu";
		   return false;
	}
	std::string tileset = pla->Attribute("file");
	std::string datatype = pla->Attribute("datatype");
	anitex.setFrameTime(sf::seconds(atof(pla->Attribute("frametime"))));
	if(!tiles.loadFromFile(tileset)){
		LOG(ERROR) << "Nie udalo sie wczytać tilemapy bytu";
		return false;
	}
	unsigned int width, height;
	width = atoi(pla->Attribute("width"));
	height = atoi(pla->Attribute("height"));
	speed = atof(pla->Attribute("speed"));
	TiXmlElement *tex = pla->FirstChildElement();
	while(tex){
		TiXmlElement* data = tex->FirstChildElement();
		if(tex->Attribute("action") == NULL){
			LOG(ERROR) << "Brak atrybutu action w pliku \"" << path << "\"";
			return false;
		}
		std::string action = tex->Attribute("action");
		Animation _anim;
		_anim.setTileset(tiles);
		while(data){
			if(datatype == "gid"){
				if(data->Attribute("gid") == NULL){
					LOG(ERROR) << "Brak atrybutu gid w pliku \"" << path << "\"";
					return false;
				}
				unsigned int gid;
				gid = atoi(data->Attribute("gid"));
				_anim.addFrameGID(gid);
			}
			if(datatype == "xy"){
				if(data->Attribute("x") == NULL || data->Attribute("y") == NULL){
					LOG(ERROR) << "Brak atrybutów x lub y w pliku \"" << path << "\"";
					return false;
				}
				unsigned int x,y;
				x = atoi(data->Attribute("x"));
				y = atoi(data->Attribute("y"));
				_anim.addFrame(sf::IntRect(x,y,width,height));
			}
			data = data->NextSiblingElement("data");
		}
		_anims[action] = _anim;
		tex = tex->NextSiblingElement("tex");
	}
	try{
    c_anim = &_anims.at("down");
	}
	catch(const std::out_of_range& oou){
	    LOG(ERROR) << "Nie znaleziono animacji";
	    return false;
	}
	LOG(DEBUG) << "Byt załadowany";
	return true;
}
/**
 * \brief Porusza obiekt w dół i animuje ruch
 */
void Entity::move(std::string action){
    nokeypressed = false;
	try{
	c_anim = &_anims.at(action);
	}
	catch(const std::out_of_range& oou){
	    LOG(ERROR) << "Nie znaleziono animacji " << "\"" << action << "\"";
	    return;
	}
	if(action == "down")
        position.y += speed;
    else if(action == "up")
        position.y -= speed;
    else if(action == "left")
        position.x -= speed;
    else if(action == "right")
        position.x += speed;
}
void Entity::action(std::string action){
    try{
    c_anim = &_anims.at(action);
    }
    catch(const std::out_of_range& oou){
        LOG(ERROR) << "Nie znaleziono animacji " << "\"" << action << "\"";
        return;
    }
    nokeypressed = false;
}
/**
 * \brief Odświeża animacje
 */
void Entity::update(){
	sf::Time ftime = _clock.restart();
	anitex.play(*c_anim);
	anitex.move(position * ftime.asSeconds());
	if(nokeypressed){
	anitex.stop();
	}
	anitex.update(ftime);
	nokeypressed = true;
	idle();
}
/**
 * \brief Ustawia pozycje ( w kaflach )
 * \param xy - współrzędne
 */
void Entity::setPosition(unsigned int x,unsigned int y){
	anitex.setPosition(sf::Vector2f(x*tile_width,y*tile_height));
}
/**
 * \brief Ustawia pozycje ( float )
 * \param xy - współrzędne
 */
void Entity::setPositionFloat(float x, float y){
	anitex.setPosition(sf::Vector2f(x,y));
}
/**
 * \brief Rysuje
 */
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	anitex.draw(target,states);
}
/**
 * \brief idle
 */
void Entity::idle(){
	position = sf::Vector2f(0,0);
}
/**
 * \brief Zwraca pozycje przeliczoną na kafle
 * \return Pozycja
 */
sf::Vector2u Entity::getPosition() const{
	return sf::Vector2u((anitex.getPosition().x)/tile_width,(anitex.getPosition().y)/tile_height);
}
sf::Vector2i Entity::getPositionInt() const{
    return sf::Vector2i((anitex.getPosition().x)/tile_width,(anitex.getPosition().y)/tile_height);
}
/**
 * \brief Zwraca pozycje w floatcie
 */
sf::Vector2f Entity::getPositionFloat()const {
	return sf::Vector2f((anitex.getPosition().x)/tile_width,(anitex.getPosition().y)/tile_height);
}
