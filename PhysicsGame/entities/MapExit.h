#pragma once
#include "Entity.h"
#include "SDL_ttf.h"

/**
@brief Creates all data for the MapExit
*/
class MapExit : public Entity
{
public:

	MapExit();
	virtual ~MapExit();

	/**
	@brief Create the MapExit using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the MapExit.
	*/
	MapExit(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the MapExit.
	@param dimensions The dimensions of the MapExit.
	*/
	MapExit(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the MapExit with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the MapExit.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	MapExit(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the MapExit with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the MapExit.
	@param dimensions The dimensions of the MapExit.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	MapExit(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);




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

	void setOpen(bool o);

	bool getOpen();


protected:
	/**
	@brief Builds the MapExit in this function
	*/
	void buildMapExit();

	///The MapExit background
	Texture *MapExitBgr;

	///The text used on the MapExit
	TTF_Font *font = NULL;

	///If displaying the hover image
	bool hover = false;

	///if displaying the selected image
	bool selected = false;

	float radius;

	bool opened = false;





};