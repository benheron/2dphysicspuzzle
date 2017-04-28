#include "TextCharacterType.h"

TextCharacterType::TextCharacterType(Texture *spritesheet, int asciiID, std::string textChar, Vec2 spritePosition, Vec2 spriteDimensions)
	:spritesheet(spritesheet), asciiID(asciiID), textChar(textChar), spritePosition(spritePosition), spriteDimensions(spriteDimensions)
{

}

TextCharacterType::~TextCharacterType()
{

}

void TextCharacterType::render(SDL_Renderer* renderer, Vec2 pos, Vec2 dimensions)
{
	spritesheet->pushSpriteToScreen(renderer, pos, spriteDimensions, spritePosition, spriteDimensions);
}

Vec2 TextCharacterType::getTextCharacterDimensions()
{
	return spriteDimensions;
}