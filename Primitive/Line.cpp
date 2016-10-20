#include "Line.hpp"

Line::Line()
{
	mA = Point(0,0);
	mB = Point(0,0);
}
Line::Line(Point a, Point b)
{
	mA = a;
	mB = b;
}

Point Line::a()
{
	return mA;
}
Point Line::b()
{
	return mB;
}
void  Line::setA(Point a)
{
	mA = a;
}
void  Line::setB(Point b)
{
	mB = b;
}

double Line::length()
{
	distance(mA, mB);
}

bool  Line::contains(Point point)
{
	if(distance(mA, point) + distance(point, mB) == distance(mA, mB))
	{
		return true;
	}
	return false;
}
bool  Line::intersects(Shape& shape)
{

}

std::ostream &operator<<(std::ostream &os, const Line& line)
{
	os << "<Line " << &line << ": mA=" << line.mA << ", mB=" << line.mB << ">";
	return os;
}