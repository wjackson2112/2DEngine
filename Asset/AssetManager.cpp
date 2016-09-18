#include "AssetManager.hpp"

AssetManager* AssetManager::instance = NULL;

AssetManager::~AssetManager()
{
	// textures.clear();
	// sounds.clear();
}

AssetManager* AssetManager::Instance()
{
	if(!instance)
	{
		instance = new AssetManager();
	}

	return instance;
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

// template<>
// Sound& getAsset<Sound>(string key)
// {

// 	Sound& sound;

// 	unordered_map<string, Sound&>::iterator it = sounds.find(key);

// 	if(it != sounds.end())
// 	{
// 		return it->second;
// 	}

// 	//TODO: Make the options globally available
// 	sound = new Sound(key, this->options);

// 	sounds.insert(make_pair(key, sound));
// 	return sound;
// }