#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/easylogging++.h"
#include "../Resources/tree.hh"
#include "../Resources/Utils.hpp"
struct NPC
{
		NPC();
		NPC(std::string, unsigned int,unsigned int, sf::Vector2u);
		std::string name;
        tree<Action>             dialog;
        tree<Action>::sibling_iterator c_node;
        void print_tree();
		unsigned int x;
		unsigned int y;
		unsigned int id;
		unsigned int gid;
		bool operator==(const NPC&);
};
