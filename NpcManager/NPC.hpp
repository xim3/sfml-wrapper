#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/easylogging++.h"
struct NPC
{
		NPC();
		NPC(std::string, unsigned int,unsigned int, sf::Vector2u, std::string);
		std::string name;
		std::string file;
		std::vector<std::string> talky;
		sf::Vector2u m_pos;
		unsigned int id;
		unsigned int gid;
		bool load();
};