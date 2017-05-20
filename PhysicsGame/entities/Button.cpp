#include "Button.h"


Button::Button(Vec2 pos, Vec2 dimensions) : Entity(pos, dimensions)
{
	bState = buttonIdle;
}

Button::Button(Texture* texture, Vec2 pos) : Entity(texture, pos)
{
	bState = buttonIdle;

}

Button::Button(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	bState = buttonIdle;
}


Button::Button(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{
	bState = buttonIdle;
}

Button::~Button()
{

}

void Button::buildButton()
{

}

void Button::update(float dt)
{
}


void Button::render(SDL_Renderer *renderer)
{
	switch (bState)
	{
	case Button::buttonHover:
		texture->pushSpriteToScreen(renderer, pos, Vec2(spritePos.x, spriteDimensions.y), spriteDimensions);
		break;
	case Button::buttonSelected:
		texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
		//texture->pushSpriteToScreen(renderer, pos, Vec2(spritePos.x, spriteDimensions.y * 2), spriteDimensions);
		break;
	case Button::buttonIdle:
		texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
		break;
	default:
		texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
		break;
	}

	
	
}


bool Button::isHover()
{
	return bState == buttonHover ? true : false;
}

void Button::setHover(bool h)
{
	bState = buttonHover;
}

bool Button::getHover()
{
	return bState == buttonHover ? true : false;
	//return hover;
}

void Button::setSelected(bool s)
{
	bState = buttonSelected;
}

bool Button::getSelected()
{
	return bState == buttonSelected ? true : false;
}

void Button::setIdle()
{
	bState = buttonIdle;
}