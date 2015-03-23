#pragma once
#include "NPC.hpp"
#include "../DialogSystem/TextWindow.hpp"
#include "../Resources/tree.hh"
#include "../Resources/Utils.hpp"
enum STATE  {NO_TALK, NOW_TALKING, BEGIN_TALK};
class NpcManager
{
	public:
		NpcManager(IDataRead&, TextWindow&, sf::Vector2u&);
		void addNPC(NPC);
		void clean();
		void update();
		void talk(int);
		void talkWithNearest(sf::Vector2u&);
		void getActions(NPC&, const tree<Action>::sibling_iterator,std::vector<std::wstring> &, bool);
		bool loadDialogs(std::string);
        int  nearNPC(sf::Vector2u) const;
		void  choiceMouseNPC(sf::Vector2i&,sf::Vector2u&, int, int);
        std::size_t countNPC();
	private:
        void loadTree(TiXmlElement*,NPC&, tree<Action>::sibling_iterator, bool);
		std::vector<NPC>          m_npcs;
		std::vector<std::wstring> current_dialogs;
		TextWindow                &window;
		IDataRead                 &reader;
		STATE                     state;
		sf::Clock                 click_clock;
		int                       actual_selected;
		sf::Vector2u              &pl_pos;
};

