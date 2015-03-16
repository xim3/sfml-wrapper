#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <limits>
template<class T>
bool xyCompare(const T& first, const sf::Vector2u &vct)
{
	if(first.x == vct.x && first.y == vct.y)
		return true;
	else
		return false;
}
template<class T, class T1>
bool xyCompare(const T& first, const T1& second)
{
	if(first.x == second.x && first.y == second.y)
		return true;
	else
		return false;
}

template<class T>
bool xyCompareFloat(const T& first, const sf::Vector2f vct)
{
    printf("Vx:%i(%f) Vy:%i(%f) firstx:%i firsty:%i\n", (unsigned int)vct.x,vct.x,(unsigned int)vct.y,vct.y,first.x,first.y);
    if(static_cast<unsigned int>(vct.x) == first.x && static_cast<unsigned int>(vct.y) == first.y)
        return true;
    else
        return false;
}
template<class T>
bool _near(const T& obj, const sf::Vector2u &vct)
{
	if( (obj.x == vct.x 	&& obj.y == vct.y    ) ||
	    (obj.x == vct.x     && obj.y == vct.y - 1) ||
	    (obj.x == vct.x - 1 && obj.y == vct.y - 1) ||
	    (obj.x == vct.x - 1 && obj.y == vct.y    ) ||
	    (obj.x == vct.x - 1 && obj.y == vct.y + 1) ||
	    (obj.x == vct.x     && obj.y == vct.y + 1) ||
	    (obj.x == vct.x + 1 && obj.y == vct.y - 1) ||
	    (obj.x == vct.x + 1 && obj.y == vct.y    ) ||
        (obj.x == vct.x + 1 && obj.y == vct.y + 1) )
        return true;
	else
		return false;
}
