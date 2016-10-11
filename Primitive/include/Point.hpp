#ifndef PAIR_H
#define PAIR_H

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
};

typedef Pair<double> Point;
typedef Pair<int>    Size;

#endif