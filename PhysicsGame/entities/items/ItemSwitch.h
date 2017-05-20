#pragma once
#include "ActivatableItem.h"

class ItemSwitch : public Entity
{
public:
	virtual ~ItemSwitch();


	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the PressurePad.
	@param dimensions The dimensions of the PressurePad.
	*/
	ItemSwitch(Texture* texture, Vec2 pos, Vec2 dimensions, ActivatableItem *ai);




	/**
	@brief Update the Creature.
	@param dt The delta time.
	*/
	virtual void update(float dt);


	/**
	@brief Render the Creature.
	@param renderer A pointer to the renderer.
	*/
	virtual void render(SDL_Renderer* renderer);



	void activate();

	bool getActivate();



protected:


	///The PressurePad background
	//Texture *PressurePadBgr;

	bool activated;
	Vec2 activatedSpritePos;

	ActivatableItem *linkedItem;
};