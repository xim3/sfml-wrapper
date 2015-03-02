#include "Entity.hpp"
#include "../Resources/easylogging++.h"
#include "../Resources/tinyxml/tinyxml.h"
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
bool Entity::load(const std::string path)
{
	TiXmlDocument doc(path.c_str());
	if(!doc.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku ludzika \"" << path << "\".";
		return false;
	}
	TiXmlElement *pla = doc.FirstChildElement("player");
	if(pla->Attribute("file") == NULL || pla->Attribute("width") == NULL ||
	   pla->Attribute("height") == NULL  ||  pla->Attribute("speed") == NULL ||
	   pla->Attribute("datatype") == NULL || pla->Attribute("frametime") == NULL){
		   LOG(ERROR) << "Brakuje atrybutu w pliku ludzika";
		   return false;
	}
	std::string tileset = pla->Attribute("file");
	std::string datatype = pla->Attribute("datatype");
	anitex.setFrameTime(sf::seconds(atof(pla->Attribute("frametime"))));
	if(!tiles.loadFromFile(tileset)){
		LOG(ERROR) << "Nie udalo sie wczytać tilemapy ludzika";
		return false;
	}	
	unsigned int width, height;
	width = atoi(pla->Attribute("width"));
	height = atoi(pla->Attribute("height"));
	speed = atof(pla->Attribute("speed"));
	TiXmlElement *tex = pla->FirstChildElement();
	while(tex){
		TiXmlElement* data = tex->FirstChildElement();
		if(tex->Attribute("dir") == NULL){
			LOG(ERROR) << "Brak atrybutu dir w pliku \"" << path << "\"";
			return false;
		}
		std::string dir = tex->Attribute("dir");
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
		anims.push_back(_anim);
		tex = tex->NextSiblingElement("tex");
	}
	c_anim = &anims[0];
	LOG(DEBUG) << "Ludzik załadowany";
	return true;
}
/**
 * \brief Porusza obiekt w dół i animuje ruch
 */
void Entity::moveDown(){
	nokeypressed = false;
	c_anim = &anims[0];
	position.y += (unsigned int)speed;
}
/**
 * \brief Porusza obiekt w lewo i animuje ruch
 */
void Entity::moveLeft(){
	nokeypressed = false;
	c_anim = &anims[1];
	position.x -= (unsigned int)speed;
}
/**
 * \brief Porusza obiekt w prawo i animuje ruch
 */
void Entity::moveRight(){
	nokeypressed = false;
	c_anim = &anims[2];
	position.x += (unsigned int)speed;
}
/**
 * \brief Porusza obiekt w góre i animuje ruch
 */
void Entity::moveUp(){
	nokeypressed = false;
	c_anim = &anims[3];
	position.y -= (unsigned int)speed;
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
sf::Vector2u Entity::getPosition(){
	return sf::Vector2u((anitex.getPosition().x)/tile_width,(anitex.getPosition().y)/tile_height);
}
/**
 * \brief Zwraca pozycje w floatcie
 */
sf::Vector2f Entity::getPositionFloat(){
	return sf::Vector2f(anitex.getPosition().x,anitex.getPosition().y);
}
