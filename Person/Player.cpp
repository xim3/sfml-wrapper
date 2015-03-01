#pragma once
#include "Player.hpp"
Player::Player() : Person() {}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	anitex.draw(target,states);
}
