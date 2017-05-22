#pragma once
#include "State.h"
#include "../DataManager.h"
#include "ChooseLevelState.h"


class OnDeathState : public State
{
public:
	OnDeathState(StateManager* manager, Platform *platform, DataManager *d, bool &retry);
	~OnDeathState();

	/**
	@brief Handles any events such as keyboard/mouse input.

	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Update any internal values.

	@param dt - delta time.
	*/
	void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();

protected:

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();

	Button *retryButton;
	Button *quitMenuBtn;
	Button *quitDesktopBtn;

	std::vector<Button*> deathStateButtons;

	bool leftDown = false;

	DataManager *dtmng;

	Vec2 mousePos;

	bool &retry;

	Vec2 bgPos;

	Text* haveDied;

	Vec2 deathFacePos;
};