#include "Rect.hpp"

#include "Circle.hpp"

Rect::Rect()
{
	mOrigin = Point(0,0);
	mSize 	= Size(0,0);
}

Rect::Rect(Point origin, Size size)
{
	mOrigin = origin;
	mSize 	= size;
}

Point Rect::origin()
{
	return mOrigin;
}

void  Rect::setOrigin(Point origin)
{
	mOrigin = origin;
}

Size  Rect::size()
{
	return mSize;
}

void  Rect::setSize(Size size)
{
	mSize = size;
}

void  Rect::setSize(Size size, Anchor anchor)
{
	switch(anchor)
	{
		case ORIGIN:
			setSize(size);
		case CENTER:
		{
			Point c = center();
			setSize(size);
			setCenter(c);
			break;
		}
		case OPPOSITE:
		{
			Point o = opposite();
			setSize(size);
			setOpposite(o);
			break;
		}
	}
}

Point Rect::center()
{
	return Point(mOrigin.x + mSize.x/2, mOrigin.y + mSize.y/2);
}

void  Rect::setCenter(Point center)
{
	mOrigin = Point(center.x - mSize.x/2, center.y - mSize.y/2);
}

Point Rect::opposite()
{
	return Point(mOrigin.x + mSize.x, mOrigin.y + mSize.y);
}

void  Rect::setOpposite(Point opposite)
{
	mOrigin = Point(opposite.x - mSize.x, opposite.y - mSize.y);
}

bool  Rect::contains(Point point)
{
	if(point.x > mOrigin.x &&
	   point.x < opposite().x &&
	   point.y > mOrigin.y &&
	   point.y < opposite().y)
	{
		return true;
	}

	return false;
}

SDL_Rect Rect::toSDLRect()
{
	SDL_Rect sdl_rect;
	sdl_rect.x = mOrigin.x;
	sdl_rect.y = mOrigin.y;
	sdl_rect.w = mSize.x;
	sdl_rect.h = mSize.y;
	return sdl_rect;
}

bool Rect::intersects(Shape* shape)
{
	if(dynamic_cast<Rect*>(shape))
	{
		SDL_Rect a = this->toSDLRect();
		SDL_Rect b = ((Rect*) shape)->toSDLRect();

		return SDL_HasIntersection(&a, &b);
	}
	else if(dynamic_cast<Line*>(shape))
	{
		Line* line = (Line*) shape;

		return line->intersects(this);
	}
	else if(dynamic_cast<Circle*>(shape))
	{
		Circle* circle = (Circle*) shape;

		//If the circle's center is inside, then intersection
		if(contains(circle->center()))
		{
			return true;
		}

		//If any side intersects the circle, then intersection
		if(top().intersects(circle) ||
		   left().intersects(circle) ||
		   right().intersects(circle) ||
		   bottom().intersects(circle))
		{
			return true;
		}

		Rect wideBoundingRect = Rect(Point(origin().x-circle->radius(),
								           origin().y-circle->radius()),
								      Size(size().x+circle->radius()*2,
								           size().y+circle->radius()*2));

		//If center in box that is size of box + radius of circle
		if(wideBoundingRect.contains(circle->center()))
		{
			//If in left box
			Rect leftBoundingRect = Rect(Point(origin().x - circle->radius(),
				                               origin().y),
										  Size(circle->radius(),
										  	   size().y));
			if(leftBoundingRect.contains(circle->center()))
			{
				return true;
			}

			//If in right box
			Rect rightBoundingRect = Rect(Point(opposite().x,
				                               origin().y),
										  Size(circle->radius(),
										  	   size().y));
			if(rightBoundingRect.contains(circle->center()))
			{
				return true;
			}

			//If in upper box
			Rect upperBoundingRect = Rect(Point(origin().x,
				                               origin().y - circle->radius()),
										  Size(size().x,
										  	   circle->radius()));
			if(upperBoundingRect.contains(circle->center()))
			{
				return true;
			}

			//If in lower box
			Rect lowerBoundingRect = Rect(Point(origin().x,
				                               opposite().y),
										  Size(size().x,
										  	   circle->radius()));
			if(lowerBoundingRect.contains(circle->center()))
			{
				return true;
			}


			//If inside rounded corners
			if(distance(pointA(), circle->center()) < circle->radius() ||
			   distance(pointB(), circle->center()) < circle->radius() ||
			   distance(pointC(), circle->center()) < circle->radius() ||
			   distance(pointD(), circle->center()) < circle->radius())
			{
				return true;
			}
		}

		return false;
	}

	return false;
}

// B-A
// | |
// C-D

Point Rect::pointA()
{
	return Point(opposite().x, origin().y);
}

Point Rect::pointB()
{
	return origin();
}

Point Rect::pointC()
{
	return Point(origin().x, opposite().y);
}

Point Rect::pointD()
{
	return opposite();
}

Line  Rect::right()
{
	return Line(pointA(), opposite());
}

Line  Rect::top()
{
	return Line(origin(), pointA());
}

Line  Rect::left()
{
	return Line(pointC(), origin());
}

Line  Rect::bottom()
{
	return Line(opposite(), pointC());
}

std::ostream &operator<<(std::ostream &os, const Rect& rect)
{
	os << "<Rect " << &rect << ": mOrigin=" << rect.mOrigin << ", mSize=" << rect.mSize << ">";
	return os;
}