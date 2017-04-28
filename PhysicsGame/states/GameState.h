#pragma once

#include "State.h"
#include "StateManager.h"
#include "../DataManager.h"
#include "PauseMenuState.h"
#include "GameOverState.h"
#include "ChooseLevelState.h"
#include "../Platform.h"
#include "../levelManagement/TileTypeManager.h"
#include "../levelManagement/MapManager.h"
#include "../levelManagement/Map.h"
#include "../entities/particles/ParticleSystem.h"
#include "../entities/creatures/CreatureManager.h"
#include "../levelManagement/MapRoom.h"

#include "../entities/GameHUD/HealthIcon.h"
#include "../entities/GameHUD/LevelStopWatch.h"

#include "../entities/shapes/Circle.h"
#include "../entities/shapes/Square.h"

#include "../entities/PressurePad.h"
#include "../entities/MapExit.h"
#include <stdio.h>

#include "../Raycast.h"

//#include "..entities/creatures/Character.h"

/**
@class GameState
@brief A game state that contains the game itself
*/
class GameState : public State
{
public:

	/**
	@brief Create the GameState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	GameState(StateManager* manager, Platform *platform, DataManager *dtmng, Level *level);
	
	virtual ~GameState();

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


	void saveLevel();





	void resolveCollision(Square* a, Square* b);

	void letBodyGo();

	void throwBody();



	MapRoom *currentMap;

	CharacterType *playerType;

	ParticleSystem* particles;

	//Character *player;


	TileTypeManager *ttmng;
	CreatureManager *cmng;
 	MapManager *mmng;

	PauseMenuState *pms;


	DataManager *dtmng;

	int mode;

	int changeThisState = 0;

	bool esc = false;

	bool kUp = false, kDown = false, kLeft = false, kRight = false;




	HealthIcon *health;


	Texture *circleTexture;
	Texture *squareTexture;




	Square *box;
	Square *box2;
	Square *box3;
	Square *box4;
	Square *box5;
	Square *box6;

	Circle *circ;
	Circle *circ2;
	Circle *circ3;
	Circle *circ4;
	Circle *circ5;

	std::vector<Square*> squares;
	std::vector<Circle*> circles;

	float power = 0;

	///font used
	TTF_Font *font = NULL;

	LevelStopwatch *levelTime;

	Texture *pressPadB;
	Texture *pressPadT;

	Texture *pressPad;

	PressurePad *pp1;

	MapExit *exitm;

	Texture *white;


	int numSecretsFound = 0;
	bool levelComplete = false;
	bool writtenToFile = false;
	unsigned int time = 0;

	Level *level;

	Vec2 mousePos;

	bool bodyPick = false;
	int bodyPickIndex;
	//bool throwBody = false;

	Square *jumphitbox;
	bool jumphitcollide;

	bool canJump;
	bool canDash;
	bool dash;

	int dashTimer;

	Manifold *m = new Manifold();

	Character *player;
};