#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Entity.hpp"
class Player : public Entity
{
public:
    Player(unsigned int x=32,unsigned int y=32);
    void addStat(std::string, unsigned int);
    int  getStat(std::string);
    std::unordered_map<std::string, unsigned int>* getFullStats();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::unordered_map<std::string, unsigned int> stats;
};

