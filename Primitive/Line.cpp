#include "Line.hpp"
#include "Rect.hpp"
#include "Circle.hpp"

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
bool  Line::intersects(Shape* shape)
{

	if(dynamic_cast<Line*>(shape))
	{
		Line* other = (Line*) shape;

		//Calculate the 4 orientations
		Orientation o1 = orientation(a(), b(), other->a());
		Orientation o2 = orientation(a(), b(), other->b());
		Orientation o3 = orientation(other->a(), other->b(), a());
		Orientation o4 = orientation(other->a(), other->b(), b());

		//Check that the orientations are opposite
		if(o1 != o2 && o3 != o4)
		{
			return true;
		}

		//Check special cases
		if(o1 == COLINEAR && Line(a(),b()).contains(other->a()))
		{
			return true;
		}
		else if(o2 == COLINEAR && Line(a(),b()).contains(other->b()))
		{
			return true;
		}
		else if(o3 == COLINEAR && Line(other->a(),other->b()).contains(a()))
		{
			return true;
		}
		else if(o4 == COLINEAR && Line(other->a(),other->b()).contains(b()))
		{
			return true;
		}

		return false;
	}
	else if(dynamic_cast<Rect*>(shape))
	{
		Rect* rect = (Rect*) shape;

		Line top, right, bottom, left;

		//If the line is completely inside the rectangle
		if(rect->contains(a()) && rect->contains(b()))
		{
			return true;
		}

		top = rect->top();
		right = rect->right();
		bottom = rect->bottom();
		left = rect->left();

		//If the line intesects any of the rectangles edges
		if(intersects(&top) ||
		   intersects(&right) ||
		   intersects(&bottom) ||
		   intersects(&left))
		{
			return true;
		}

		return false;
	}
	else if(dynamic_cast<Circle*>(shape))
	{
		Circle* circle = (Circle*) shape;

		if(distance(circle->center(), *this) < circle->radius())
		{
			return true;
		}

		return false;
	}
}

std::ostream &operator<<(std::ostream &os, const Line& line)
{
	os << "<Line " << &line << ": mA=" << line.mA << ", mB=" << line.mB << ">";
	return os;
}

double distance(Point point, Line line)
{

	//https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
	double x0 = point.x;
	double y0 = point.y;
	double x1 = line.a().x;
	double y1 = line.a().y;
	double x2 = line.b().x;
	double y2 = line.b().y;


	if((x0 < x1 && x0 < x2) ||
	   (x0 > x1 && x0 > x2) ||
	   (y0 < y1 && y0 < y2) ||
	   (y0 > y1 && y0 > y2))
	{
		double distToA = distance(point, line.a());
		double distToB = distance(point, line.b());
		if(distToA < distToB)
		{
			return distToA;
		}
		else
		{
			return distToB;
		}
	}
	else
	{
		double numer = abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1);
		double denom = sqrt(pow(y2-y1,2) + pow(x2-x1,2));

		return numer/denom;
	}
}