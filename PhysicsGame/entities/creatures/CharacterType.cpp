#pragma once
#include "CharacterType.h"

#include "../../Utility.h"

CharacterType::CharacterType(Texture* spritesheet, std::string ID, std::string characterName, Vec2 spriteDimensions,
	float weight, float speed, float maxSpeed, float strength, float maxHealth, std::unordered_map<std::string, Animation*> animations) :
	spritesheet(spritesheet), ID(ID), characterName(characterName), spriteDimensions(spriteDimensions),
	weight(weight), speed(speed), maxSpeed(maxSpeed), strength(strength), maxHealth(maxHealth), animations(animations)
{
}

CharacterType::~CharacterType()
{

}

void CharacterType::render(SDL_Renderer *renderer, Vec2 pos, Vec2 dimensions, std::string newState, bool addFrame, Vec2 scale)
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

	//spritesheet->pushSpriteToScreen(renderer, pos, dimensions * scale, sp, sd);
}

Texture* CharacterType::getTexture()
{
	return spritesheet;
}

std::string CharacterType::getID()
{
	return ID;
}


Vec2 CharacterType::getSpriteDimensions()
{
	return spriteDimensions;
}

float CharacterType::getWeight()
{
	return weight;
}

float CharacterType::getSpeed()
{
	return speed;
}

float CharacterType::getMaxSpeed()
{
	return maxSpeed;
}

float CharacterType::getStrength()
{
	return strength;
}

float CharacterType::getMaxHealth()
{
	return maxHealth;
}

Vec2 CharacterType::getSpriteStateDimensions(std::string ssd)
{
	return animations[ssd]->getFrame(frame)->getFrameDimens();
}