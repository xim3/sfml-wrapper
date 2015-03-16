#include "OwnItemManager.hpp"
#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/easylogging++.h"
bool MyItemManager::loadItems(const std::string name)
{
	TiXmlDocument doc(name.c_str());
	if(!doc.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku \"" << name << "\".";
		return false;
	}
	TiXmlElement *items = doc.FirstChildElement("items");
	TiXmlElement *item = items->FirstChildElement("item");
	std::wstring nline_pattern = L"\\n";
	while(item){
		unsigned int _attack,_quality,_price,_defence,_power;
		double _speed;
		std::wstring name,desc;
		int gid = (atoi(item->Attribute("gid")) );
		name = wide_string<std::wstring>(item->Attribute("name"));
		TiXmlElement* descr = item->FirstChildElement("desc");
		desc = wide_string<std::wstring>(descr->GetText());

		size_t pos = 0;
		while ((pos = desc.find(L"\\n", pos)) != std::string::npos){
                desc.replace(pos-nline_pattern.length(),4,L"\n\n");
		}
		TiXmlElement* data = descr->NextSiblingElement("data");
		ITEM_TYPE typen = (ITEM_TYPE)atoi(item->Attribute("type"));
		switch(typen){
			case WEAPON:
			// Bronie mogą miec
			// Atak, szybkość, obrone, moc, jakość, cene
			if(data->Attribute("attack")  == NULL || data->Attribute("speed") == NULL ||
               data->Attribute("defence") == NULL || data->Attribute("power") == NULL ||
			   data->Attribute("quality") == NULL || data->Attribute("price") == NULL){
				   LOG(ERROR) << "Brakuje atrybutu itemka \"" << name <<  "\".";
				   return false;
			  }
			_attack = atoi(data->Attribute("attack"));
			_speed = atoi(data->Attribute("speed"));
			_power = atof(data->Attribute("power"));
			_quality = atoi(data->Attribute("quality"));
			_price = atoi(data->Attribute("price"));
			_defence = atoi(data->Attribute("defence"));
			break;
            // Zbroje mogą mieć
            // Obrone, jakość, moc, cene
			case ARMOR:
			if(data->Attribute("defence") == NULL || data->Attribute("price") == NULL ||
			   data->Attribute("quality") == NULL || data->Attribute("power") == NULL  ){
				   LOG(ERROR) << "Brakuje atrybutu itemka \"" << name << "\".";
				   return false;
		     }
			_attack = _speed;
			_power = atoi(data->Attribute("power"));
			_defence = atoi(data->Attribute("defence"));
			_quality = atoi(data->Attribute("quality"));
			_price = atoi(data->Attribute("price"));
			break;
            //Potiony mogą mieć
            //Moc i cene
			case RECOVERY:
			if(data->Attribute("power") == NULL || data->Attribute("price") == NULL){
				LOG(ERROR)<< "Brakuje atrybutu itemka \"" << name << "\".";
				return false;
			}
			_attack = _defence = _speed = _quality = 0;
			_speed = 0;
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
const Data& MyItemManager::getData(size_t gid) const
{
	std::vector<ItemData>::const_iterator it =
	std::find(itemsinfo.cbegin(), itemsinfo.cend(), ItemData(WEAPON,L"",L"",0,0,0,0,0,0,gid));
	if(it != itemsinfo.end()){
		return *it;
	}
	return undef;
}
