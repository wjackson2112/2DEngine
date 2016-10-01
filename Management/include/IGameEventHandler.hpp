#ifndef IGAME_EVENT_HANDLER_H
#define IGAME_EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class IGameEventHandler
{
public:
	virtual void handleGameEvents(vector<int>) = 0;
};

#endif