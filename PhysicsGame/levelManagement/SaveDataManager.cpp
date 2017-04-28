#include "SaveDataManager.h"

SaveDataManager::SaveDataManager(std::string filePath, MapManager *mmng)
{

	loadSaveData(filePath, mmng);
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

			levelsID[levelID] = newLevel;
			levelsString.push_back(newLevel);
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