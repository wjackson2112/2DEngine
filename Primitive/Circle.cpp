#include "Circle.hpp"

#include "Rect.hpp"
#include "Line.hpp"

Circle::Circle()
{
	mCenter = Point(0,0);
	mRadius = 0;
}
Circle::Circle(Point center, int radius)
{
	mCenter = center;
	mRadius = radius;
}

int  Circle::radius()
{
	return mRadius;
}
void Circle::setRadius(int radius)
{
	mRadius = radius;
}

Point Circle::center()
{
	return mCenter;
}
void  Circle::setCenter(Point center)
{
	mCenter = center;
}

bool  Circle::contains(Point point)
{
	if(distance(point, mCenter) < mRadius)
	{
		return true;
	}
	return false;
}
bool  Circle::intersects(Shape& shape)
{
	if(dynamic_cast<Line*>(&shape))
	{
		Line* line = (Line*) &shape;

		return line->intersects(*this);
	}
	else if(dynamic_cast<Rect*>(&shape))
	{
		Rect* rect = (Rect*) &shape;

		return rect->intersects(*this);
	}
	else if(dynamic_cast<Circle*>(&shape))
	{
		Circle* other = (Circle*) &shape;

		if(radius() + other->radius() > distance(center(), other->center()))
		{
			return true;
		}
		return false;
	}
}

std::ostream &operator<<(std::ostream &os, const Circle& circle)
{
	os << "<Circle " << &circle << ": mCenter=" << circle.mCenter << ", mRadius=" << circle.mRadius << ">";
	return os;
}