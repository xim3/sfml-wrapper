inline size_t ItemManager::playerItemCount() const{
	return playerItems.size();
}

inline void ItemManager::addItem(Item itm){
	std::vector<Item>::iterator it = 
	std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,itm.id,0));
	if(it == playerItems.end()){
	playerItems.push_back(itm);
	}
	else return;
}

inline bool ItemManager::deleteItem(const int id){
	std::vector<Item>::iterator it 
	= std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,id,0));
	if(it != playerItems.end()){
		playerItems.erase(it);
		return true;
	}
	else
		return false;
}

Item ItemManager::getItem(const int id) const{
	std::vector<Item>::const_iterator it 
	= std::find(playerItems.begin(), playerItems.end(), Item(0,0,0,id,0));
	if(it != playerItems.end())
		return Item(*it);
	else
		return Item();
}

void ItemManager::update(const sf::Vector2u &vct){
	for(auto &item : playerItems){
		item.x = vct.x;
		item.y = vct.y;
	}
}

bool ItemManager::loadItems(std::string name)
{
	TiXmlDocument doc(name.c_str());
	if(!doc.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku \"" << name << "\".";
		return false;
	}
	TiXmlElement *items = doc.FirstChildElement("items");
	TiXmlElement *item = items->FirstChildElement("item");
	while(item){
		unsigned int _attack,_quality,_price,_defence,_power;
		double _speed;	
		std::string name,desc;
		int gid = (atoi(item->Attribute("gid")) );
		name = item->Attribute("name");
		TiXmlElement* descr = item->FirstChildElement("desc");
		desc = descr->GetText();
		TiXmlElement* data = descr->NextSiblingElement("data");
		ITEM_TYPE typen = (ITEM_TYPE)atoi(item->Attribute("type"));
		switch(typen){
			case WEAPON:
			if(data->Attribute("attack")  == NULL || data->Attribute("speed") == NULL ||
			   data->Attribute("quality") == NULL || data->Attribute("price") == NULL){
				   LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
				   return false;
			  }
			_attack = atoi(data->Attribute("attack"));
			_speed = atof(data->Attribute("speed"));
			_quality = atoi(data->Attribute("quality"));
			_price = atoi(data->Attribute("price"));
			_defence = _power = 0;
			break;
			
			case ARMOR:
			if(data->Attribute("defence") == NULL || data->Attribute("price") == NULL ||
			   data->Attribute("quality") == NULL){
				   LOG(ERROR) << "Brakuje atrybutu itemka \"" << name << "\".";
				   return false;
		     }
			_attack = _speed = _power = 0;
			_defence = atoi(data->Attribute("defence"));
			_quality = atoi(data->Attribute("quality"));
			_price = atoi(data->Attribute("price"));
			break;
			
			case RECOVERY:
			if(data->Attribute("power") == NULL || data->Attribute("price") == NULL){
				LOG(ERROR)<< "Brakuje atrybutu itemka \"" << name << "\".";
				return false;
			}
			_attack = _defence = _speed = _quality = 0;
			_speed = 0.0;
			_power = atoi(data->Attribute("power"));
			_price = atoi(data->Attribute("price"));
			break;
			
			default:
			_attack = _defence = _quality = _power = _price  = 0;
			_speed  = 0.0f;
		}
		itemsinfo.push_back(ItemData(typen, desc, name,_attack,_defence,_quality,_price,_power,_speed,gid));
		item = item->NextSiblingElement("item");
	}
	LOG(ERROR) << "Załadowano dane" << itemsinfo.size() << " itemów.";
	return true;
}

ItemData ItemManager::getData(size_t gid) const
{
	std::vector<ItemData>::const_iterator it = 
	std::find(itemsinfo.begin(), itemsinfo.end(), ItemData(WEAPON,"","",0,0,0,0,0,0,gid));
	if(it != itemsinfo.end())
		return *it;
	return ItemData(WEAPON,"undefined","undefined",0,0,0,0,0,0,0);
}

int ItemManager::getGID(size_t id) const
{
	return getItem(id).gid;
}

inline void ItemManager::setPicked(size_t id){
	picked[id] = true;
}

inline bool ItemManager::isPicked(size_t id) const{
	return picked[id];
}

