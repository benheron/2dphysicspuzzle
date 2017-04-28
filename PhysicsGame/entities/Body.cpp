#include "Body.h"


Body::Body(Texture* texture, Vec2 pos) : Entity(texture, pos)
{
	radius = 16;

}

Body::Body(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	spritePos = 0;
	radius = 16;
}


Body::Body(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{
	radius = 16;
}

Body::~Body()
{

}

void Body::buildBody()
{

}

void Body::update(float dt)
{

	if (gravityOn)
	{
		float accY = 0;
		accY += 2;


		velocity.y += accY;



	}
	pos += velocity * dt;

}


void Body::render(SDL_Renderer *renderer)
{
	texture->pushSpriteToScreen(renderer, pos, 0, spriteDimensions);

}



/*
void Body::setRadius(float r)
{
radius = r;
}

float Body::getRadius()
{
return radius;
}*/