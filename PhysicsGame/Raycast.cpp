#include "Raycast.h"
#include "Collision.h"

Raycast::Raycast(Vec2 startPos, Vec2 endPos, int step) : startPos(startPos), endPos(endPos), step(step)
{
	buildRay();

}

Raycast::Raycast(Texture* rayText, Vec2 startPos, Vec2 endPos, int step) : startPos(startPos), endPos(endPos), step(step), rayText(rayText)
{
	buildRay();
}

Raycast::Raycast(Texture* rayText, Vec2 startPos, Vec2 dir, float length, int step) : dir(dir), startPos(startPos), length(length), step(step), rayText(rayText)
{
	buildRayDir();
}

Raycast::~Raycast()
{

}

void Raycast::buildRay()
{
	dir = endPos - startPos;
	dir = dir.normalize();

	float dist = Collision::distanceBetween(endPos, startPos);
	int num = dist / step;

	for (int i = 0; i < num; i++)
	{
		Vec2 nPoint;
		if (i != 0)
		{
			nPoint = points[i - 1] + dir;
		}
		else {
			nPoint = startPos + dir;
		}
		points.push_back(nPoint);
	}
}

void Raycast::buildRayEndPosLength()
{
	dir = endPos - startPos;
	dir = dir.normalize();

	int num = length / step;

	for (int i = 0; i < num; i++)
	{
		Vec2 nPoint;
		if (i != 0)
		{
			nPoint = points[i - 1] + dir;
		}
		else {
			nPoint = startPos + dir;
		}
		points.push_back(nPoint);
	}
}

void Raycast::buildRayDir()
{
	endPos = startPos + dir*length;
	int num = length / step;
	for (int i = 0; i < num; i++)
	{
		Vec2 nPoint;
		if (i != 0)
		{
			nPoint = points[i - 1] + dir;
		}
		else {
			nPoint = startPos + dir;
		}
		points.push_back(nPoint);
	}
}

std::vector<Vec2> Raycast::getRayPoints()
{
	return points;
}

void Raycast::updateRayEndPos(Vec2 ep)
{
	points.clear();
	endPos = ep;
	buildRayEndPosLength();
}

void Raycast::updateRayDir(Vec2 nDir)
{
	points.clear();
	dir = nDir;
	buildRayDir();
}

void Raycast::renderRay(SDL_Renderer* renderer)
{
	for (int i = 0; i < points.size(); i++)
	{
		rayText->pushSpriteToScreen(renderer, points[i]);
	}
}

void Raycast::renderRay(SDL_Renderer* renderer, int numPoints)
{
	for (int i = 0; i < numPoints; i++)
	{
		rayText->pushSpriteToScreen(renderer, points[i]);
	}
}