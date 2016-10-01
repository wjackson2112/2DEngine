#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SDL2/SDL.h>
#include <vector>
#include "IGameEventHandler.hpp"
#include "IMouseEventHandler.hpp"
#include "IKeyboardEventHandler.hpp"

using namespace std;

class EventManager
{
	SDL_Event e;

	vector<IGameEventHandler*> gameEventHandlers;
	vector<IMouseEventHandler*> mouseEventHandlers;
	vector<IKeyboardEventHandler*> keyboardEventHandlers;

	vector<int> gameEvents;

	void clearGameEvents();
public:
	
	EventManager(int numGameEventTypes);

	void registerGameEventHandler(IGameEventHandler* handler);
	void unregisterGameEventHandler(IGameEventHandler* handler);
	void handleGameEvents();

	void registerMouseEventHandler(IMouseEventHandler* handler);
	void unregisterMouseEventHandler(IMouseEventHandler* handler);
	void handleMouseEvents();

	void registerKeyboardEventHandler(IKeyboardEventHandler* handler);
	void unregisterKeyboardEventHandler(IKeyboardEventHandler* handler);
	void handleKeyboardEvents();

	void reportGameEvent(int event);
};

#endif