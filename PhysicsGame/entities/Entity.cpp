#include "Entity.h"


Entity::Entity(Vec2 pos) :pos(pos)
{

}

Entity::Entity(Vec2 pos, Vec2 dimensions) :pos(pos), dimensions(dimensions)
{

}

Entity::Entity(Texture* texture, Vec2 pos) 
	: texture(texture), pos(pos), spritePos(Vec2())
{
	dimensions = texture->getDimensions();
	spriteDimensions = texture->getDimensions();
}

Entity::Entity(Texture* texture, Vec2 pos, Vec2 dimensions) 
	: texture(texture), pos(pos), dimensions(dimensions), spritePos(Vec2())
{
	spriteDimensions = texture->getDimensions();
}

Entity::Entity(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos)
	: texture(texture), pos(pos), dimensions(dimensions), spritePos(spritePos)
{
	spriteDimensions = dimensions;
}

Entity::Entity(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions)
	: texture(texture), pos(pos), dimensions(dimensions), spritePos(spritePos), spriteDimensions(spriteDimensions)
{
}

Entity::~Entity()
{
}

void Entity::render(SDL_Renderer* renderer)
{
	//texture->pushSpriteToScreen(renderer, pos, dimensions, spritePos, spriteDimensions);
}

void Entity::setPosition(Vec2 pos)
{
	lastPos = pos;
	this->pos = pos;
}

void Entity::setDimensions(Vec2 dimensions)
{
	this->dimensions = dimensions;
}

Vec2 Entity::getPosition()
{
	return pos;
}

Vec2 Entity::getDimensions()
{
	return dimensions;
}



bool Entity::mouseCollide(int mouseX, int mouseY)
{
	if (mouseX > pos.x &&
		mouseX < (pos.x + dimensions.x) &&
		mouseY > pos.y &&
		mouseY < (pos.y + dimensions.y))
	{
		return true;
	}
	return false;


} 

void Entity::setRadius(float r)
{
	radius = r;
}

float Entity::getRadius()
{
	return radius;
}


Vec2 Entity::getLastPos()
{
	return lastPos;
}


void Entity::setGravityOn(bool g) {
	gravityOn = g;
}

bool Entity::isGravityOn() {
	return gravityOn;
}

Vec2 Entity::getCentre() {
	float x = pos.x + dimensions.x / 2;
	float y = pos.y + dimensions.y / 2;

	return Vec2(x, y);
}




std::string Entity::getID()
{
	return itemID;
}

float Entity::getBounciness()
{
	return bounciness;
}