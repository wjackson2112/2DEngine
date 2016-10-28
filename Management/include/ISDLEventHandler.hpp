#ifndef ISDL_EVENT_HANDLER_H
#define ISDL_EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class ISDLEventHandler
{
public:
	virtual void handleSDLEvent(SDL_Event event) = 0;
};

#endif