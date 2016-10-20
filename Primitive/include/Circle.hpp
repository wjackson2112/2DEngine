#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Shape.hpp"
#include "Point.hpp"

class Circle : public Shape
{
protected:
	Point mCenter;
	int mRadius;

public:
	Circle();
	Circle(Point center, int radius);

	int  radius();
	void setRadius(int radius);

	Point center();
	void  setCenter(Point center);

	bool  contains(Point point);
	bool  intersects(Shape& shape);

	friend std::ostream &operator<<(std::ostream &os, const Circle& circle);
};

#endif