#pragma once
template<class T>
bool xyCompare(const T& some, const sf::Vector2u &vct)
{
	if(some.x == vct.x && some.y == vct.y)
		return true;
	else
		return false;
}
template<class T, class T1>
bool xyCompare(const T& first, const T& second)
{
	if(first.x == second.x && first.y == second.y)
		return true;
	else
		return false;
}
