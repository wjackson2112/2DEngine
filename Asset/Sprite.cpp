#include "Sprite.hpp"	

Sprite::Sprite()
{
	texture = NULL;
}

Sprite::Sprite(SDL_Texture* texture)
{
	int w,h;

	this->texture = texture;

	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
	setSize(Size(w, h));
}

void Sprite::render()
{
	SDL_Rect dstrect; 
	dstrect.x = origin().x;
	dstrect.y = origin().y;
	dstrect.w = size().x;
	dstrect.h = size().y;
	SDL_RenderCopy(WindowManager::Instance().renderer, texture, NULL, &dstrect);
}

void Sprite::scale(double scaleFactor)
{
	setSize(Size(size().x * scaleFactor, size().y * scaleFactor));
}

void Sprite::scaleToWidth(int width)
{
	double scaleFactor = (double) width / (double) size().x;

	scale(scaleFactor);
}

void Sprite::scaleToHeight(int height)
{
	double scaleFactor = (double) height / (double) size().y;

	scale(scaleFactor);
}