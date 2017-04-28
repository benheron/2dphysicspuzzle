#pragma once
#include <string>
#include <vector>
#include "../../Vec2.h"
#include "../../Texture.h"

class ItemType {
public:
	ItemType(Texture* spritesheet, std::string ID, std::string creatureName, Vec2 spriteDimensions, float mass);
	~ItemType();

	Texture *getSpriteSheet();
	std::string getID();
	std::string getName();
	Vec2 getSpriteDimensions();
	float getMass();


protected:
	Texture *spritesheet;
	std::string ID;
	std::string name;
	Vec2 spriteDimensions;
	float mass;

};