#pragma once
#include "Entity.h"
#include "SDL_ttf.h"

/**
@brief Creates all data for the Body
*/
class Body : public Entity
{
public:

	Body();
	virtual ~Body();

	/**
	@brief Create the Body using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Body.
	*/
	Body(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Body.
	@param dimensions The dimensions of the Body.
	*/
	Body(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the Body with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Body.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	Body(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the Body with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Body.
	@param dimensions The dimensions of the Body.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	Body(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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

	//bool mouseCollide(int mouseX, int mouseY);


	/**
	@brief Get the hover value
	*/
	bool isHover();

	/**
	@brief Sets the hover value
	@param h The hover value to set to
	*/
	void setHover(bool h);

	/**
	@brief Sets the selected value
	@param s The selected value to set to
	*/
	void setSelected(bool s);

	/**
	@brief Gets the selected value
	*/
	bool getSelected();


	/*void setRadius(float r);

	float getRadius();*/


protected:
	/**
	@brief Builds the Body in this function
	*/
	void buildBody();

	///The Body background
	Texture *BodyBgr;

	///The text used on the Body
	TTF_Font *font = NULL;


	float radius;


};