#include "Point.hpp"

double distance(Point a, Point b)
{
	double deltaX = a.x - b.x;
	double deltaY = a.y - b.y;
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

Orientation orientation(Point a, Point b, Point c)
{
	int val = (b.y - a.y) * (c.x - b.x) -
			  (b.x - a.x) * (c.y - b.y);

	if(val == 0)
	{
		return COLINEAR;
	}

	if(val > 0)
	{
		return CLOCKWISE;
	}
	else
	{
		return COUNTER_CLOCKWISE;
	}
}