#pragma once

#include "State.h"
#include "StateManager.h"
#include "../Platform.h"
#include "../Texture.h"
#include "GameState.h"
#include "PauseMenuState.h"
#include "../entities/particles/ParticleSystem.h"
#include "../entities/creatures/CreatureManager.h"
#include "../levelManagement/MapRoom.h"
#include "../levelManagement/TileTypeManager.h"
#include "../levelManagement/MapManager.h"
#include "../levelManagement/Map.h"
#include "../levelManagement/TileSelection.h"

#include "../entities/Button.h"

#include "../UI/LevelIcon.h"




/**
@class ChooseLevelState
@brief The editor state to customise generation
*/
class ChooseLevelState : public State
{
public:

	/**
	@brief Create the ChooseLevelState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	ChooseLevelState(StateManager* manager, Platform *platform, DataManager *d);

	virtual ~ChooseLevelState();

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

	///local reference to the tile type manager
	TileTypeManager *ttmng;

	///local reference to the creature manager
	CreatureManager *cmng;

	///local reference to the map manager
	MapManager *mmng;

	PauseMenuState *pms;

	Vec2 mousePos;

	std::vector<Button*> levelButtons;

	std::vector<LevelIcon*> levelIcons;


	Texture *white;

	Texture *levTex1;
	Texture *levTex2;
	Texture *levTex3;

	bool playLevel = false;
	std::string levelToPlay;

};