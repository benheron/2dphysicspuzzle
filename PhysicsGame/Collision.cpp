#include "Collision.h"
#include "Utility.h"

bool Collision::pointBoxCollision(Vec2 posA, Vec2 posB, Vec2 dimenB)
{
	if (posA.x > posB.x &&
		posA.x < (posB.x + dimenB.x) &&
		posA.y > posB.y &&
		posA.y < (posB.y + dimenB.y))
	{
		return true;
	}
	return false;
}

bool Collision::pointBoxCollision(Vec2 A, Entity *B)
{
	if (A.x > B->getPosition().x  &&
		A.x < (B->getPosition().x+ B->getDimensions().x) &&
		A.y > B->getPosition().y  &&
		A.y < (B->getPosition().y + B->getDimensions().y))
	{
		return true;
	}
	return false;
}

bool Collision::boxBoxCollision(Vec2 posA, Vec2 dimenA, Vec2 posB, Vec2 dimenB)
{
	if ((posA.x + dimenA.x) < posB.x ||
		posA.x > (posB.x + dimenB.x) ||
		(posA.y + dimenA.y) < posB.y ||
		posA.y > (posB.y + dimenB.y))
	{
		return false;
	}

	return true;
}

bool Collision::boxTileEdgeCollision(ManifoldTile *m)
{
	Vec2 n = m->B->getCentre() - m->A->getCentre();

	float hWidthA = m->A->getDimensions().x / 2;
	float hWidthB = m->B->getDimensions().x / 2;

	float xOverlap = hWidthA + hWidthB - abs(n.x);

	if (xOverlap > 0)
	{
		float hHeightA = m->A->getDimensions().y / 2;
		float hHeightB = m->B->getDimensions().y / 2;

		float yOverlap = hHeightA + hHeightB - abs(n.y);

		if (yOverlap > 0)
		{
			//least penetration for side
			if (xOverlap < yOverlap)
			{
				if (n.x < 0)
				{
					m->normal = Vec2(-1, 0);
				}
				else {
					m->normal = Vec2(1, 0);
				}
				m->penetration = xOverlap;
				return true;
			}
			else
			{
				if (n.y < 0)
				{
					m->normal = Vec2(0, -1);
				}
				else {
					m->normal = Vec2(0, 1);
				}
				m->penetration = yOverlap;
				return true;
			}
		}
	}
	//does not collide at all
	return false;
}

bool Collision::boxBoxCollisionM(Manifold *m)
{
	Vec2 n = m->B->getCentre() - m->A->getCentre();

	float hWidthA = m->A->getDimensions().x / 2;
	float hWidthB = m->B->getDimensions().x / 2;

	float xOverlap = hWidthA + hWidthB - abs(n.x);

	if (xOverlap > 0)
	{
		float hHeightA = m->A->getDimensions().y / 2;
		float hHeightB = m->B->getDimensions().y / 2;

		float yOverlap = hHeightA + hHeightB - abs(n.y);

		if (yOverlap > 0)
		{
			//least penetration for side
			if (xOverlap < yOverlap)
			{
				if (n.x < 0)
				{
					m->normal = Vec2(-1, 0);
				}
				else {
					m->normal = Vec2(1, 0);
				}
				m->penetration = xOverlap;
				return true;
			}
			else
			{
				if (n.y < 0)
				{
					m->normal = Vec2(0, -1);
				}
				else {
					m->normal = Vec2(0, 1);
				}
				m->penetration = yOverlap;
				return true;
			}
		}
	}
	//does not collide at all
	return false;
	
}

float Collision::distanceBetween(Vec2 a, Vec2 b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

bool Collision::circleCircleCollision(Circle a, Circle b)
{
	float radius = a.getRadius() + b.getRadius();
	return radius < distanceBetween(a.getPosition(), b.getPosition());
}

bool Collision::circleCircleCollisionM(Manifold *m)
{
	Vec2 diff = m->B->getCentre() - m->A->getCentre();
	float diffFloat = diff.getLength();

	float radius = m->A->getRadius() + m->B->getRadius();

	if (radius < distanceBetween(m->A->getCentre(), m->B->getCentre()))
	{
		return false;
	}

	if (diffFloat != 0)
	{
		m->penetration = radius - diffFloat;
		m->normal = diff / diffFloat;
		return true;
	}
	else {
		m->penetration = m->A->getRadius();
		m->normal = Vec2(1, 0);
		return true;
	}


}

bool Collision::boxCircleCollision(Manifold *m)
{
	Vec2 diff = m->B->getCentre() - m->A->getCentre();

	return true;
}

void Collision::resolve(Manifold *m)
{

	//make sure not dividing by 0
	if (m->A->mass == 0)
	{
		m->A->invMass = 0;
	}
	else {
		m->A->invMass = 1 / m->A->mass;
	}

	if (m->B->mass == 0)
	{
		m->B->invMass = 0;
	}
	else {
		m->B->invMass = 1 / m->B->mass;
	}


	Vec2 rv = m->B->velocity - m->A->velocity;

	Vec2 t = rv*m->normal;
	float relVelNorm = t.x + t.y;

	//actually going towards each other
	if (relVelNorm > 0)
	{
		return;
	}

	
	float bounciness = std::min(m->A->getBounciness(), m->B->getBounciness());

	float pushback = -(1 + bounciness) * relVelNorm;
	pushback /= (m->A->invMass + m->B->invMass);

	Vec2 impulse = m->normal * pushback;
	m->A->velocity -= impulse * m->A->invMass;
	m->B->velocity += impulse * m->B->invMass;
	


	//friction response
	//get new velocity
	rv = m->B->velocity - m->A->velocity;
	Vec2 dotv = rv*m->normal;
	float dot = dotv.x + dotv.y;

	Vec2 tangent = rv - m->normal*dot;
	Vec2 tnorm = tangent.normalize();

	//Utility::log(Utility::I, "Collision normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y));
	
	Vec2 fictionv = tnorm * rv;
	float pushbackfriction = -(fictionv.x + fictionv.y);

	pushbackfriction /= (m->A->invMass + m->B->invMass);


	float average = (m->A->staticFriction + m->B->staticFriction)/2;

	Vec2 impulse3;

	if (abs(pushbackfriction) < (pushback * average))
	{
		impulse3 = tnorm *pushbackfriction;
	} else{
		float dynFriction = pythagorus(m->A->dynamicFriction, m->B->dynamicFriction);
		impulse3 = tnorm * dynFriction * -pushback;
	}

	/*Vec2 impulse2 = tnorm * pushbackfriction;
	m->A->velocity -= impulse2 * m->A->invMass;
	m->B->velocity += impulse2 * m->B->invMass;*/

	m->A->velocity -= impulse3 * m->A->invMass;
	m->B->velocity += impulse3 * m->B->invMass;

}

void Collision::correctPositions(Manifold *m)
{
	float percent = 0.4;
	float slop = 0.001;
	//Vec2 correction = m->normal* (m->penetration / (m->A->invMass + m->B->invMass)) * percent;

	Vec2 correction = m->normal* (std::max(m->penetration - slop, 0.0f) / (m->A->invMass + m->B->invMass)) * percent;

	Vec2 tmpA, tmpB;
	
	tmpA = m->A->getPosition();
	tmpA -= correction * m->A->invMass;

	m->A->setPosition(tmpA);

	tmpB = m->B->getPosition();
	tmpB += correction * m->B->invMass;

	m->B->setPosition(tmpB);
}

float Collision::pythagorus(float a, float b)
{
	float a2 = a*a;
	float b2 = b*b;

	float c2 = a2 + b2;
	float c = sqrt(c2);

	return c;
}