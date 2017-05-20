#pragma once

#include "levelManagement/MapManager.h"
#include "levelManagement/TileTypeManager.h"
#include "levelManagement/SaveDataManager.h"
#include "entities/creatures/CharacterManager.h"
#include "entities/items/ItemManager.h"
#include "audio/AudioManager.h"
#include "TextImageManager.h"
#include "AssetManager.h"

#include "states/PauseMenuState.h"
#include "Keyboard.h"

class DataManager {
public:
	DataManager(Platform *platform, StateManager *manager);
	~DataManager();

	//getAudioManager()
	MapManager* getMapManager();
	TileTypeManager* getTileTypeManager();
	CreatureManager* getCreatureManager();
	SaveDataManager* getSaveDataManager();
	ItemManager* getItemManager();
	AudioManager* getAudioManager();
	TextImageManager* getTextImageManager();
	KeyboardManager* getKeyboardManager();
	AssetManager* getAssetManager();
	PauseMenuState* getPauseMenuState();
	

protected:


	TileTypeManager *ttmng;
	CreatureManager *cmng;
	MapManager *mmng;
	SaveDataManager *sdmng;
	ItemManager *imng;
	AudioManager *amng;
	TextImageManager* timng;

	PauseMenuState *pms;

	KeyboardManager *kmng;

	AssetManager *asmng;
};