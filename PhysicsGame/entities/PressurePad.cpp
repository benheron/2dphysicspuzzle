#include "PressurePad.h"



PressurePad::PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions, ActivatableItem *linkedItem) : Entity(texture, pos, dimensions), linkedItem(linkedItem)
{
	spritePos = 0;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
	activated = false;
	mass = 0;
}

PressurePad::~PressurePad()
{

}

void PressurePad::buildPressurePad()
{

}

void PressurePad::update(float dt)
{

	linkedItem->setActivated(activated);

}


void PressurePad::setActivate(bool a)
{
	activated = a;
	linkedItem->setActivated(a);
}

bool PressurePad::getActivate()
{
	return activated;
}

void PressurePad::render(SDL_Renderer *renderer)
{
	texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
}


