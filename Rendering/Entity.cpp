#include "Entity.hpp"

Entity::Entity()
{
	setOrigin(Point(0,0));
}

Entity::Entity(string spriteFile)
{
	sprite = AssetManager::Instance().getAsset<Sprite>(spriteFile);
	setOrigin(Point(0,0));
	setSize(sprite.size);
}

bool Entity::render(Camera* camera)
{
	if(camera == NULL)
	{
		if(sprite.render(*this) != true)
		{
			return false;
		}
		return true;
	}

	if(sprite.render(camera->apply(*this)) != true)
	{
		return false;
	}

	return true;
}

void Entity::update(int frameTime)
{

}

bool operator==(const Entity& entity1, const Entity& entity2)
{
	if(entity1.sprite != entity2.sprite)
	{
		return false;
	}

	return true;
}

bool operator!=(const Entity& entity1, const Entity& entity2)
{
	if(entity1 == entity2)
	{
		return false;
	}
	return true;
}