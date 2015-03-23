#include "DataReader.hpp"
#include "../Resources/Utils.hpp"
#include "../Resources/tinyxml/tinyxml.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
/*
Struktura dialogów to
<reply>
<player>
<reply>
I tak w kółko, reply może być tylko jedne na dialog, natomiast player(odpowiedzi) może być wiele
Możliwe atrybuty dla reply
        0(ONLY_TALK), 1(GIVE_ITEM), 2(GET_ITEM), 3(GIVE_QUEST)
        4(VALID_QUEST), 5(FIGHT), 6(TRADE), i 2 pola są zarezerwowane na przyszłość
Możliwe atrybuty dla player
        9(RESPONSE) -> 17
Możliwe parmetry dla reply action, który określa atrybut, oraz params, przez który
przekazujemy parametry po przecinku (params="23,42,12,55") które są parsowane i pakowane w vector intów

Możliwe parametry dla player, condition, czyli warunek który musi być spełniony
Aby opcja była widoczna
*/
void DataRead::read(TiXmlElement* ent)
{
    current_processed.clean();
	current_processed.text = wide_string<std::wstring>(ent->Attribute("text"));
	std::string parsed_node_type = ent->Value();
    if(parsed_node_type == "reply")
    {
        if(ent->Attribute("action") != NULL)
        {
            current_processed.type_action = (ATYPE)(atoi(ent->Attribute("action")));
            std::string params;
            if(ent->Attribute("params") != NULL)
                params = ent->Attribute("params");
            switch(current_processed.type_action)
            {
                case NPC_GIVE_ITEM:
                    parseParams(params,current_processed.ad_info.additdata,',');
                break;
                case NPC_GET_ITEM:
                    parseParams(params,current_processed.ad_info.additdata,',');
                break;
                case NPC_GIVE_QUEST:
                    if(ent->Attribute("questname") != NULL)
                        current_processed.ad_info.helpstring = ent->Attribute("questname");
                break;
                case NPC_TRADE:
                    parseParams(params,current_processed.ad_info.additdata,',');
                break;
            }
	    }
    }
    if(parsed_node_type == "player")
    {
        ATYPE type;
        if(ent->Attribute("action") == NULL)
            type = PLAYER_RESPONSE;
        else if(ent->Attribute("action") != NULL)
        {
            type = (ATYPE)atoi(ent->Attribute("action"));
            if(type < PLAYER_RESPONSE)
                type = ACTION_NOT_VALID;
        }
        current_processed.type_action = type;
        if(ent->Attribute("condition") != NULL)
            current_processed.ad_info.helpstring = ent->Attribute("condition");
    }
}
void DataRead::parseParams(const std::string params, std::vector<int>& v, char delim)
{
    std::stringstream ss(params);
    std::string item;
    while (std::getline(ss, item, delim)) {
        v.push_back(std::stoi(item));
    }
}
Action DataRead::get()
{
    return current_processed;
}
