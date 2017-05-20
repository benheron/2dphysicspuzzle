#include "Creature.h"

Creature::Creature(Texture* texture, Vec2 pos, CreatureType *creatureType) : Entity(texture, pos), creatureType(creatureType)
{
	mass = 1;
	bounciness = 0;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}

Creature::Creature(Texture* texture, Vec2 pos, Vec2 dimensions, CreatureType *creatureType) : Entity(texture, pos, dimensions), creatureType(creatureType)
{
	mass = 1;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}	

Creature::Creature(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spriteDimensions, CreatureType *creatureType) : Entity(texture, pos, dimensions, Vec2(0, 0), spriteDimensions), creatureType(creatureType)
{
	mass = 1;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
}

Creature::~Creature()
{
}

void Creature::update(float dt)
{

	if (gravityOn)
	{
		float accY = 0;
		accY += 400;


		velocity.y += accY * dt;
	}
	if (moveToward)
	{
		if (posMoveTo.x < pos.x)
		{
			velocity.x = -30;
		}
		else {
			velocity.x = 30;
		}
	}

	switch (cs)
	{
	case Creature::approach:
		if (posMoveTo.x < pos.x)
		{
			velocity.x = -30;
		}
		else {
			velocity.x = 30;
		}
		break;
	case Creature::attack:
		break;
	case Creature::runAway:
		break;
	case Creature::idle:
		break;
	default:
		break;
	}

	pos += velocity * dt;
}

void Creature::render(SDL_Renderer* renderer)
{
	//If the Tile does not have a blank ID then render to the Tile
	if (creatureType->getID() != "XX")
	{
//		creatureType->render(renderer, pos, dimensions);
	}
}

CreatureType* Creature::getCreatureType()
{
	return creatureType;
}


void Creature::setMoveToward(bool m)
{
	moveToward = m;
	if (!moveToward)
	{
		velocity.x = 0;
	}
}

void Creature::setMoveTowardPos(Vec2 p)
{
	posMoveTo = p;
}