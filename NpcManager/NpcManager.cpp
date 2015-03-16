#include "NpcManager.hpp"
#include "NPC.hpp"
#include "../Resources/Utils.hpp"
#include <SFML/Graphics.hpp>
NpcManager::NpcManager()
{
}
void NpcManager::addNPC(NPC npc){
	m_npcs.push_back(npc);
}
std::size_t NpcManager::countNPC(){
	return m_npcs.size();
}
bool NpcManager::nearNPC(sf::Vector2u v)const {
	std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
	std::bind(_near<NPC>,std::placeholders::_1,v));
	if(it!=m_npcs.end()){
		return 1;
	}
    else{
		return 0;
	}
}
void NpcManager::clean(){
	m_npcs.clear();
}
