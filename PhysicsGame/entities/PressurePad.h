#pragma once
#include "Entity.h"
#include "SDL_ttf.h"

/**
@brief Creates all data for the PressurePad
*/
class PressurePad : public Entity
{
public:

	PressurePad();
	virtual ~PressurePad();

	/**
	@brief Create the PressurePad using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the PressurePad.
	*/
	PressurePad(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the PressurePad.
	@param dimensions The dimensions of the PressurePad.
	*/
	PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the PressurePad with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the PressurePad.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the PressurePad with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the PressurePad.
	@param dimensions The dimensions of the PressurePad.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	PressurePad(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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
	Texture *PressurePadBgr;

	///The text used on the PressurePad
	TTF_Font *font = NULL;

	///If displaying the hover image
	bool hover = false;

	///if displaying the selected image
	bool selected = false;

	float radius;

	bool activated = false;




};