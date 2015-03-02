#include "Player.hpp"
#include "Entity.hpp"

Player::Player(unsigned int x,unsigned int y) 
: Entity(x,y)
{
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	anitex.draw(target,states);
}
