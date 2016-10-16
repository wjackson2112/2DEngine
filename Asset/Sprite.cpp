#include "Sprite.hpp"	

Sprite::Sprite()
{
	mTexture = NULL;
}

Sprite::Sprite(SDL_Texture* texture)
{
	int w,h = 0;

	mTexture = texture;

	if(SDL_QueryTexture(mTexture, NULL, NULL, &w, &h) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	size = Size(w,h);
}

void Sprite::render(Rect destRect)
{
	SDL_Rect destSDLRect = destRect.toSDLRect();

	if(mTexture != NULL)
	{
		SDL_RenderCopy(WindowManager::Instance().renderer, mTexture, NULL, &destSDLRect);
	}
	//TODO: Else log an error?
}

bool operator==(const Sprite &sprite1, const Sprite &sprite2)
{
	if(sprite1.mTexture == sprite2.mTexture)
	{
		return true;
	}
	return false;
}

bool operator!=(const Sprite &sprite1, const Sprite &sprite2)
{
	if(sprite1 == sprite2)
	{
		return false;
	}
	return true;
}

std::ostream &operator<<(std::ostream &os, const Sprite& sprite)
{
	os << "<Sprite " << &sprite << ": mTexture=" << sprite.mTexture << ", size=" << sprite.size << ">";
	return os;
}