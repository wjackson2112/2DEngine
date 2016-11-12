#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Shape.hpp"

class Collider;

class ColliderParent
{
public:
	Collider* collider;

	virtual void colliderCallback(ColliderParent *, Shape* shape) = 0;
	virtual void negotiateCollision(ColliderParent *, Shape* shape) = 0;
};

class Collider
{
	Shape* mShape;
	int mPriority;
	ColliderParent* mParent;

public:

	Collider(Shape* shape, int priority, ColliderParent* parent)
		: mShape{shape}, mPriority{priority}, mParent(parent){};

	~Collider()
	{
		// delete mShape;
	}

	void resolveCollision(Collider collider)
	{
		collider.mParent->colliderCallback(mParent, mShape);
		mParent->colliderCallback(collider.mParent, collider.mShape);
	}

	friend bool intersects(Collider a, Collider b)
	{
		return a.mShape->intersects(b.mShape);
	}

	friend void resolveCollisions(Collider a, Collider b)
	{
		if(intersects(a,b))
		{
			if(a.mPriority > b.mPriority)
			{
				a.resolveCollision(b);
			}
			else if(a.mPriority < b.mPriority)
			{
				b.resolveCollision(a);
			}
			else
			{
				while(intersects(a,b))
				{
					a.mParent->negotiateCollision(b.mParent, b.mShape);
					b.mParent->negotiateCollision(a.mParent, a.mShape);
				}
			}
		}
	}

	void operator=(const Collider &collider)
	{
		mShape = collider.mShape;
		mPriority = collider.mPriority;
		mParent = collider.mParent;
	}
};



#endif