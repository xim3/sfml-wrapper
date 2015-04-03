#pragma once
#include "NPC.hpp"
#include "../DialogSystem/TextWindow.hpp"
#include "../Resources/tree.hh"
#include "../Resources/Utils.hpp"
#include <unordered_map>
#include <string>
enum STATE  {NO_TALK, NOW_TALKING, BEGIN_TALK};
class NpcManager
{
	public:
		NpcManager(IDataRead&, TextWindow&, sf::Vector2u&, sf::Vector2i&, int t_w=32,int t_h=32);
		void    addNPC(NPC);
		void    clean();
		void    update();
		bool    loadDialogs(std::string);
        int     nearNPC(sf::Vector2u) const;
        std::size_t countNPC();
        void    setPlayerStats(std::unordered_map<std::string, unsigned int>*);
        void    print();
	private:
        bool    checkConditions(std::string);
		void    talk(int);
	    void    choiceMouseNPC();
	    void    drawActions();
	    void    getActions(NPC&, const tree<Action>::sibling_iterator, bool);
        void loadTree(TiXmlElement*,NPC&, tree<Action>::sibling_iterator, bool);
		std::vector<NPC>          m_npcs;
		std::vector<Action>       current_actions;
		TextWindow                &window;
		IDataRead                 &reader;
		STATE                     state;
		sf::Clock                 click_clock;
		int                       actual_selected;
		sf::Vector2u              &pl_pos;
		sf::Vector2i              &mouse;
		int                       t_width;
		int                       t_height;
		std::unordered_map<std::string, unsigned int>* memory = nullptr;
};

