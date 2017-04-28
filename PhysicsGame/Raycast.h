#pragma once
#include "Vec2.h"
#include <vector>

class Raycast {
public:
	Raycast(Vec2 startPos, Vec2 endPos, int step);
	~Raycast();

	std::vector<Vec2> getRayPoints();

protected:
	std::vector<Vec2> points;
	Vec2 dir;

};