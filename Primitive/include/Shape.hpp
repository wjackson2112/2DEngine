#ifndef SHAPE_H
#define SHAPE_H

#include "Point.hpp"

class Shape
{
public:
	virtual bool intersects(Shape& shape) = 0;
	virtual bool contains(Point point) = 0;
};

#endif