#include <string>
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
	mWindow = NULL;
	renderer = NULL;
}

WindowManager::~WindowManager()
{
	mWindow = NULL;
	renderer = NULL;
}

bool WindowManager::setName(string name)
{
	destroy();

	mName = name;

	return create();
}

Size WindowManager::getSize()
{
	return mSize;
}

bool WindowManager::setSize(Size size)
{
	destroy();

	mSize = size;

	return create();
}

bool WindowManager::setFull(bool fullscreen)
{
	destroy();

	mFullscreen = fullscreen;

	return create();
}

bool WindowManager::init()
{
	mName = "2DEngine";
	mFullscreen = false;
	mSize = Size(640, 480);

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
	alutInit(NULL, NULL);

	return true;
}

bool WindowManager::create()
{
	//Create Window
	mWindow = SDL_CreateWindow(mName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mSize.x, mSize.y, SDL_WINDOW_SHOWN);
	if(mWindow == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		destroy();
		return false;
	}

	if(mFullscreen && SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		destroy();
		return false;
	}

	//Create Renderer
	renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		destroy();
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	//Force the screen to get cleared to black
	if(!clear() || !present())
	{
		destroy();
		return false;
	}

	return true;
}

bool WindowManager::open()
{
	if(!mWindow && !renderer && !init())
	{
		return false;
	}

	//Create Window and Renderer
	return create();
}

bool WindowManager::clear()
{
	if(SDL_RenderClear(renderer) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

bool WindowManager::present()
{
	if(renderer == NULL)
	{
		return false;
	}

	SDL_RenderPresent(renderer);

	return true;
}

bool WindowManager::close()
{
	//Destroy Window and Renderer
	destroy();

	alutExit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return true;
}

bool WindowManager::destroy()
{
	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(mWindow)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}
	
	//Reset the AssetManager since the renderer is no good now
	AssetManager::Instance().clearAllAssets();

	return true;
}
