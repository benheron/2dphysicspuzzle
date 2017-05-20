#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Texture.h"

class AssetManager {
public:
	AssetManager(SDL_Renderer *renderer);
	~AssetManager();

	Texture* getTexture(std::string id);

	

protected:
	std::unordered_map<std::string, Texture*> miscTextures;

};