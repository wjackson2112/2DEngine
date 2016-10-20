#include "Circle.hpp"

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

}

std::ostream &operator<<(std::ostream &os, const Circle& circle)
{
	os << "<Circle " << &circle << ": mCenter=" << circle.mCenter << ", mRadius=" << circle.mRadius << ">";
	return os;
}