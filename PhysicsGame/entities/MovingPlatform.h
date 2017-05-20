#pragma once
#include "items/ActivatableItem.h"
#include "../Collision.h"

class MovingPlatform : public ActivatableItem {
public:
	MovingPlatform(Texture* texture, Vec2 start, Vec2 end, Vec2 dimens, int speed, bool activated, bool reversing);
	~MovingPlatform();


	/**
	@brief Update the MovingPlatform
	@param dt The delta time.
	*/
	virtual void update(float dt);

	/**
	@brief Render the MovingPlatform
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);

	

	void setReversing(bool r);
	bool getReversing();

protected:
	int speed;
	
	bool reversing;

	bool reverseIt;

	Vec2 start;
	Vec2 end;

	float dist;
	Vec2 direction;

	

};