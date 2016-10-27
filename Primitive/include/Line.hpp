#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "Shape.hpp"
#include "Point.hpp"


class Line : public Shape
{
protected:
	Point mA, mB;

public:
	Line();
	Line(Point a, Point b);

	Point a();
	Point b();
	void  setA(Point a);
	void  setB(Point b);

	double length();

	bool  contains(Point point);
	bool  intersects(Shape* shape);

	friend std::ostream &operator<<(std::ostream &os, const Line& line);
};

double distance(Point point, Line line);

#endif