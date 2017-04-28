#pragma once
#include "../Entity.h"
#include "../Body.h"
#include "SDL_ttf.h"

/**
@brief Creates all data for the Circle
*/
class Circle : public Body
{
public:

	Circle();
	virtual ~Circle();

	/**
	@brief Create the Circle using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Circle.
	*/
	Circle(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Circle.
	@param dimensions The dimensions of the Circle.
	*/
	Circle(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the Circle with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Circle.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	Circle(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the Circle with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Circle.
	@param dimensions The dimensions of the Circle.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	Circle(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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
	@brief Builds the Circle in this function
	*/
	void buildCircle();

	///The Circle background
	Texture *CircleBgr;

	///The text used on the Circle
	TTF_Font *font = NULL;

	///If displaying the hover image
	bool hover = false;

	///if displaying the selected image
	bool selected = false;

	//float radius;




};