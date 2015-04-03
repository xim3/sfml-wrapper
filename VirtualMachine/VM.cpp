#include "VM.hpp"
using namespace std;
Machine::Machine(sf::Vector2u& player, TextWindow& win, IDataRead& rdr)
: window(win)
, machine_state(IDLE_NO_EVENT)
, npc_mgr(rdr, window, player)
{

}
void Machine::setProcessed(std::vector<Action> act)
{
    processed = act;
}
const std::vector<Action>& Machine::getProcessed()
{
    return processed;
}
void Machine::setDepth(size_t s)
{
    depth = s;
}
void Machine::addAction(Action act)
{
    if(processed.size() < depth)
        processed.push_back(act);
}
void Machine::clean()
{
    processed.clear();
}
void Machine::printstate()
{
    for(int i=0;i<80;++i)std::cout<< "=";
    std::cout << "\n";
    int i=0;
    for(auto action : processed)
    {
        //std::cout << "Size:" << processed.size() << endl;
        std::wcout << i << ":"<< action.text << endl;
        ++i;
    }
    std::cout << "Size of:" << processed.size() << "\n";
    std::cout << "Stan:" << machine_state << "\n";
    for(int i=0;i<80;++i)std::cout << "=";
    std::cout << "\n";
}
void Machine::setState(MSTATE _st)
{
    machine_state = _st;
}
MSTATE Machine::getState()
{
    return machine_state;
}
bool Machine::setupNpcSystem(std::string path)
{
    return npc_mgr.loadDialogs(path);
}
