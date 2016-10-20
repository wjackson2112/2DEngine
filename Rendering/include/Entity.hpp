#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>

#include "AssetManager.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"

class Entity : public Rect
{
protected:
	Sprite sprite;
public:
	Entity();
	Entity(string spriteFile);

	bool render(Camera* camera);
	void update(int frameTime);

	friend bool operator==(const Entity& entity1, const Entity& entity2);
	friend bool operator!=(const Entity& entity1, const Entity& entity2);
};



#endif