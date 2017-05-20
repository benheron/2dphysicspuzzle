#pragma once
#include "Creature.h"
#include "../../Raycast.h"
#include "Character.h"

class Sentinel : public Creature
{
public:
	Sentinel(Texture* sentinel, Texture* laser, Vec2 pos, Vec2 dimens, CreatureType* ct);
	~Sentinel();

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

	void setLockedOn(bool lo);
	void setLockedOn(bool lo, Character* t);

	bool getLockedOn();

	void moveLaserTo(Vec2 laserToPos);

	std::vector<Vec2> getLaserPoints();

	void setLaserPointsToRender(int lp);


protected:

	bool isLockedOn;

	Texture* laserText;
	Vec2 laserPos;
	Vec2 laserDir;
	float laserlength;
	Raycast *laser;
	Character* theTarget;

	int laserPointsToRender;



	enum SentinelState {
		lockedOn,
		centring,
		passive
	};
	SentinelState sstate;

	float lockedOnTime = 0;
};