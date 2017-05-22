#include "SaveDataManager.h"

SaveDataManager::SaveDataManager(std::string filePath, MapManager *mmng, SDL_Renderer* renderer)
{
	defaultImage = new Texture("res/img/icondefault.png", renderer);
	loadSaveData(filePath, mmng);
}

SaveDataManager::~SaveDataManager()
{
	for (int i = 0; i < levelsString.size(); i++)
	{
		delete levelsString[i];
	}
}

bool SaveDataManager::loadSaveData(std::string filePath, MapManager *mmng)
{
	

	Utility::log(Utility::I, "Loading save data : " + filePath);

	std::ifstream dataFile(filePath);

	if (dataFile.is_open())
	{
		dataFile >> numLevels;

		for (int i = 0; i < numLevels; i++)
		{
			std::string levelID;
			unsigned int fastestTime;
			int numSecrets;
			bool complete;

			dataFile >> levelID;
			dataFile >> fastestTime;
			dataFile >> numSecrets;
			dataFile >> complete;

			Level* newLevel = new Level(mmng->getMap(levelID), levelID, fastestTime, numSecrets, complete);
			newLevel->setLevelIndex(i);

			levelsID[levelID] = newLevel;
			levelsString.push_back(newLevel);

			theLevelIDs.push_back(levelID);

			//temp textures for level icons
			iconTexturesID[levelID] = mmng->getLevelIcon(levelID);
		}

		return true;
	}
	else {
		return false;
	}
}

Level* SaveDataManager::getLevelFromIndex(int i)
{
	return levelsString[i];
}

Level* SaveDataManager::getLevelFromID(std::string ID)
{
	return levelsID[ID];
}

int SaveDataManager::getNumLevels()
{
	return levelsString.size();
}

std::vector<std::string> SaveDataManager::getTheLevelIDs()
{
	return theLevelIDs;
}

Texture* SaveDataManager::getLevelIconFromID(std::string ID)
{
	return iconTexturesID[ID];
}