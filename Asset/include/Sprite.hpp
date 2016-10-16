#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Rect.hpp"
#include "WindowManager.hpp"

class Sprite
{
	SDL_Texture* mTexture;

public:

	Size size;

	Sprite();
	Sprite(SDL_Texture* texture);

	void render(Rect destRect);

	friend bool operator==(const Sprite &sprite1, const Sprite &sprite2);
	friend bool operator!=(const Sprite &sprite1, const Sprite &sprite2);

	friend std::ostream &operator<<(std::ostream &os, const Sprite& sprite);
};



#endif