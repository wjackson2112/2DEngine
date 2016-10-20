#include "Point.hpp"

double distance(Point a, Point b)
{
	double deltaX = a.x - b.x;
	double deltaY = a.y - b.y;
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}