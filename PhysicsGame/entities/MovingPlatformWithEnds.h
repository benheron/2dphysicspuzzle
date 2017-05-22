#pragma once
#include "MovingPlatform.h"
#include "../Collision.h"

class MovingPlatformWithEnds : public Entity
{
public:
	MovingPlatformWithEnds(Texture* endsTexture, Texture* dashTexture, Texture*movingPlatformTexture, Vec2 start, Vec2 end, Vec2 dimens, int speed, bool activated, bool reversing);
	~MovingPlatformWithEnds();


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

	void setActivated(bool a);
	bool getActivated();

	MovingPlatform* getMovingPlatform();

	bool checkPlatformCollision(Manifold *m);

	bool checkCrushPlayer(Manifold *m);

protected:
	MovingPlatform* mp;
	Texture* endsTexture;
	Texture* dashTexture;

	Vec2 dashSize;
	float dashAngle;
	float dashLength;

	Vec2 startPos;
	Vec2 endPos;
	
	std::vector<Vec2> dashPos;

	Square *crushSquare;

};