#include "Door.h"

Door::Door(Texture *texture, Vec2 pos, Vec2 dimens, bool activated) : ActivatableItem(texture, pos, dimens, activated), initialPos(pos)
{
	velocity = Vec2(0);

	changeVel = Vec2(0, -40);

	moveToPos = initialPos - Vec2(0.f, dimensions.y);

	dist = Collision::distanceBetween(initialPos, moveToPos);

	dState = close;
	still = false;
	applyFriction = false;
	mass = 0;
}

Door::~Door()
{

}

void Door::update(float dt)
{
	if (activated)
	{
		pos += changeVel * dt;
		if (Collision::distanceBetween(initialPos, pos) > dist)
		{
			dState = open;
			pos = moveToPos;
			velocity = 0;
			still = true;
		}
		else {
			still = false;
		}

	}
	else if (!activated) {
		pos -= changeVel *dt;
		if (Collision::distanceBetween(moveToPos, pos) > dist)
		{
			dState = close;
			pos = initialPos;
			still = true;
		}
		else {
			still = false;
		}
	}
}

void Door::render(SDL_Renderer* renderer)
{
	texture->pushSpriteToScreen(renderer, pos, 0, dimensions);
}