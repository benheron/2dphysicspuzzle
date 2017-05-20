#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Texture* texture, Vec2 start, Vec2 end, Vec2 dimens, int speed, bool activated, bool reversing) : ActivatableItem(texture, start, dimens, activated), start(start), end(end), speed(speed), reversing(reversing)
{
	dist = Collision::distanceBetween(start, end);

	Vec2 dir = end - start;
	direction = dir.normalize();
	mass = 0;


	staticFriction = 1;
	dynamicFriction = 0.5;
	//velocity = direction *speed;
	velocity = 0;

	reverseIt = false;
}

MovingPlatform::~MovingPlatform()
{

}

void MovingPlatform::update(float dt)
{
	if (activated)
	{
		//if (pos != end)
		{
			if (Collision::distanceBetween(start, pos) > dist)
			{
				if (reversing)
				{
					direction *= -1;
					velocity *= -1;
					Vec2 tmp = start;
					start = end;
					end = tmp;
				}
				else {
					//activated = false;
					pos = end;
					velocity = 0;
				}

			}
			else {
				if (pos != end)
				{
					velocity = direction *speed;
					pos += velocity * dt;
				}
				else {
					if (reversing)
					{
						direction *= -1;
						velocity *= -1;
						Vec2 tmp = start;
						start = end;
						end = tmp;
					}
				}
				
			}
//		} else {
			//velocity = 0;
		}

	}
	else
	{
		if (reversing)
		{
			velocity = 0;
		}
		else {
			if (pos != start)
			{
				velocity = direction *speed *-1;
				pos += velocity *dt;
				if (Collision::distanceBetween(end, pos) > dist)
				{
					pos = start;
				}
				
			}
			else {
				velocity = 0;
			}
			
		}

		if (!reversing)
		{

		}
		
	}
}

void MovingPlatform::render(SDL_Renderer* renderer)
{
	texture->pushSpriteToScreen(renderer, pos, 0, dimensions);
}



void MovingPlatform::setReversing(bool r)
{
	reversing = r;
}

bool MovingPlatform::getReversing()
{
	return reversing;
}