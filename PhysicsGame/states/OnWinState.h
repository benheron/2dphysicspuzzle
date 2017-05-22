#pragma once
#include "State.h"
#include "../DataManager.h"
#include "ChooseLevelState.h"


class OnWinState : public State
{
public:
	OnWinState(StateManager* manager, Platform *platform, DataManager *d, bool &retry, LevelStopwatch* levelTime, Level *curLevel);
	~OnWinState();

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

	Button *nextlevelBtn;
	Button *retryButton;
	Button *quitMenuBtn;
	Button *quitDesktopBtn;

	std::vector<Button*> winStateButtons;

	bool leftDown = false;

	DataManager *dtmng;

	Vec2 mousePos;

	bool &retry;

	Vec2 bgPos;

	Text* levelComplete;
	LevelStopwatch *levelTime;

	std::string levTimeString;
	Text* levTimeEnd;

	Level *curLevel;
};