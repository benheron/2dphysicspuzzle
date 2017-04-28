#include "PressurePad.h"


PressurePad::PressurePad(Texture* texture, Vec2 pos) : Entity(texture, pos)
{

	spritePos = 0;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}

PressurePad::PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	spritePos = 0;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}


PressurePad::PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{
	spritePos = 0;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}

PressurePad::~PressurePad()
{

}

void PressurePad::buildPressurePad()
{

}

void PressurePad::update(float dt)
{



}


void PressurePad::setActivate(bool a)
{
	activated = a;
}

bool PressurePad::getActivate()
{
	return activated;
}

void PressurePad::render(SDL_Renderer *renderer)
{
	texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
}


