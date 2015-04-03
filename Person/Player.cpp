#include "Player.hpp"
#include "Entity.hpp"
#include <stdexcept>
Player::Player(unsigned int x,unsigned int y)
: Entity(x,y)
{
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	anitex.draw(target,states);
}
void Player::addStat(std::string name, unsigned value)
{
    stats[name] = value;
}
int Player::getStat(std::string name)
{
    unsigned int value;
	try
	{
        value = stats.at(name);
	}
	catch(const std::out_of_range& oou)
	{
	    return -1;
	}
	return value;
}
std::unordered_map<std::string, unsigned int>*
Player::getFullStats()
{
    return &stats;
}
