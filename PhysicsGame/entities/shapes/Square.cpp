#include "Square.h"


Square::Square(Vec2 pos, Vec2 dimensions) : Entity(pos, dimensions)
{
	spritePos = 0;
	bounciness = 0.5;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
	mass = 0.5;
}

Square::Square(Texture* texture, Vec2 pos) : Entity(texture, pos)
{
	bounciness = 0.5;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
	mass = 0.5;
}

Square::Square(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	spritePos = 0;
	bounciness = 0.5;
	staticFriction = 0.4;
	dynamicFriction = 0.2;
	mass = 0.5;
}


Square::Square(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{

}

Square::~Square()
{

}

void Square::buildSquare()
{

}

void Square::update(float dt)
{
	
	if (gravityOn)
	{
		float accY = 0;
		accY += 200;


		velocity.y += accY *dt;

		



		/*int maxSpeed = 400;

		if (velocity.x > maxSpeed)
		{
			velocity.x = maxSpeed;
		}

		if (velocity.x < -maxSpeed)
		{
			velocity.x = -maxSpeed;
		}

		if (velocity.y > maxSpeed)
		{
			velocity.y = maxSpeed;
		}

		if (velocity.y < -maxSpeed)
		{
			velocity.y = -maxSpeed;
		}*/

	}
	/*velocity.x *= 0.991;

	if (velocity.x < 0.05 && velocity.x > -0.05)
	{
		velocity.x = 0;
	}*/
	
	pos += velocity * dt;




}


void Square::render(SDL_Renderer *renderer)
{
	texture->pushSpriteToScreen(renderer, pos, spritePos, spriteDimensions);
}


