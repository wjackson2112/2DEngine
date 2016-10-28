#include "EventManager.hpp"

EventManager::EventManager(int numGameEventTypes)
{
	gameEvents.resize(numGameEventTypes);
	clearGameEvents();
}

void EventManager::clearGameEvents()
{
	for(int i = 0; i < gameEvents.size(); i++)
	{
		gameEvents[i] = 0;
	}
}

template<typename T>
void registerEventHandler(std::vector<T*> &eventHandlers, T* handler)
{
	eventHandlers.push_back(handler);
}

template<typename T>
void unregisterEventHandler(std::vector<T*> &eventHandlers, T* handler)
{
	for(typename std::vector<T*>::iterator it=eventHandlers.begin(); it!=eventHandlers.end();)
	{
		if(*it == handler)
		{
			it = eventHandlers.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void EventManager::registerGameEventHandler(IGameEventHandler* handler)
{
	registerEventHandler(this->gameEventHandlers, handler);
}

void EventManager::unregisterGameEventHandler(IGameEventHandler* handler)
{
	unregisterEventHandler(this->gameEventHandlers, handler);
}

void EventManager::registerMouseEventHandler(IMouseEventHandler* handler)
{
	registerEventHandler(this->mouseEventHandlers, handler);
}

void EventManager::unregisterMouseEventHandler(IMouseEventHandler* handler)
{
	unregisterEventHandler(this->mouseEventHandlers, handler);
}

void EventManager::registerKeyboardEventHandler(IKeyboardEventHandler* handler)
{
	registerEventHandler(this->keyboardEventHandlers, handler);
}

void EventManager::unregisterKeyboardEventHandler(IKeyboardEventHandler* handler)
{
	unregisterEventHandler(this->keyboardEventHandlers, handler);
}

void EventManager::registerSDLEventHandler(ISDLEventHandler* handler)
{
	registerEventHandler(this->sdlEventHandlers, handler);
}

void EventManager::unregisterSDLEventHandler(ISDLEventHandler* handler)
{
	unregisterEventHandler(this->sdlEventHandlers, handler);
}

void EventManager::handleMouseEvents()
{
	static int prevX, prevY, prevMouseState;

	int x, y, mouseState;

	SDL_PumpEvents();
	mouseState = SDL_GetMouseState(&x, &y);

	for(int i = SDL_BUTTON_LEFT; i <= SDL_BUTTON_X2; i++)
	{
		if(mouseState & SDL_BUTTON(i) && !(prevMouseState & SDL_BUTTON(i)))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMousePress(i, x, y);
			}
		}
		else if(!(mouseState & SDL_BUTTON(i)) && prevMouseState & SDL_BUTTON(i))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMouseRelease(i, x, y);
			}
		}
		else if(mouseState & SDL_BUTTON(i) && prevMouseState & SDL_BUTTON(i))
		{
			for(auto &handler : mouseEventHandlers)
			{
				handler->handleMouseDrag(i, prevX, prevY, x, y);
			}
		}
	}

	prevX = x;
	prevY = y;
	prevMouseState = mouseState;
}

void EventManager::handleKeyboardEvents()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	for(auto &handler : keyboardEventHandlers)
	{
		handler->handleKeyboardEvents(keyStates);
	}
}

void EventManager::reportGameEvent(int event)
{
	gameEvents[event] += 1;
}

void EventManager::handleGameEvents()
{
	for(auto &handler : gameEventHandlers)
	{
		handler->handleGameEvents(gameEvents);
	}
	this->clearGameEvents();
}

void EventManager::handleSDLEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		for(auto &handler : sdlEventHandlers)
		{
			handler->handleSDLEvent(event);
		}
	}
}