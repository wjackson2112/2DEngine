#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <AL/alut.h>
#include <string>

#include "AssetManager.hpp"
#include "Point.hpp"
#include "Sound.hpp"

using namespace std;

class WindowManager 
{
	SDL_Window* mWindow;
	
	bool mFullscreen;
	Size mSize;
	string mName;

	WindowManager();
	~WindowManager();

	bool create();
	bool destroy();

public:

	SDL_Renderer* renderer;

	//Meyer's Singleton
	static WindowManager& Instance()
	{
		static WindowManager instance;
		return instance;
	}

	bool setName(string name);
	Size getSize();
	bool setSize(Size size);
	bool setFull(bool fullscreen);

	bool init();
	bool open();
	bool clear();
	bool present();
	bool close();

};

#endif