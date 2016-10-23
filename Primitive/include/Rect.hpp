#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Shape.hpp"
#include "Line.hpp"
#include "Point.hpp"

typedef enum
{
	ORIGIN,
	CENTER,
	OPPOSITE
} Anchor;

class Rect : public Shape
{
protected:
	Point mOrigin;
	Size mSize;

public:
	Rect();
	Rect(Point origin, Size size);

	Point origin();
	void  setOrigin(Point origin);

	Size  size();
	void  setSize(Size size);
	void  setSize(Size size, Anchor anchor);

	Point center();
	void  setCenter(Point center);

	Point opposite();
	void  setOpposite(Point opposite);

	bool  contains(Point point);

	SDL_Rect toSDLRect();
	bool  intersects(Shape& shape);

	Line  right();
	Line  top();
	Line  left();
	Line  bottom();

	friend std::ostream &operator<<(std::ostream &os, const Rect& rect);
};

#endif