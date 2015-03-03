#include "Equipment.h"
#include "../Resources/easylogging++.h"
Equipment::Equipment(std::string path, std::string path1,sf::RenderWindow* _whnd, int width_in_tiles,
int height_in_tiles, sf::Vector2f position,int t_width,int t_height){
    loadTextureBg(path);
    loadTextureItems(path1);
    background.setTexture(_bg1);
    background.setPosition(position);
    item_grid.setPrimitiveType(sf::Quads);
    item_grid.resize(width_in_tiles * height_in_tiles * 4); 
    window = _whnd;
}

void Equipment::addItem(EquipmentItem new_item){
    items.push_back(new_item);
}

void Equipment::removeItem(int id){
    items.erase(items.begin() + id);
}

/*void Equipment::draw(sf::RenderWindow& window){
    window.draw(background);
    items[0].setPosition(background.getPosition(), 0, 0, 0);
    window.draw(items[0].getSprite());
    for(size_t x = 1; x < items.size(); x++)
    {
        items[x].setPosition(sf::Vector2f(background.getPosition().x + 1, background.getPosition().y + 1), 0, 0, 0); //TODO
        window.draw(items[x].getSprite());
    }
}*/

void Equipment::showBox() const{
    sf::Vector2f mouse_position(sf::Mouse::getPosition(*window));
    for(size_t x = 0; x < items.size(); x++)
    {
        //if(items[x].getSprite().getGlobalBounds().contains(mouse_position))
        //    items[x].showBox(*window);
    }
}
void Equipment::loadTextureBg(const std::string name){
	if(_bg1.loadFromFile(name) == false){
		LOG(ERROR) << "Błąd wczytywania tekstury GUI";
		printf("xxxa");
		return;
	}
}
void Equipment::loadTextureItems(const std::string name){
	if(_it1.loadFromFile(name) == false){
		LOG(ERROR) << "Błąd wczytywania tekstury itemów";
		printf("xxx");
		return;
	}
}
void Equipment::setPosition(sf::Vector2f vct){
	background.setPosition(vct);
	
}
//void Equipment::drawItems(){
//	for(auto it = items.begin(); it != items.end(); ++it){
//		
//	}
//}
void Equipment::appendItem(const unsigned int x,const unsigned int y, const unsigned int GID){
	sf::Int32 tu = GID  % (_it1.getSize().x / tile_width);
	sf::Int32 tv = GID / (_it1.getSize().x / tile_height);
	sf::Vertex* quad;
	quad = &item_grid[(x + y * width_in_tiles) * 4];	
	quad[0].position = sf::Vector2f(x * tile_width, y * tile_height);
	quad[1].position = sf::Vector2f((x + 1) * tile_width, y * tile_height);
	quad[2].position = sf::Vector2f((x + 1) * tile_width, (y + 1) * tile_height);
	quad[3].position = sf::Vector2f(x * tile_width, (y + 1) * tile_height);
			
	quad[0].texCoords = sf::Vector2f(tu * tile_width, tv * tile_height);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tile_width, tv * tile_height);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tile_width, (tv + 1) * tile_height);
	quad[3].texCoords = sf::Vector2f(tu * tile_width, (tv + 1) * tile_height);
}
void Equipment::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &_it1;
	target.draw(item_grid,states);
	//target.draw(background);
	
}
