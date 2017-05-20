#include "Sentinel.h"

Sentinel::Sentinel(Texture* sentinel, Texture* laserText, Vec2 pos, Vec2 dimens, CreatureType* ct) : Creature(sentinel, pos, dimens, ct), laserText(laserText)
{
	float laserX = pos.x + dimens.x / 2;
	float laserY = pos.y + dimens.y;;

	laserPos = Vec2(laserX, laserY-1);
	laserlength = 9 * 32;
	laserDir = Vec2(0, 1);

	laser = new Raycast(laserText, laserPos, laserDir, laserlength, 1);

	sstate = passive;

	laserPointsToRender = -1;

}

Sentinel::~Sentinel()
{

}

void Sentinel::update(float dt)
{
	
	laserPointsToRender = -1;
	switch (sstate)
	{
	case Sentinel::lockedOn:
		laser->updateRayEndPos(theTarget->getCentre());
		lockedOnTime += dt;
		break;
	case Sentinel::centring:
		laser->updateRayDir(laserDir);
		sstate = passive;
		if (lockedOnTime > 0)
		{
			lockedOnTime -= dt;
		}
	
		break;
	case Sentinel::passive:
	
		break;
	default:
		laser->updateRayDir(laserDir);
		break;
	}

	if (lockedOnTime > 1.2)
	{
		if (sstate == lockedOn)
		{
			theTarget->setAlive(false);
		}
	}
}

void Sentinel::render(SDL_Renderer* renderer)
{
	if (laserPointsToRender == -1)
	{
		laser->renderRay(renderer);
	}
	else {
		laser->renderRay(renderer, laserPointsToRender);
	}

	creatureType->render(renderer, pos, dimensions, "I", false, Vec2(1, 0));
	//creatureType->render(renderer, pos, dimensions);
}

void Sentinel::setLockedOn(bool lo)
{
	isLockedOn = lo;

	if (!isLockedOn && sstate != passive)
	{
		sstate = centring;
	}
}

void Sentinel::setLockedOn(bool lo, Character* t)
{
	isLockedOn = lo;
	theTarget = t;

	sstate = lockedOn;
}

bool Sentinel::getLockedOn()
{
	return isLockedOn;
}

void Sentinel::moveLaserTo(Vec2 laserToPos)
{

}

std::vector<Vec2> Sentinel::getLaserPoints()
{
	return laser->getRayPoints();
}

void Sentinel::setLaserPointsToRender(int lp)
{
	laserPointsToRender = lp;
}