#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <cmath>

template<class T>
class Pair
{
public:
	T x, y;

	Pair(){
		this->x = 0;
		this->y = 0;
	}

	Pair(T x, T y){
		this->x = x;
		this->y = y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pair& pair)
	{
		os << "(" << pair.x << ", " << pair.y << ")";
		return os;
	}
};

typedef Pair<double> Point;
typedef Pair<int>    Size;

double distance(Point a, Point b);

#endif