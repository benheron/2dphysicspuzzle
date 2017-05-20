#pragma once
#include "ActivatableItem.h"
#include "../../Collision.h"

class Door : public ActivatableItem
{
public:
	Door(Texture* texture, Vec2 pos, Vec2 dimens, bool activated);
	~Door();

	/**
	@brief Update the Door
	@param dt The delta time.
	*/
	virtual void update(float dt);

	/**
	@brief Render the Door
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);



protected:
	Vec2 initialPos;
	Vec2 moveToPos;
	bool still;

	Vec2 changeVel;

	float dist;

	enum DoorState {
		open,
		close
	};

	DoorState dState;

};