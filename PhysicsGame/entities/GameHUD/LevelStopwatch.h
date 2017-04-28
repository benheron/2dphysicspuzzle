#pragma once

#include <string>
#include "../Entity.h"
#include "../creatures/Character.h"
#include "../../Text.h"

class LevelStopwatch : public Entity
{
public:

	LevelStopwatch::LevelStopwatch(Vec2 pos, Vec2 dimensions, TextImageManager *timng);
	/**
	@brief Create the LevelStopwatch using the size of the Texture as the size of the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the LevelStopwatch.
	*/
	LevelStopwatch(Texture* texture, Vec2 pos);

	/**
	@brief Create the Entity.
	@param texture A pointer to the Texture.
	@param pos The position of the LevelStopwatch.
	@param dimensions The dimensions of the LevelStopwatch.
	*/
	LevelStopwatch(Texture* texture, Vec2 pos, Vec2 dimensions);



	/**
	@brief Create the LevelStopwatch with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the Entity.
	@param dimensions The dimensions of the LevelStopwatch.
	@param spritePos The position of the sprite in the spritesheet.
	*/
	LevelStopwatch(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos);

	/**
	@brief Create the LevelStopwatch with a sprite from a spritesheet.
	@param texture A pointer to the Texture.
	@param pos The position of the LevelStopwatch.
	@param dimensions The dimensions of the LevelStopwatch.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	*/
	LevelStopwatch(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos, Vec2 spriteDimensions);

	virtual ~LevelStopwatch();

	/**
	@brief Updates the Tile.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Render the Tile.
	@param renderer A pointer to the renderer.
	*/
	void render(SDL_Renderer* renderer);


	void stop();

	void start();

	bool isRunning();

	unsigned int getTime();

protected:
	bool running;

	Texture *timerText;

	unsigned int startTime;
	unsigned int elapsedTime;
	unsigned int lastTime;

	float now;

	std::string elapsedTimeString;

	TTF_Font *font = NULL;

	Text* minText;
	Text* secText;
	Text* milText;
	Text *spaceColonSpace;

	Text* elapsedTimeText;


};