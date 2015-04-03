#include "NpcManager.hpp"
#include "NPC.hpp"
#include "../Resources/Utils.hpp"
#include "../Resources/tinyxml/tinyxml.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
NpcManager::NpcManager(IDataRead& _del0, TextWindow& _del1, sf::Vector2u& player, sf::Vector2i& mous, int t_w, int t_h)
: window(_del1)
, reader(_del0)
, actual_selected(-1)
, pl_pos(player)
, mouse(mous)
, t_width(t_w)
, t_height(t_h) {}
#include <iostream>
using namespace std;
void  NpcManager::choiceMouseNPC()
{
    sf::Vector2u normalised = sf::Vector2u(mouse.x/t_width, mouse.y/t_height);
    sf::Time time_button_hold;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        time_button_hold += sf::Time(click_clock.getElapsedTime());
        if( time_button_hold > sf::milliseconds(100) )
        {
            time_button_hold = sf::Time::Zero;
            click_clock.restart();
            std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
            std::bind(xyCompare<NPC>,std::placeholders::_1,normalised));
            unsigned int _nearID = nearNPC(pl_pos);
            if(it != m_npcs.end() && _nearID == it->id)
            {
                state = BEGIN_TALK;
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
            getActions(*it, it->c_node, 0);
        }
        if(state == BEGIN_TALK)
        {
            window.setVisible(true);
            getActions(*it,it->dialog.begin(), 1);
        }
    }
}
void NpcManager::update()
{
    choiceMouseNPC();
    int n_npc = nearNPC(pl_pos);
    if(n_npc == -1 || n_npc != actual_selected)
    {
        actual_selected = -1;
        window.setVisible(false);
    }
    else talk(actual_selected);
}
bool NpcManager::checkConditions(std::string to_check)
{
    std::string signs[] = {">","<","==","!=",">=", "<="};
    std::string condition = to_check;
    size_t first_argument_offset   = condition.find_first_of(" ");
    std::string first_arg_to_check = condition.substr(0, first_argument_offset);
    enum {GREATER, LESS, EQUAL, NOT_SAME,GREATER_OR_EQUAL, LESS_OR_EQUAL , UNKNOWN_SIGN} comparision_sign;
    size_t sign_found;
    for(auto sign : signs)
    {
        sign_found = condition.find(sign);
        if(sign_found != string::npos)
        {
            std::string checked = condition.substr(sign_found,(sign.length()==1)?(2):(1));
            if(checked ==  ">") comparision_sign = GREATER;
            if(checked ==  "<") comparision_sign = LESS;
            if(checked == "==") comparision_sign = EQUAL;
            if(checked == "!=") comparision_sign = NOT_SAME;
            if(checked == ">=") comparision_sign = GREATER_OR_EQUAL;
            if(checked == "<=") comparision_sign = LESS_OR_EQUAL;
            break;
        }
        else comparision_sign = UNKNOWN_SIGN;
    }
    if(comparision_sign == UNKNOWN_SIGN) return true;
    int value = 0;
    enum {NUMERIC, STRING} val_type;
    std::string s_value;
    auto second_argument = std::find_if(condition.begin() + sign_found, condition.end(), [](char c)->bool{return isdigit(c);});
    if(second_argument != condition.end()) {value = stoi(std::string(second_argument, condition.end())); val_type = NUMERIC;}
    else
    {
        auto s_second_argument = std::find_if(condition.begin() + sign_found, condition.end(), [](char c)->bool{return isalpha(c);});
        if(s_second_argument != condition.end()) {s_value = std::string(s_second_argument, condition.end()); val_type = STRING;}
    }
    if(memory != nullptr)
    {
        int v1;
        try {v1 = memory->at(first_arg_to_check);}
        catch(const std::out_of_range& oou){return false;}
        if(val_type == NUMERIC)
        {
            if(comparision_sign == GREATER         ) return v1 >  value;
            if(comparision_sign == LESS            ) return v1 <  value;
            if(comparision_sign == EQUAL           ) return v1 == value;
            if(comparision_sign == NOT_SAME        ) return v1 != value;
            if(comparision_sign == GREATER_OR_EQUAL) return v1 >= value;
            if(comparision_sign == LESS_OR_EQUAL   ) return v1 <= value;
        }
        if(val_type == STRING)
        {
            int v2;
            try {v2 = memory->at(s_value);}
            catch(const std::out_of_range& oou){return false;}
            if(comparision_sign == GREATER         ) return v1 >  v2;
            if(comparision_sign == LESS            ) return v1 <  v2;
            if(comparision_sign == EQUAL           ) return v1 == v2;
            if(comparision_sign == NOT_SAME        ) return v1 != v2;
            if(comparision_sign == GREATER_OR_EQUAL) return v1 >= v2;
            if(comparision_sign == LESS_OR_EQUAL   ) return v1 <= v2;
        }
        return false;
    }
    else return false;
}
void NpcManager::setPlayerStats(std::unordered_map<std::string, unsigned int>* p_mem)
{
    memory = p_mem;
}
void NpcManager::drawActions()
{
    for(auto action : current_actions)
    {
        if(action.type_action == 0)
            window.setNPCString(action.text);
        if(action.type_action == 9)
            window.addString(action.text);
    }
}
void NpcManager::getActions(NPC& npc, const tree<Action>::sibling_iterator deep, bool first)
{
    print();
    window.clear();
    current_actions.clear();
    int depth = npc.dialog.number_of_children(deep);
    if(first)
        current_actions.push_back((*npc.dialog.begin()));
    if(!first)
        current_actions.push_back((*npc.dialog.child(deep,0)));
    if(depth == 1)
    {
        current_actions.clear();
        current_actions.push_back((*npc.dialog.child(deep,0)));
        window.setNPCString((*npc.dialog.child(deep,0)).text);
        if(window.buttonHold(150))
        {
            npc.c_node = npc.dialog.begin();
            state = NO_TALK;
        }
        return;
    }
    int not_valid=0;
    for(int i = (first)?(0):(1);i<depth;++i)
    {
        if((*npc.dialog.child(deep,i)).has_condition)
        {
            bool cond = checkConditions((*npc.dialog.child(deep,i)).ad_info.helpstring);
            if(cond) current_actions.push_back((*npc.dialog.child(deep,i)));
            else     not_valid++;
            if(cond == false && depth == 2)
            {
                current_actions.clear();
                window.setNPCString((*npc.dialog.child(deep,0)).text);
                if(window.buttonHold(250))
                {
                    npc.c_node = npc.dialog.begin();
                    state = NO_TALK;
                }
                return;
            }
        }
        else current_actions.push_back((*npc.dialog.child(deep,i)));
	}
	drawActions();
	int choice = -1;
    if(first) choice = window.selectAnwser(0);
    else      choice = window.selectAnwser(1 + not_valid);
    if(choice != -1)
    {
        current_actions.clear();
        state = NOW_TALKING;
        npc.c_node = npc.dialog.child(deep, choice);
    }
}
void NpcManager::addNPC(NPC npc){
	m_npcs.push_back(npc);
}
void NpcManager::print()
{
    int id = 0;
    for(auto dial : current_actions)
    {
        std::wcout << "Text:" << dial.text <<" id:" << id<< endl;
        id++;
    }
    std::cout << "size:" << current_actions.size() << endl;
}
std::size_t NpcManager::countNPC() {
	return m_npcs.size();
}
int NpcManager::nearNPC(sf::Vector2u v)const{
	std::vector<NPC>::const_iterator it = std::find_if(m_npcs.begin(),m_npcs.end(),
	std::bind(_near<NPC>,std::placeholders::_1,v));
	if(it!=m_npcs.end()) return it->id;
    else                 return -1;
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
    Action _tmp(wide_string<std::wstring>(txt), NPC_ONLY_TALK, HelpInfo(), false);
    if(first) root = npc.dialog.insert(npc.dialog.begin(), _tmp);
    if(reply->FirstChildElement("player") != NULL)
    {
        TiXmlElement *player = reply->FirstChildElement("player");
        if(first) sit = root;
        else      sit = go_deeper;
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
