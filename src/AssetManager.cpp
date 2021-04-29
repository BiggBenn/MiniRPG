#include "AssetManager.hpp"


//set the singleton pointer to be nullptr, so we can check if it's initialized
AssetManager* AssetManager::Singleton = nullptr;

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	//ensure all textures are unloaded
	for (std::pair<std::string,RegisteredTexture> regtex : LoadedTextures)
	{
		UnloadTexture(regtex.second.texture);
	}
}

AssetManager* AssetManager::GetAssetManager()
{
	if (Singleton == nullptr)
	{
		Singleton = new AssetManager();
	}
	return Singleton;
}

Texture2D AssetManager::RequestTexture(std::string path)
{
	//check if the texture is already loaded
	if (LoadedTextures.count(path) == 1)
	{
		//if so, note that theres a new user, and return the texture
		LoadedTextures[path].userCount += 1;
		return LoadedTextures[path].texture;
	}
	else
	{
		//otherwise, load up the texture
		RegisteredTexture regtex;
		regtex.texture = LoadTexture(path.c_str());
		regtex.userCount = 1;
		LoadedTextures.emplace(path, regtex);
		return regtex.texture;
	}
}

void AssetManager::UnregisterTexture(std::string path)
{
	//Just assume the texture is loaded already, otherwise there'll be a crash lol. If that happens too often, add a check here.
	LoadedTextures[path].userCount -= 1;
	
	//if there are no users, unload the texture. no need to hog vram
	//if the loading and unloading causes lags, put a check here to prevent unloading certain/all/recently freed textures
	if (LoadedTextures[path].userCount <= 0)
	{
		UnloadTexture(LoadedTextures[path].texture);
		LoadedTextures.erase(path);
	}
}
