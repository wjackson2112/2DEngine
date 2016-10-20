#include <string>
#include "WindowManager.hpp"

WindowManager::WindowManager()
{
	mWindow = NULL;
	renderer = NULL;
	created = false;
	opened = false;
}

WindowManager::~WindowManager()
{
	close();
	alutExit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	mWindow = NULL;
	renderer = NULL;
	created = false;
	opened = false;
}

bool WindowManager::setName(string name)
{
	if(opened)
	{
		close();
		init();
		mName = name;
		return open();
	}
	else if(created)
	{
		destroy();
		mName = name;
		return create();
	}
	else
	{
		mName = name;
		return true;
	}
}

Size WindowManager::getSize()
{
	return mSize;
}

bool WindowManager::setSize(Size size)
{
	if(opened)
	{
		close();
		mSize = size;
		init();
		return open();
	}
	else if(created)
	{
		destroy();
		mSize = size;
		return create();
	}
	else
	{
		mSize = size;
		return true;
	}
}

bool WindowManager::setFull(bool fullscreen)
{
	if(opened)
	{
		close();
		mFullscreen = fullscreen;
		init();
		return open();
	}
	else if(created)
	{
		destroy();
		mFullscreen = fullscreen;
		return create();
	}
	else
	{
		mFullscreen = fullscreen;
		return true;
	}
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
	created = true;

	//Create Window
	if(mWindow != NULL)
	{
		std::cout << "ERROR: WINDOW ALREADY EXISTS" << std::endl;
	}
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
	if(renderer != NULL)
	{
		std::cout << "ERROR: RENDERER ALREADY EXISTS" << std::endl;
	}
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
	opened = true;
	create();

	if(mWindow == NULL)
	{
		std::cout << "ERROR: Window not initialized before trying to open" << std::endl;
		return false;
	}
	if(renderer == NULL)
	{
		std::cout << "ERROR: Renderer not initialized before trying to open" << std::endl;
		return false;
	}

	//Create Window and Renderer
	return true;
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
	opened = false;
	//Destroy Window and Renderer
	destroy();

	return true;
}

bool WindowManager::destroy()
{
	created = false;

	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}

	//Reset the AssetManager since the renderer is no good now
	AssetManager::Instance().clearAllAssets();

	return true;
}
