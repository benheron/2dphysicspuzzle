#include "DataManager.h"

DataManager::DataManager(Platform *platform, StateManager *stateManager)
{
	//manage tiles
	ttmng = new TileTypeManager("res/txt/tiles.txt", platform->getRenderer());
	//Creature + character loading test
	cmng = new CreatureManager("res/txt/creatures.txt", "res/txt/characters.txt", platform->getRenderer());
	//load map

	mmng = new MapManager("res/txt", ttmng, cmng, 0, platform->getRenderer());

	sdmng = new SaveDataManager("res/txt/savedata.txt", mmng, platform->getRenderer());

	imng = new ItemManager("res/txt/items.txt", platform->getRenderer());

	amng = new AudioManager("res/txt/audio.txt");

	timng = new TextImageManager("res/fonts/fontarial.txt", platform->getRenderer() );

	kmng = new KeyboardManager();

	asmng = new AssetManager(platform->getRenderer());

	pms = new PauseMenuState(stateManager, platform, this);
	
	
}

DataManager::~DataManager()
{
	delete ttmng;
	delete cmng;
	delete mmng;
	delete sdmng;
	delete imng;
	delete amng;
	delete timng;
	delete kmng;
	delete asmng;
	delete pms;
}

MapManager* DataManager::getMapManager()
{
	return mmng;
}

TileTypeManager* DataManager::getTileTypeManager()
{
	return ttmng;
}

CreatureManager* DataManager::getCreatureManager()
{
	return cmng;
}

SaveDataManager* DataManager::getSaveDataManager()
{
	return sdmng;
}

ItemManager* DataManager::getItemManager()
{
	return imng;
}

AudioManager* DataManager::getAudioManager()
{
	return amng;
}

TextImageManager* DataManager::getTextImageManager()
{
	return timng;
}

KeyboardManager* DataManager::getKeyboardManager()
{
	return kmng;
}

AssetManager* DataManager::getAssetManager()
{
	return asmng;
}

PauseMenuState* DataManager::getPauseMenuState()
{
	return pms;
}