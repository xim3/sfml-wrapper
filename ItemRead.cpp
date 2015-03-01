#include <iostream>
#include <string>
#include "tinyxml/tinyxml.h"

void printNextNodes(TiXmlElement *option, unsigned int num){
	
	
}
void getNextNode(TiXmlElement *_case){
	printf("id:%s text:%s\n", _case->Attribute("id"), _case->Attribute("text"));
	TiXmlElement *next_node = _case->FirstChildElement("npctext");
	printf("npc:%s\n",next_node->Attribute("text"));
	if(next_node->Attribute("exit") != NULL){
		printf("Koniec dialogu id:%s\n",_case->Attribute("id"));
		return;
	}
	else{
		printf("Istnieje więcej gałęzi id:%s\n",_case->Attribute("id"));
		TiXmlElement *n_node = _case->FirstChildElement("npctext");
		return;
		
	}
}
int main()
{
	TiXmlDocument doc("zenek.xml");
	if(!doc.LoadFile()){

	printf("lipa");
		return true;
	}
	TiXmlElement *npc = doc.FirstChildElement("npc");
	TiXmlElement *talk = npc->FirstChildElement("talk");
	TiXmlElement *npctext = talk->FirstChildElement("npctext");
	TiXmlElement *option = npctext->NextSiblingElement("options");
	printf("num:%s\n", option->Attribute("count"));
	TiXmlElement *_case = option->FirstChildElement("case");
	while(_case)
	{
		getNextNode(_case);
		_case = _case->NextSiblingElement("case");
	}
}
