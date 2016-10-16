#ifndef MENU_ENTITY_H
#define MENU_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "Point.h"
#include "Rect.h"
#include "IMouseEventHandler.h"

class MenuEntity : public Entity, public IMouseEventHandler
{
protected:
	SDL_Texture* texture;
public:
	MenuEntity(string texture_file, Point origin);

	virtual void handleMousePress(int mouseState, int x, int y) = 0;
	virtual void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY) = 0;
	virtual void handleMouseRelease(int mouseState, int x, int y) = 0;
};

#endif