#ifndef COLLIDER_H
#define COLLIDER_H

#include <SDL2/SDL.h>
#include <iostream>

class ColliderParent
{
public:
	virtual void colliderCallback(ColliderParent *) = 0;
	virtual void negotiateCollision(ColliderParent *) = 0;
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
		collider.mParent->colliderCallback(mParent);
		mParent->colliderCallback(collider.mParent);
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
					a.mParent->negotiateCollision(b.mParent);
					b.mParent->negotiateCollision(a.mParent);
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