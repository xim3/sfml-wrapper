#pragma once
Player::Player(unsigned int x,unsigned int y) : Person(x,y) {}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	anitex.draw(target,states);
}
