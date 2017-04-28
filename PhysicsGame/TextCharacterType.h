#pragma once
#include "Texture.h"

class TextCharacterType
{
public:
	TextCharacterType(Texture *spritesheet, int asciiID, std::string textChar, Vec2 spritePositions, Vec2 spriteDimensions);
	~TextCharacterType();

	void render(SDL_Renderer* renderer, Vec2 pos, Vec2 dimensions);
	Vec2 getTextCharacterDimensions();


protected:
	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the TextCharacterType (or the character itself).
	int asciiID;
	///The character itself
	std::string textChar;
	///The position of the sprite on the spritesheet.
	Vec2 spritePosition;
	///The index position of the sprite on the spritesheet.
	Vec2 spriteIndexPositions;
	///The dimensions of the sprite.
	Vec2 spriteDimensions;

};