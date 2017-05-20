#include "CreatureType.h"

#include "../../Utility.h"

CreatureType::CreatureType(Texture* spritesheet, std::string ID, std::string creatureName, Vec2 spriteDimensions,
	float weight, float speed, float maxSpeed, float strength, float maxHealth, std::unordered_map<std::string, Animation*> animations) :
	spritesheet(spritesheet), ID(ID), creatureName(creatureName), spriteDimensions(spriteDimensions),
	weight(weight), speed(speed), maxSpeed(maxSpeed), strength(strength), maxHealth(maxHealth), animations(animations)
{
}

CreatureType::~CreatureType()
{

}

void CreatureType::render(SDL_Renderer *renderer, Vec2 pos, Vec2 dimensions, std::string newState, bool addFrame, Vec2 scale)
{
	state = newState;

	Animation *a = animations[state];
	int numFrames = a->getNumFrames();

	if (addFrame)
	{
		frame += 1;
	}

	if (state != lastState)
	{
		frame = 0;
	}

	if (frame >= numFrames)
	{
		frame = 0;
	}

	Vec2 sp = animations[state]->getFrame(frame)->getFramePos();
	Vec2 sd = animations[state]->getFrame(frame)->getFrameDimens();

	lastState = state;

	if (scale.x < 0)
	{
		spritesheet->pushSpriteToScreen(renderer, pos, sd, sp, sd, SDL_FLIP_HORIZONTAL);
	}
	else {
		spritesheet->pushSpriteToScreen(renderer, pos, sd, sp, sd, SDL_FLIP_NONE);
	}


	//spritesheet->pushSpriteToScreen(renderer, pos, dimensions, 0, spriteDimensions);
}

Texture* CreatureType::getTexture()
{
	return spritesheet;
}

std::string CreatureType::getID()
{
	return ID;
}


Vec2 CreatureType::getSpriteDimensions()
{
	return spriteDimensions;
}

float CreatureType::getWeight()
{
	return weight;
}

float CreatureType::getSpeed()
{
	return speed;
}

float CreatureType::getMaxSpeed()
{
	return maxSpeed;
}

float CreatureType::getStrength()
{
	return strength;
}

float CreatureType::getMaxHealth()
{
	return maxHealth;
}

