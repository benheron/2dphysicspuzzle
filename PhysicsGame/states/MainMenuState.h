#pragma once

#include "State.h"
#include "../Platform.h"
#include "StateManager.h"
#include "../entities/Button.h"
#include "../Texture.h"
#include "GameState.h"

#include "PauseMenuState.h"
#include "ChooseLevelState.h"
#include "../audio/SFXR.h"
#include "../audio/MusicR.h"
#include "../audio/audio.h"

#include "../Text.h"

/**
@class MainMenuState
@brief The main menu state to the different parts of the project
*/
class MainMenuState : public State
{
public:

	/**
	@brief Create the MainMenuState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	MainMenuState(StateManager* manager, Platform *platform, DataManager *d);

	virtual ~MainMenuState();

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

	Button *redPlay;

	Texture *playTexture;
	Texture *editorTexture;

	bool redDown = false;
	bool greenDown = false;

	std::vector<Button*> mainMenuButtons;

	DataManager *dtmng;

	
};