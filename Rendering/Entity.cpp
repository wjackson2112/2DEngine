#include "Entity.hpp"

Entity::Entity()
{
	setOrigin(Point(0,0));
}

Entity::Entity(string spriteFile)
{
	sprites.push_back(AssetManager::Instance().getAsset<Sprite>(spriteFile));
	setOrigin(Point(0,0));
	setSize(sprites[0].size);
}

bool Entity::render(Camera* camera)
{
	if(camera == NULL)
	{
		if(sprites[0].render(*this) != true)
		{
			return false;
		}
		return true;
	}

	if(sprites[0].render(camera->apply(*this)) != true)
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
	//If they don't have the same number of sprites, they can't the same
	if(entity1.sprites.size() != entity2.sprites.size())
	{
		return false;
	}

	//They should also be the same sprites in the same order
	for(int i = 0; i < entity1.sprites.size(); i++)
	{
		if(entity1.sprites[i] != entity2.sprites[i])
		{
			return false;
		}
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