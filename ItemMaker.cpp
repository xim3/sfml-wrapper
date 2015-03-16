#include <iostream>
#include <string>
#include "tinyxml/tinyxml.h"
// Type
// weapon, armor, recovery, 
// data
// wep
//	attack speed quality
// arm
//  defense quality
// rec
//  power
#define TYPESNUM 3
enum ITEM_TYPE{WEAPON, ARMOR, RECOVERY};
std::string resolveTypename(ITEM_TYPE x){
	switch(x){
		case 0:
		return "weapon";
		case 1:
		return "armor";
		case 2:
		return "recovery";
		default:
		return "undefined";
	}
}
void createItem(ITEM_TYPE t, TiXmlElement *root)
{
	std::string buffer, buffer1;
	std::cout << "Podaj GID:";
	std::cin >> buffer;
	std::cin.ignore(100,'\n');
	std::cout << "Podaj nazwe:";
	getline(std::cin, buffer1);
	std::cin.ignore(100,'\n');
	TiXmlElement *item = new TiXmlElement("item");
	item->SetAttribute("gid", buffer.c_str());
	item->SetAttribute("name", buffer1.c_str());
	std::string typ = resolveTypename(t);
	item->SetAttribute("type", typ.c_str());
	root->LinkEndChild(item);		
	std::cout << "Podaj opis:";
	getline(std::cin, buffer);
	std::cin.ignore(100,'\n');
	TiXmlText *x = new TiXmlText(buffer.c_str());
	TiXmlElement *itemDescript = new TiXmlElement("desc");
	item->LinkEndChild(itemDescript);
	itemDescript->LinkEndChild(x);	
	TiXmlElement *itemData = new TiXmlElement("data");
	switch(t)
	{
		case WEAPON:
		std::cout << "Podaj atak:";
		std::cin >> buffer;
		itemData->SetAttribute("attack", buffer.c_str());		
		std::cout << "Podaj szybkość:";
		std::cin >> buffer;
		itemData->SetAttribute("speed", buffer.c_str());		
		std::cout << "Podaj jakość:";
		std::cin >> buffer;
		itemData->SetAttribute("quality", buffer.c_str());		
		std::cout << "Podaj cene:";
		std::cin >> buffer;
		itemData->SetAttribute("price", buffer.c_str());		
		break;
		case ARMOR:
		std::cout << "Podaj obrone:";
		std::cin >> buffer;
		itemData->SetAttribute("defense", buffer.c_str());
		std::cout << "Podaj jakość:";
		std::cin>>buffer;
		itemData->SetAttribute("quality", buffer.c_str());		
		std::cout << "Podaj cene:";
		std::cin >> buffer;
		itemData->SetAttribute("price", buffer.c_str());		
		break;
		case RECOVERY:
		std::cout << "Podaj moc:";
		std::cin >> buffer;
		itemData->SetAttribute("power", buffer.c_str());		
		std::cout << "Podaj cene:";
		std::cin >> buffer;
		itemData->SetAttribute("price", buffer.c_str());		
		break;
	}
	item->LinkEndChild(itemData);	
}
int main()
{
	TiXmlDocument doc;	
	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0","","");
	doc.LinkEndChild(decl);	
	TiXmlElement *root = new TiXmlElement("items");
	doc.LinkEndChild(root);	
	int x=0;
	while(1)
	{
		std::cout << "Jaki typ itemu chcesz zrobić:";
		std::cin >> x;
		if(x == 666) break;
		if(x >= 0 && x < TYPESNUM)
			createItem((ITEM_TYPE)x,root);		
		else
			std::cout << "Zły typ\n";
	}
	doc.SaveFile("items.xml");
}
