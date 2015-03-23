#include "NPC.hpp"
#include <iostream>
NPC::NPC() {}
NPC::NPC(std::string _name, unsigned int _id, unsigned int _gid, sf::Vector2u _pos)
: name(_name)
, x(_pos.x)
, y(_pos.y)
, id(_id)
, gid(_gid)
{
    c_node = dialog.begin();
}
bool NPC::operator==(const NPC& r){
    if(this->id == r.id)
        return true;
    else return false;
}
void NPC::print_tree()
{
    if(!dialog.is_valid(dialog.begin())) return;
    int rootdepth=dialog.depth(dialog.begin());
    std::cout << "-----" << std::endl;
    tree<Action>::pre_order_iterator it,end;
    it = dialog.begin();
    end = dialog.end();
    while(it!=end)
    {
        for(int i=0; i<dialog.depth(it)-rootdepth; ++i)
        std::cout << "  ";
        std::wcout << (*it).text;
        std::wcout << " ATYPE:" <<(*it).type_action;
        std::cout<< " Condition:" << (*it).ad_info.helpstring << std::endl;
        ++it;
    }
    std::cout << "-----" << std::endl;
}

