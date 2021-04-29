#pragma once
#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <string>
#include <unordered_map>

#include "raylib.h"

struct RegisteredTexture{
	Texture2D texture;
	int userCount;
};

class AssetManager
{
private:
	//
	static AssetManager* Singleton;

	//loaded textures
	std::unordered_map<std::string, RegisteredTexture> LoadedTextures;

	//constructor
	AssetManager();


public:
	//destructor
	~AssetManager();

	//singleton type class
	static AssetManager* GetAssetManager();

	// Loading functions, essentially the manager should load any unloaded files, and only hand off pointers to already loaded ones //

	//Request Texture loads the texture into gpu if it's not loaded yet, and takes note of how many users of the texture there are
	Texture2D RequestTexture(std::string path);
	//Unregister should be called when an object stops using a texture, like when it's destroyed
	void UnregisterTexture(std::string path);

};



#endif