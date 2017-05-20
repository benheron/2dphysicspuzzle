#include "Tile.h"
#include "../Utility.h"

Tile::Tile(Vec2 pos, Vec2 dimensions, TileType *tileType) : Entity(pos, dimensions), tileType(tileType)
{
	mass = 0;
	invMass = 0;

	collidable = tileType->getCollidable();
	destructible = tileType->getDamageValue();
	bounciness = tileType->getBounciness();
	climbable = tileType->getClimbable();
	damageValue = tileType->getDamageValue();


	sideL = false;
	sideR = false;
	sideU = false;
	sideD = false;

	staticFriction = 0.7;
	dynamicFriction = 0.6;
}

Tile::Tile(Texture* texture, Vec2 pos, Vec2 dimensions, TileType *tileType) : Entity(texture, pos, dimensions), tileType(tileType)
{
	mass = 0;
	invMass = 0;


}

Tile::Tile(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions, TileType* tileType)
	: Entity(texture, pos, dimensions, spritePos, spriteDimensions), tileType(tileType)
{
	mass = 0;
	invMass = 0;
}

Tile::~Tile()
{
}

void Tile::update(float dt)
{
}

void Tile::render(SDL_Renderer *renderer)
{
	//If the Tile does not have a blank ID then render to the Tile
	if (tileType->getID() != "XX")
	{
		tileType->render(renderer, pos, dimensions);
	}
}

bool Tile::haveBlankID()
{
	return (tileType->getID() == "XX") ? true : false;
}

void Tile::setTileType(std::string ID, TileTypeManager *ttmng)
{
	tileType = ttmng->getTileType(ID);
}

std::string Tile::getTileTypeID()
{
	return tileType->getID();
}


bool Tile::getCollidable()
{
	return collidable;
}

bool Tile::getDestructible()
{
	return destructible;
}

float Tile::getFrictionValue()
{
	return frictionValue;
}

float Tile::getDamageValue()
{
	return damageValue;
}

bool Tile::getClimbable()
{
	return climbable;
}

void Tile::setSideR(bool s)
{
	sideR = s;
}

bool Tile::getSideR()
{
	return sideR;
}

void Tile::setSideL(bool s)
{
	sideL = s;
}

bool Tile::getSideL()
{
	return sideL;
}

void Tile::setSideU(bool s)
{
	sideU = s;
}

bool Tile::getSideU()
{
	return sideU;
}

void Tile::setSideD(bool s)
{
	sideD = s;
}

bool Tile::getSideD()
{
	return sideD;
}