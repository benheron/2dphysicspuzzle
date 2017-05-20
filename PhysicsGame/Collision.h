#pragma once

#include "Vec2.h"
#include "entities/Entity.h"
#include "levelManagement/Tile.h"
#include "entities/shapes/Square.h"
#include "entities/shapes/Circle.h"
#include <math.h>
#include <cmath>
#include <algorithm>  


struct Manifold {
	Entity *A;
	Entity *B;
	float penetration;
	Vec2 normal;
};

struct ManifoldTile {
	Entity *A;
	Tile *B;
	float penetration;
	Vec2 normal;
};



/**
@brief A collection of collision functions
*/
namespace Collision
{
	/**
	@brief Collision between a single point and a box
	@param posA The position of the point
	@param posB The position of the box
	@param dimenB The dimensions of this box
	*/
	bool pointBoxCollision(Vec2 posA, Vec2 posB, Vec2 dimenB);

	bool pointBoxCollision(Vec2 A, Entity *B);


	/**
	@brief Collision between two boxes
	@param posA The position of the first box
	@param dimenA The dimensions of the first box
	@param posB The position of the second box
	@param dimenB The dimensions of the second box
	*/
	bool boxBoxCollision(Vec2 posA, Vec2 dimenA, Vec2 posB, Vec2 dimenB);

	float distanceBetween(Vec2 a, Vec2 b);

	bool circleCircleCollision(Circle a, Circle b);



	bool boxTileEdgeCollision(ManifoldTile *m);

	bool boxBoxCollisionM(Manifold *m);
	bool circleCircleCollisionM(Manifold *m);
	bool circleBoxCollision(Manifold *m);

	bool boxCircleCollision(Manifold *m);

	void resolve(Manifold *m);

	void correctPositions(Manifold *m);

	float pythagorus(float a, float b);

	float findAngleRad(Vec2 v);

	float findAngleDeg(Vec2 v);

	const float PI = 3.14159265359;

}


