#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include "Sound.hpp"
// #include "Options.h"

#include "SimpleIni.h"

using namespace std;

class AssetManager {	
private:

	static AssetManager* instance;

	unordered_map<string, SDL_Texture*> textures;
	// unordered_map<string, Sound> sounds;
	// SDL_Renderer* gRenderer;
	// Options& options;
	AssetManager(){};
	~AssetManager();
public: 
	
	static AssetManager* Instance();

	template<typename T>	
	T& getAsset(string key)
	{
		cout << "Type " << typeid(T).name() << " is not supported by the AssetManager" << endl;
	}
};

#endif