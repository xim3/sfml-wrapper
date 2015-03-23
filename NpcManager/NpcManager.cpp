#include "NpcManager.hpp"
#include "NPC.hpp"
#include "../Resources/Utils.hpp"
#include "../Resources/tinyxml/tinyxml.h"
#include <iostream>
#include <SFML/Graphics.hpp>

NpcManager::NpcManager(IDataRead& _del0, TextWindow& _del1, sf::Vector2u& player)
: window(_del1)
, reader(_del0)
, pl_pos(player)
, actual_selected(-1)
{
}
#include <iostream>
using namespace std;
void  NpcManager::choiceMouseNPC(sf::Vector2i& mouse, sf::Vector2u& player, int tw, int th)
{
    sf::Vector2u normalised = sf::Vector2u(mouse.x/tw, mouse.y/th);
    sf::Time time_button_hold;
    int id = -1;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        time_button_hold += sf::Time(click_clock.getElapsedTime());
        if( time_button_hold > sf::milliseconds(250) )
        {
            time_button_hold = sf::Time::Zero;
            click_clock.restart();
            std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
            std::bind(xyCompare<NPC>,std::placeholders::_1,normalised));
            if(it != m_npcs.end() && nearNPC(player) == it->id)
            {
                state = BEGIN_TALK;
                std::cout << "Selected id:" << it->id << " near id:" << nearNPC(player) << std::endl;
                actual_selected = it->id;
            }
        }
    }
    else
    {
        time_button_hold = sf::Time::Zero;
        click_clock.restart();
    }
}
void NpcManager::talkWithNearest(sf::Vector2u& pos)
{
    int id = nearNPC(pos);
    if(id != -1)
    {
        window.setVisible(true);
        state = NOW_TALKING;
        talk(id);
    }
    else
    {
        window.setVisible(false);
        state = NO_TALK;
    }
}
void NpcManager::talk(int id)
{
    auto it = std::find(m_npcs.begin(), m_npcs.end(), NPC("", id, 0, sf::Vector2u(0,0)));
    if(it != m_npcs.end())
    {
        if(state == NO_TALK)
        {
            window.setVisible(false);
            it->c_node = it->dialog.begin();
        }
        if(state == NOW_TALKING)
        {
            window.setVisible(true);
            getActions(*it, it->c_node, current_dialogs, 0);
        }
        if(state == BEGIN_TALK)
        {
            window.setVisible(true);
            getActions(*it,it->dialog.begin(), current_dialogs, 1);
        }
    }
}
void NpcManager::update()
{
    int n_npc = nearNPC(pl_pos);
    if(n_npc == -1 || n_npc != actual_selected)
    {
        actual_selected = -1;
        window.setVisible(false);
    }
    else
        talk(actual_selected);
}
void NpcManager::getActions(NPC& npc, const tree<Action>::sibling_iterator deep,std::vector<std::wstring> &dials, bool first)
{
    window.clear();
    current_dialogs.clear();
    int depth = npc.dialog.number_of_children(deep);
    if(first)
        window.setNPCString((*npc.dialog.begin()).text);
    if(!first)
		window.setNPCString((*npc.dialog.child(deep,0)).text);
    if(depth == 1)
    {
        window.setNPCString((*npc.dialog.child(deep,0)).text);
        if(window.buttonHold(250))
        {
            npc.c_node = npc.dialog.begin();
            state = NO_TALK;
            window.setVisible(false);
        }
        return;
    }
    int i = (first)?(0):(1);
    for(;i<depth;++i)
    {
        current_dialogs.push_back((*npc.dialog.child(deep,i)).text);
        window.addString((*npc.dialog.child(deep,i)).text);
	}
	int choice;
    if(first)
    choice = window.selectAnwser(0);
    else
    choice = window.selectAnwser(1);
    if(choice != -1)
    {
        window.setVisible(true);
        state = NOW_TALKING;
        npc.c_node = npc.dialog.child(deep, choice);

    }
}
void NpcManager::addNPC(NPC npc){
	m_npcs.push_back(npc);
}
std::size_t NpcManager::countNPC(){
	return m_npcs.size();
}
int NpcManager::nearNPC(sf::Vector2u v)const{
	std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
	std::bind(_near<NPC>,std::placeholders::_1,v));
	if(it!=m_npcs.end())
	    //std::cout << "near!" << " " << it->name << std::endl;
		return it->id;
    else
		return -1;
}
void NpcManager::clean(){
	m_npcs.clear();
}
void NpcManager::loadTree(TiXmlElement* npc_el, NPC &npc, tree<Action>::sibling_iterator go_deeper, bool first)
{
    TiXmlElement *reply = npc_el;
    tree<Action>::iterator root;
    tree<Action>::sibling_iterator sit;
    std::string txt = reply->Attribute("text");
    Action _tmp(wide_string<std::wstring>(txt), NPC_ONLY_TALK, HelpInfo());
    if(first)
        root = npc.dialog.insert(npc.dialog.begin(), _tmp);
    if(reply->FirstChildElement("player") != NULL)
    {
        TiXmlElement *player = reply->FirstChildElement("player");
        if(first)
            sit = root;
        else
            sit = go_deeper;
        while(player)
        {
            reader.read(player);
            auto p_reply = npc.dialog.append_child(sit,reader.get());
            if(player->FirstChildElement("reply") != NULL)
            {
				TiXmlElement* npc_quote = player->FirstChildElement("reply");
				reader.read(npc_quote);
                npc.dialog.append_child(p_reply,reader.get());
                loadTree(player->FirstChildElement("reply"), npc, p_reply, 0);
            }
            player = player->NextSiblingElement("player");

        }
    }
    else return;
}
bool NpcManager::loadDialogs(std::string path)
{
    TiXmlDocument doc(path.c_str());
    if(!doc.LoadFile()){
        LOG(ERROR) << "Nie udalo sie wczytac pliku dialogów";
        return false;
    }
    TiXmlElement *firstChild = doc.FirstChildElement("dialogs");
    TiXmlElement *npc_ent = firstChild->FirstChildElement("npc");
    while(npc_ent)
    {
        if(npc_ent->Attribute("id") == NULL)
        {
            LOG(ERROR) << "Brakuje id w dialogu";
            return false;
        }
        int id = atoi(npc_ent->Attribute("id"));
        auto npc_by_id = std::find(m_npcs.begin(), m_npcs.end(), NPC("",id,0,sf::Vector2u(0,0)));
        if(npc_by_id != m_npcs.end())
        {
            TiXmlElement *hello_npc_message = npc_ent->FirstChildElement("reply");
            loadTree(hello_npc_message, *npc_by_id, npc_by_id->dialog.begin(), 1);
            npc_by_id->print_tree();
        }
        npc_ent = npc_ent->NextSiblingElement("npc");
    }
    return true;
}
