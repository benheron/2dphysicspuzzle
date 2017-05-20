#include "Circle.h"


Circle::Circle(Texture* texture, Vec2 pos) : Body(texture, pos)
{
	radius = 16;

}

Circle::Circle(Texture* texture, Vec2 pos, Vec2 dimensions) : Body(texture, pos, dimensions)
{
	spritePos = 0;
	radius = 16;
}


Circle::Circle(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Body(texture, pos, dimensions, spritePos)
{
	radius = 16;
}

Circle::~Circle()
{

}

void Circle::buildCircle()
{

}

void Circle::update(float dt) 
{
	//Body::update(dt);
	

}


void Circle::render(SDL_Renderer *renderer)
{
	texture->pushSpriteToScreen(renderer, pos, 0, spriteDimensions);

}


bool Circle::isHover()
{
	return hover;
}

void Circle::setHover(bool h)
{
	hover = h;
}

void Circle::setSelected(bool s)
{
	selected = s;
}

bool Circle::getSelected()
{
	return selected;
}

/*
void Circle::setRadius(float r)
{
	radius = r;
}

float Circle::getRadius()
{
	return radius;
}*/