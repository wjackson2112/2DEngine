#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sound.hpp"
#include "Sprite.hpp"

using namespace std;

class AssetManager 
{	

	unordered_map<string, SDL_Texture*> textures;
	unordered_map<string, Sound*> sounds;

	AssetManager();
	~AssetManager();
public: 
	
	//Meyer's Singleton
	static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}

	template<typename T>	
	T getAsset(string key)
	{
		cout << "Type " << typeid(T).name() << " is not supported by the AssetManager" << endl;
		return NULL;
	}

	void clearAllAssets();
};

#endif