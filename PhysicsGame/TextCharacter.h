#pragma once
#include <string>
#include "Texture.h"
#include "entities/Entity.h"
#include "TextCharacterType.h"

class TextCharacter : public Entity 
{
public:
	TextCharacter(Vec2 pos, Vec2 dimensions, TextCharacterType* textCharType);
	~TextCharacter();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	void setTextCharacterType(TextCharacterType *tct);

protected:
	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the TextCharacter (or the character itself).
	std::string ID;
	///The position of the sprite on the spritesheet.
	Vec2 spritePosition;
	///The index position of the sprite on the spritesheet.
	Vec2 spriteIndexPositions;
	///The dimensions of the sprite.
	Vec2 spriteDimensions;

	TextCharacterType* textCharType;

};