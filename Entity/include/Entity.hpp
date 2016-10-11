#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
	virtual void render() = 0;
	virtual void update(int frameTime) = 0;
};

#endif