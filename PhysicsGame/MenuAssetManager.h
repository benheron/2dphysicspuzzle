#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Texture.h"

class MenuAssetManager {
public:
	MenuAssetManager();

	~MenuAssetManager();

protected:


	std::unordered_map<std::string, Texture*> k;

};