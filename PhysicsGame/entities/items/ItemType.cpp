#include "ItemType.h"

ItemType::ItemType(Texture* spritesheet, std::string ID, std::string name, Vec2 spriteDimensions, float mass) : 
	spritesheet(spritesheet), ID(ID), name(name), spriteDimensions(spriteDimensions), mass(mass)
{

}

ItemType::~ItemType()
{

}

Texture* ItemType::getSpriteSheet()
{
	return spritesheet;
}

std::string ItemType::getID()
{
	return ID;
}

std::string ItemType::getName()
{
	return name;
}

Vec2 ItemType::getSpriteDimensions()
{
	return spriteDimensions;
}

float ItemType::getMass()
{
	return mass;
}