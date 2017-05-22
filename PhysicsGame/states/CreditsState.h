#pragma once

#include "State.h"
#include "StateManager.h"
#include "../DataManager.h"

/**
@class PauseMenuState
@brief The editor state to customise generation
*/
class CreditsState : public State
{
public:

	/**
	@brief Create the PauseMenuState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	CreditsState(StateManager* manager, Platform *platform, DataManager *d);

	virtual ~CreditsState();

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


	

	DataManager *dtmng;


	Texture* credits;
};