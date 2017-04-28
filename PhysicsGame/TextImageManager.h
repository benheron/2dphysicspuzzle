#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Texture.h"
#include "TextCharacterType.h"

#include "Utility.h"

class TextImageManager {
public:
	TextImageManager(std::string filePath, SDL_Renderer* renderer);
	~TextImageManager();

	TextCharacterType* getTextCharacterTypeByAscii(int ID);
	TextCharacterType* getTextCharacterTypeByLetter(std::string l);

protected:
	bool loadTextImageData(std::string filePath, SDL_Renderer* renderer);

	std::unordered_map<int, TextCharacterType*> TextCharacterTypesAsciiID;
	std::unordered_map<std::string, TextCharacterType*> TextCharacterTypesAsciiLetter;


};