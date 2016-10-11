#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "Rect.hpp"
#include "WindowManager.hpp"

class Sprite : Rect
{
	SDL_Texture* texture;

public:

	Sprite();
	Sprite(SDL_Texture* texture);

	void render();

	void scale(double scaleFactor);
	void scaleToWidth(int width);
	void scaleToHeight(int height);
};

#endif