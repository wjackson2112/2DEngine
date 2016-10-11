#include <string>
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
	window = NULL;
	renderer = NULL;
}

WindowManager::~WindowManager()
{
	window = NULL;
	renderer = NULL;
}

bool WindowManager::setName(string name)
{
	destroy();

	this->name = name;

	return create();
}

bool WindowManager::setSize(int width, int height)
{
	destroy();

	this->width = width;
	this->height = height;

	return create();
}

bool WindowManager::setFull(bool fullscreen)
{
	destroy();

	this->fullscreen = fullscreen;

	return create();
}

bool WindowManager::init()
{
	name = "2DEngine";
	fullscreen = false;
	width = 640;
	height = 480;

	//Init SDL
	if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Init Fonts
	if(TTF_Init() < 0)
	{
		printf("Font library could not intiialize! SDL_Error: %s\n", TTF_GetError());
		return false;
	}

	//Init Sound
	alutInit(0, NULL);
	alGetError();	

	return true;
}

bool WindowManager::create()
{
	//Create Window
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if(fullscreen){
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	
	//Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if(renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Force the screen to get cleared to black
	clear();
	present();

	return true;
}

bool WindowManager::open()
{
	if(!window && !renderer && !init())
	{
		return false;
	}

	//Create Window and Renderer
	return create();
}

void WindowManager::clear()
{
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);
}

void WindowManager::present()
{
	SDL_RenderPresent(renderer);
}

void WindowManager::close()
{
	//Destroy Window and Renderer
	destroy();

	alutExit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void WindowManager::destroy()
{
	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
	
}
