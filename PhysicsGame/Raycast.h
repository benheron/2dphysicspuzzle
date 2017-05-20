#pragma once
#include "Vec2.h"
#include <vector>
#include "Texture.h"

class Raycast {
public:
	Raycast(Vec2 startPos, Vec2 endPos, int step);

	//useful for drawing a line
	Raycast(Texture* rayText, Vec2 startPos, Vec2 endPos, int step);


	Raycast(Texture* rayText, Vec2 startPos, Vec2 dir, float length, int step);
	~Raycast();

	void buildRay();

	void buildRayDir();

	void buildRayEndPosLength();

	std::vector<Vec2> getRayPoints();

	void updateRayEndPos(Vec2 ep);
	void updateRayDir(Vec2 nDir);
	void renderRay(SDL_Renderer* renderer);

	void renderRay(SDL_Renderer* renderer, int numPoints);

protected:
	Vec2 startPos;
	Vec2 endPos;
	int step;

	std::vector<Vec2> points;
	Vec2 dir;

	Texture* rayText;

	float length;

	//float maxLen
};