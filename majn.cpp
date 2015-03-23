	

#include <iostream>
#include <string>
#include "Resources/tinyxml/tinyxml.h"
#include "Resources/easylogging++.h"
#include "tree.hh"
#include <string>
using namespace std;
tree<string> dialog;
void print_tree(const tree<std::string>& tr, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
{
    if(!tr.is_valid(it)) return;
    int rootdepth=tr.depth(it);
    std::cout << "-----" << std::endl;
    while(it!=end)
    {
        for(int i=0; i<tr.depth(it)-rootdepth; ++i)
        std::cout << "  ";std::cout << (*it) << std::endl << std::flush;
        ++it;
    }
    std::cout << "-----" << std::endl;
}
void talk(const tree<std::string>& tr, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
{
    if(!tr.is_valid(it)) return;
    int rootdepth=tr.depth(it);
    std::cout << "-----" << std::endl;
    while(it!=end)
    {
        for(int i=0; i<tr.depth(it)-rootdepth; ++i)
        std::cout << "  ";
        std::cout << (*it) << std::endl << std::flush;
        ++it;
    }
    std::cout << "-----" << std::endl;
}
INITIALIZE_EASYLOGGINGPP
void newNpc(std::string name, TiXmlElement* root)
{
   TiXmlElement* npc = new TiXmlElement("npc");
   npc->SetAttribute("name",name.c_str());
}
using namespace std;
/*
MAGIC, DON`T FCKI*G TOUCH.
Ja to napisałem, ale za ch*ja nie mam pojęcia jakim cudem to działa.
Ot, chwilowy przypływ geniuszu :D
Pierwsze dziecko węzła to zawsze odpowiedź NPC
*/
void load_tree(TiXmlElement* npc, tree<string>::sibling_iterator go_deeper, bool first)
{
    TiXmlElement *reply = npc;
    tree<string>::iterator root;
    tree<string>::sibling_iterator sit;
    if(first)
        root = dialog.insert(dialog.begin(), reply->Attribute("text"));
    // jeśli player może coś odpowiedzieć
    if(reply->FirstChildElement("player") != NULL)
    {
       TiXmlElement *player = reply->FirstChildElement("player");
       if(first)
         sit = root;
         else
         sit = go_deeper;
       //przeiteruj po odpowiedziach
       while(player)
        {
            auto p_reply = dialog.append_child(sit, player->Attribute("text"));
                // jeśli NPC będzie mówił dalej
                if(player->FirstChildElement("reply") != NULL)
                {
                    dialog.append_child(p_reply, player->FirstChildElement("reply")->Attribute("text"));
                    //rekurencyjnie jedziem dalej
                    load_tree(player->FirstChildElement("reply"), p_reply, 0);
                }
                player = player->NextSiblingElement("player");
     
            }
        }
        else return;
    }
    void talky(const tree<std::string>::sibling_iterator deep, bool first)
    {
        int depth = dialog.number_of_children(deep);
        int depth1 = dialog.number_of_siblings(deep);
        std::cout << "Odpowiedzi:" << depth << endl;
        if(!first)
        std::cout << "NPC: "<<*dialog.child(deep,0) << endl;
        if(depth == 1)
            return;
        int i;
        int choice = 0;
        if(first)
            i = 0;
        else
            i = 1;
        for(; i<depth;++i)
        {
            std::cout << i << ":" << *dialog.child(deep, i) << endl;
        }
        std::cin >> choice;
        tree<std::string>::sibling_iterator c;
        c = dialog.child(deep, choice);
        talky(c,0);
     
    }
    int main()
    {
        TiXmlDocument doc("dialogs.xml");
        doc.LoadFile();
        TiXmlElement *f = doc.FirstChildElement("dialogs");
        TiXmlElement *jan = f->FirstChildElement("npc");
        load_tree(jan->FirstChildElement("reply"), dialog.begin(), 1);
        print_tree(dialog, dialog.begin(), dialog.end());
        //talk(dialog, dialog.begin(), dialog.end());
        tree<string>::iterator i = dialog.begin();
        std::cout << "NPC: "<<(*i) << endl;
        talky(i,1);
     
    }

