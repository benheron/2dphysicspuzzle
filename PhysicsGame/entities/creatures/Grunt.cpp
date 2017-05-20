#include "Grunt.h"

Grunt::Grunt(Texture* texture, Vec2 pos, Vec2 dimens, CreatureType *ct, float speed) : Creature (texture, pos, dimens, ct), speed(speed)
{
	dir = Vec2(1, 0);
	gDir = rightDir;
	gState = walking;

	dirTimer = 0;
	gravityOn = true;
}

Grunt::~Grunt()
{

}

void Grunt::update(float dt)
{
	frameTiming += dt;


	if (frameTiming > 0.033)
	{
		if (velocity.getLength() > 0)
		{
			addFrame = true;
			frameTiming = 0;
		}
	}
	else {
		addFrame = false;
	}


	if (gravityOn)
	{
		float accY = 0;

		accY += 400;

		velocity.y += accY*dt;
	}
	//Utility::log(Utility::I, Utility::floatToString(velocity.x));

	if (velocity.x > 0)
	{
		gDir = rightDir;
	}
	else if (velocity.x < 0)
	{
		gDir = leftDir;
	}

	if (dirTimer > 0)
	{
		dirTimer -= dt;
	}
	else {
		dirTimer = 0;
	}

	if (abs(velocity.x) < 5 && dirTimer <= 0)
	{
		changeDirection();
	}

	velocity += dir * speed;

	if (velocity.x < 0)
	{
		spriteScale = Vec2(-1, 0);
		if (velocity.x < -localMaxSpeedX)
		{
			velocity.x = -localMaxSpeedX;
		}
	}
	else {
		spriteScale = Vec2(1, 0);
		if (velocity.x > localMaxSpeedX)
		{
			velocity.x = localMaxSpeedX;
		}
	}

	

	switch (gState)
	{
	case Grunt::walking:
		
		pos += velocity *dt;
		break;
	case Grunt::idle:
		break;
	default:
		break;
	}


}

void Grunt::render(SDL_Renderer* renderer)
{
	

	
	switch (gState)
	{
	case Grunt::walking:

		creatureType->render(renderer, pos, dimensions, "W", addFrame, spriteScale);
		break;
	case Grunt::idle:
		break;
	default:
		break;
	}
}

void Grunt::moveLeft(float dt)
{
	
}

void Grunt::moveRight(float dt)
{
	if (velocity.x < localMaxSpeedX)
	{
		velocity.x += speed;

		if (velocity.x > localMaxSpeedX)
		{
			velocity.x = localMaxSpeedX;
		}
	}
}

void Grunt::changeDirection()
{
	dir.x *= -1;
	dirTimer = 0.6;
}

void Grunt::setSpeed(float sp)
{
	speed = sp;
}