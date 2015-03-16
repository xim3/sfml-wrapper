#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
class Player : public Entity
{
public:
    Player(unsigned int x=32,unsigned int y=32);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

};

