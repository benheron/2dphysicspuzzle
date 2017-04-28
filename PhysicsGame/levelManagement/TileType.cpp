#include "TileType.h"

TileType::TileType(Texture* spritesheet, std::string iD, Vec2 spriteIndexPositions, Vec2 spriteDimensions,
	bool collidable, bool destructible, float frictionValue, float bounciness, float damageValue, bool climbable)
	: spritesheet(spritesheet), iD(iD), spriteIndexPositions(spriteIndexPositions), spriteDimensions(spriteDimensions), 
	collidable(collidable), destructible(destructible), frictionValue(frictionValue), bounciness(bounciness), damageValue(damageValue), climbable(climbable)
	
{
	spritePosition = spriteIndexPositions * spriteDimensions;
}

TileType::~TileType()
{

}

void TileType::render(SDL_Renderer* renderer, Vec2 pos, Vec2 dimensions)
{
	spritesheet->pushSpriteToScreen(renderer, pos, dimensions, spritePosition, spriteDimensions);
}

bool TileType::getCollidable()
{
	return collidable;
}

bool TileType::getDestructible()
{
	return destructible;
}

float TileType::getFrictionValue()
{
	return frictionValue;
}

float TileType::getBounciness()
{
	return bounciness;
}

float TileType::getDamageValue()
{
	return damageValue;
}

bool TileType::getClimbable()
{
	return climbable;
}

Texture* TileType::getTexture()
{
	return spritesheet;
}

std::string TileType::getID()
{
	return iD;
}

Vec2 TileType::getSpritePos()
{
	return spritePosition;
}

Vec2 TileType::getSpriteDimensions()
{
	return spriteDimensions;
}