#include "NpcManager.hpp"
//#include "NPC.cpp"
// ugly
// x|x|x
// x|o|x <-- Sprawdzane są te pola, 'o' to NPC
// x|x|x
bool near(const NPC& _npc, const sf::Vector2u &vct) 
{
	if((_npc.m_pos.x == vct.x 	  && _npc.m_pos.y == vct.y    ) ||
	   (_npc.m_pos.x == vct.x     && _npc.m_pos.y == vct.y - 1) ||
	   (_npc.m_pos.x == vct.x - 1 && _npc.m_pos.y == vct.y - 1) ||
	   (_npc.m_pos.x == vct.x - 1 && _npc.m_pos.y == vct.y    ) ||
	   (_npc.m_pos.x == vct.x - 1 && _npc.m_pos.y == vct.y + 1) ||
	   (_npc.m_pos.x == vct.x     && _npc.m_pos.y == vct.y + 1) ||
	   (_npc.m_pos.x == vct.x + 1 && _npc.m_pos.y == vct.y - 1) ||
	   (_npc.m_pos.x == vct.x + 1 && _npc.m_pos.y == vct.y    ) ||
	   (_npc.m_pos.x == vct.x + 1 && _npc.m_pos.y == vct.y + 1))
	   return true;
	else 
		return false;
}
NpcManager::NpcManager()
{
}
void NpcManager::addNPC(NPC npc){
	m_npcs.push_back(npc);
}
inline std::size_t NpcManager::countNPC(){
	return m_npcs.size();
}
bool NpcManager::nearNPC(sf::Vector2u v)const {
	std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
	std::bind(near,std::placeholders::_1,v));
	if(it!=m_npcs.end()){
		printf("near %s!\n", it->name.c_str());
		return 1;
	}
	else{
		return 0;
	}
}
void NpcManager::clean(){
	m_npcs.clear();
}
