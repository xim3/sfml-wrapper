#pragma once
#include "NPC.hpp"
class NpcManager 
{
	public:
		NpcManager();
		void addNPC(NPC npc);
		std::size_t countNPC();
		bool nearNPC(sf::Vector2u v) const;
		void clean();
	private:
		std::vector<NPC> m_npcs;
};

