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
	textures.clear();
	sounds.clear();

	//Clean Sound
	alutExit();
}


template<>
Sprite AssetManager::getAsset<Sprite>(string key)
{
	Sprite sprite;
	SDL_Texture* texture;

	unordered_map<string, SDL_Texture*>::iterator it = textures.find(key);

	if(it != textures.end())
	{
		texture = it->second;
		sprite = Sprite(texture);
		return sprite;
	}

	texture = IMG_LoadTexture(WindowManager::Instance().renderer, key.c_str());
	sprite = Sprite(texture);

	textures.insert(make_pair(key, texture));
	return sprite;
}

template<>
Sound* AssetManager::getAsset<Sound*>(string key)
{
	Sound* sound;

	unordered_map<string, Sound*>::iterator it = sounds.find(key);

	if(it != sounds.end())
	{
		return it->second;
	}

	//TODO: Use an actual XML key for this instead of a path
	sound = new Sound(key);
	if(sound->hasError())
	{
		delete sound;
		return NULL;
	}

	sounds.insert(make_pair(key, sound));
	return sound;
}