#pragma once

#include "Creature.h"

class Grunt : public Creature
{
public:
	Grunt(Texture* texture, Vec2 pos, Vec2 dimens, CreatureType *ct, float speed);
	~Grunt();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	void moveLeft(float dt);
	void moveRight(float dt);

	void changeDirection();

	void setSpeed(float sp);
protected:
	
	enum GruntState {
		walking,
		idle
	};

	enum GruntDirection {
		leftDir,
		rightDir
	};

	GruntState gState;
	GruntDirection gDir;

	Vec2 dir;

	float speed;

	int localMaxSpeedX = 70;
	int localMaxSpeedY = 400;

	float dirTimer;

	float frameTiming = 0;
	float frameSecond;

	bool addFrame = false;

	Vec2 spriteScale;

};