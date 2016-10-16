#include "Rect.hpp"

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
	if(point.x >= mOrigin.x &&
	   point.x <= opposite().x &&
	   point.y >= mOrigin.y &&
	   point.y <= opposite().y)
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

std::ostream &operator<<(std::ostream &os, const Rect& rect)
{
	os << "<Rect " << &rect << ": mOrigin=" << rect.mOrigin << ", mSize=" << rect.mSize << ">";
	return os;
}