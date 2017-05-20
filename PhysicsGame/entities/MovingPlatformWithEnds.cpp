#include "MovingPlatformWithEnds.h"

MovingPlatformWithEnds::MovingPlatformWithEnds(Texture* endsTexture, Texture* dashTexture, Texture* movingPlatformTexture, Vec2 start, Vec2 end, Vec2 dimens, int speed, bool activated, bool reversing) : Entity(pos),
	endsTexture(endsTexture), dashTexture(dashTexture)
{
	mp = new MovingPlatform(movingPlatformTexture, start, end, dimens, speed, activated, reversing);

	startPos = start + dimens/2 - (endsTexture->getDimensions()/2);
	endPos = end + dimens/2 - (endsTexture->getDimensions() / 2);

	dimensions = endPos - startPos;

	Vec2 dir = endPos - startPos;
	Vec2 dirN = dir.normalize();

	dashSize = Vec2(9, 2);
	dashLength = dashSize.getLength();
	float dist = Collision::distanceBetween(endPos, startPos);
	
	dashAngle = Collision::findAngleDeg(dir);

	int num = dist / 9;

	for (int i = 0; i < num; i++)
	{
		if (i % 2)
		{
			Vec2 newPos = startPos + dirN*dashLength*i;
			dashPos.push_back(newPos);
		}
	}
}

MovingPlatformWithEnds::~MovingPlatformWithEnds()
{

}

void MovingPlatformWithEnds::update(float dt)
{
	mp->update(dt);
}

void MovingPlatformWithEnds::render(SDL_Renderer* renderer)
{
	endsTexture->pushSpriteToScreen(renderer, startPos);
	endsTexture->pushSpriteToScreen(renderer, endPos);

	for (int i = 0; i < dashPos.size(); i++)
	{
		dashTexture->pushSpriteToScreen(renderer, dashPos[i], dashSize, 0, dashSize, dashAngle);
	}

	mp->render(renderer);
}

void MovingPlatformWithEnds::setReversing(bool r)
{
	mp->setReversing(r);
}

bool MovingPlatformWithEnds::getReversing()
{
	return mp->getReversing();
}

void MovingPlatformWithEnds::setActivated(bool a)
{
	mp->setActivated(a);
}

bool MovingPlatformWithEnds::getActivated()
{
	return mp->getActivated();
}

MovingPlatform* MovingPlatformWithEnds::getMovingPlatform()
{
	return mp;
}

bool MovingPlatformWithEnds::checkPlatformCollision(Manifold *m)
{
	m->B = mp;
	if (Collision::boxBoxCollisionM(m))
	{
		return true;
	}
	return false;
}
