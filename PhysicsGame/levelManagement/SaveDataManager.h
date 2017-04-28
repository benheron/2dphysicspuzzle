
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Tile.h"
#include "Map.h"
#include "TileTypeManager.h"
#include "MapManager.h"
#include "../entities/creatures/Creature.h"
#include "../entities/creatures/CreatureManager.h"
#include "../Utility.h"
#include "RoomTemplate.h"
#include "Level.h"

class Level;

/**
@brief Contains all the data and functions to manage the Map Objects.
*/
class SaveDataManager
{
public:
	/**
	@brief Creates the SaveDataManager to load in the Map files
	@param filePath The path to the file which holds the initial map data.
	*/
	SaveDataManager(std::string filePath, MapManager *mmng);

	/**
	@brief SaveDataManager destructor.
	*/
	~SaveDataManager();

	/**
	@brief Loads in the Map data.
	@param filePath The path to the file which holds the map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	*/
	bool loadSaveData(std::string filePath, MapManager *mmng);

	Level* getLevelFromIndex(int i);

	Level* getLevelFromID(std::string ID);


	int getNumberLevels();

private:
	std::unordered_map<std::string, Level*> levelsID;
	std::vector<Level*> levelsString;

	int numLevels;


};