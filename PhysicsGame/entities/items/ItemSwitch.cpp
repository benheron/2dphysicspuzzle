#include "ItemSwitch.h"

ItemSwitch::ItemSwitch(Texture* texture, Vec2 pos, Vec2 dimensions, ActivatableItem *linkedItem) : Entity(texture, pos, dimensions), linkedItem(linkedItem)
{
	spritePos = 0;
	activatedSpritePos = Vec2(0.f, dimensions.y);
	staticFriction = 0.4;
	dynamicFriction = 0.2;
	activated = false;
	mass = 0;

	
}

ItemSwitch::~ItemSwitch()
{

}

void ItemSwitch::update(float dt)
{

	linkedItem->setActivated(activated);
}


void ItemSwitch::activate()
{
	if (activated)
	{
		activated = false;
	}
	else {
		activated = true;
	}	
	linkedItem->setActivated(activated);
}

bool ItemSwitch::getActivate()
{
	return activated;
}

void ItemSwitch::render(SDL_Renderer *renderer)
{
	if (activated)
	{
		texture->pushSpriteToScreen(renderer, pos, activatedSpritePos, dimensions);
	}
	else {
		texture->pushSpriteToScreen(renderer, pos, spritePos, dimensions);
	}
	
}


