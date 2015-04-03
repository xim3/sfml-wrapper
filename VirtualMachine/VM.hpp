#pragma once
#include "../NpcManager/NpcManager.hpp"
#include "../Resources/Utils.hpp"
#include "../DialogSystem/TextWindow.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
enum MSTATE
{
 NO_DIAL,
 NOW_DIAL,
 BEGIN_DIAL,
 IDLE_NO_EVENT=128
};
class Machine
{
public:
    Machine(sf::Vector2u&, TextWindow&, IDataRead&);
    void setDepth(size_t);
    const std::vector<Action>& getProcessed();
    void setProcessed(std::vector<Action>);
    void addAction(Action);
    void clean();
    void printstate();
    void setState(MSTATE);
    bool setupNpcSystem(std::string);
    MSTATE getState();
private:
    std::vector<Action>       processed;
    size_t                    depth;
    TextWindow                &window;
    MSTATE                    machine_state;
    NpcManager                npc_mgr;
};
