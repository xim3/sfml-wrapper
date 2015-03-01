#pragma once
#include "NPC.hpp"
NPC::NPC() {}
NPC::NPC(std::string _name, unsigned int _id, unsigned int _gid, sf::Vector2u _pos, std::string _file) 
, name(_name)
, m_pos(_pos)
, id(_id)
{
}

//some comment