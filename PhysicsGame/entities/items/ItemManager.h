#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "ItemType.h"
#include "../../Utility.h"
#include "../../Texture.h"

/**
@brief Contains all the data and functions to manage the Map Objects.
*/
class ItemManager
{
public:
	/**
	@brief Creates the ItemManager to load in the Map files
	@param filePath The path to the file which holds the initial map data.
	*/
	ItemManager(std::string filePath, SDL_Renderer *renderer);

	/**
	@brief ItemManager destructor.
	*/
	~ItemManager();

	/**
	@brief Loads in the Map data.
	@param filePath The path to the file which holds the map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	*/
	bool loadItemData(std::string filePath, SDL_Renderer *renderer);


	ItemType* getItemTypeByID(std::string ID);
	ItemType* getItemTypeByName(std::string itemName);
	



protected:
	///An unordered map of the creature types
	std::unordered_map<std::string, ItemType*> itemTypesID;
	std::unordered_map<std::string, ItemType*> itemTypesName;


};