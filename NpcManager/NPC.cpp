#include "NPC.hpp"
NPC::NPC() {}
NPC::NPC(std::string _name, unsigned int _id, unsigned int _gid, sf::Vector2u _pos, std::string _file)
: name(_name)
, file(_file)
, x(_pos.x)
, y(_pos.y)
, id(_id)
, gid(_gid)
{
	load();
}

bool NPC::load(){
	TiXmlDocument doc(file.c_str());
	if(!doc.LoadFile()){
		LOG(ERROR) << "Nie udało sie wczytać pliku NPC " << file << " ";
		return false;
	}
	TiXmlElement *npc = doc.FirstChildElement("npc");
	TiXmlElement *talk = npc->FirstChildElement("talk");
	TiXmlElement *dialog = talk->FirstChildElement("dialog");
	while(dialog){
		talky.push_back(dialog->GetText());
		dialog = dialog->NextSiblingElement("dialog");
	}


}
