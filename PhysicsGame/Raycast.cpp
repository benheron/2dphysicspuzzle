#include "Raycast.h"
#include "Collision.h"

Raycast::Raycast(Vec2 startPos, Vec2 endPos, int step)
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

	int d = 0;
}

Raycast::~Raycast()
{

}

std::vector<Vec2> Raycast::getRayPoints()
{
	return points;
}