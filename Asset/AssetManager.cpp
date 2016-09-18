#include <AL/alut.h>
#include "AssetManager.hpp"

using namespace std;

AssetManager::AssetManager()
{
	//Init Sound
	alutInit(0, NULL);
}

AssetManager::~AssetManager()
{
	// textures.clear();
	sounds.clear();

	//Clean Sound
	alutExit();
}


// template<>
// SDL_Texture& AssetManager::getAsset<SDL_Texture>(string key)
// {
// 	SDL_Texture* texture;

// 	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

// 	unordered_map<string, SDL_Texture&>::iterator it = textures.find(key);

// 	if(it != textures.end())
// 	{
// 		return it->second;
// 	}

// 	//TODO: Make the renderer globally available
// 	texture = IMG_LoadTexture(gRenderer, key.c_str());

// 	textures.insert(make_pair(key, texture));
// 	return texture;
// }

template<>
Sound* AssetManager::getAsset<Sound>(string key)
{
	Sound* sound;

	unordered_map<string, Sound*>::iterator it = sounds.find(key);

	if(it != sounds.end())
	{
		return it->second;
	}

	sound = new Sound(key);
	if(sound->hasError())
	{
		delete sound;
		return NULL;
	}

	sounds.insert(make_pair(key, sound));
	return sound;
}