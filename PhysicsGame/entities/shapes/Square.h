#pragma once
#include "../Entity.h"
#include "SDL_ttf.h"

/**
@brief Creates all data for the Square
*/
class Square : public Entity
{
public:

	Square();
	virtual ~Square();


	Square(Vec2 pos, Vec2 dimensions);

	/**
	@brief Create the Square using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Square.
	*/
	Square(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the Square.
	@param dimensions The dimensions of the Square.
	*/
	Square(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the Square with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the Square.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	Square(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the Square with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Square.
	@param dimensions The dimensions of the Square.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	Square(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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



protected:
	/**
	@brief Builds the Square in this function
	*/
	void buildSquare();

	///The Square background
	Texture *SquareBgr;

	///The text used on the Square
	TTF_Font *font = NULL;

	///If displaying the hover image
	bool hover = false;

	///if displaying the selected image
	bool selected = false;

	float radius;





};