#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <AL/alut.h>

using namespace std;

class WindowManager {

	SDL_Window* window;
	
	bool fullscreen;
	int width;
	int height;
	string name;

	WindowManager();
	~WindowManager();

	bool create();
	void destroy();

public:

	SDL_Renderer* renderer;

	//Meyer's Singleton
	static WindowManager& Instance()
	{
		static WindowManager instance;
		return instance;
	}

	bool setName(string name);
	bool setSize(int width, int height);
	bool setFull(bool fullscreen);

	bool init();
	bool open();
	void close();

};

#endif