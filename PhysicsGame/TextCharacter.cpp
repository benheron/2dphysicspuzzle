#include "TextCharacter.h"

TextCharacter::TextCharacter(Vec2 pos, Vec2 dimensions, TextCharacterType* textCharType) : Entity(pos, dimensions), textCharType(textCharType)
{
	
}

TextCharacter::~TextCharacter()
{

}

void TextCharacter::update(float dt)
{

}

void TextCharacter::render(SDL_Renderer *renderer)
{
	textCharType->render(renderer, pos, dimensions);
}

void TextCharacter::setTextCharacterType(TextCharacterType *tct)
{
	textCharType = tct;
}