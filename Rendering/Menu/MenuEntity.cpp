#include "MenuEntity.hpp"

MenuEntity::MenuEntity(string texture_file, Point origin)
	: Entity::Entity()
{
	int width, height;

	rect.x = origin.x;
	rect.y = origin.y;

	if(texture != "")
	{
		texture = assetFactory->Instance().getAsset<SDL_Texture>(texture_file);
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		rect.w = (double) width;
		rect.h = (double) height;
	}
}