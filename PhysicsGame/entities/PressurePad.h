#pragma once
#include "items/ActivatableItem.h"

/**
@brief Creates all data for the PressurePad
*/
class PressurePad : public Entity
{
public:

	virtual ~PressurePad();


	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the PressurePad.
	@param dimensions The dimensions of the PressurePad.
	*/
	PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions, ActivatableItem *ai);




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



	void setActivate(bool a);

	bool getActivate();



protected:
	/**
	@brief Builds the PressurePad in this function
	*/
	void buildPressurePad();

	///The PressurePad background
	//Texture *PressurePadBgr;

	bool activated;

	ActivatableItem *linkedItem;

};