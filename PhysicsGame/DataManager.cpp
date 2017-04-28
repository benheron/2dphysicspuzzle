#include "DataManager.h"

DataManager::DataManager(Platform *platform, StateManager *stateManager)
{
	//manage tiles
	ttmng = new TileTypeManager("res/txt/tiles.txt", platform->getRenderer());
	//Creature + character loading test
	cmng = new CreatureManager("res/txt/creatures.txt", "res/txt/characters.txt", platform->getRenderer());
	//load map

	mmng = new MapManager("res/txt", ttmng, cmng, 0);

	sdmng = new SaveDataManager("res/txt/savedata.txt", mmng);

	imng = new ItemManager("res/txt/items.txt", platform->getRenderer());

	amng = new AudioManager("res/txt/audio.txt");

	timng = new TextImageManager("res/fonts/fontarial.txt", platform->getRenderer());

	pms = new PauseMenuState(stateManager, platform, this);
}

DataManager::~DataManager()
{

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