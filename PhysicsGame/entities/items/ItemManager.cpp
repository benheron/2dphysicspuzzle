#pragma once
#include "ItemManager.h"

ItemManager::ItemManager(std::string filePath, SDL_Renderer *renderer)
{
	loadItemData(filePath, renderer);
}

ItemManager::~ItemManager()
{
	itemTypesID.clear();
}

bool ItemManager::loadItemData(std::string filePath, SDL_Renderer *renderer)
{


	Utility::log(Utility::I, "Loading all item type data : " + filePath);

	std::ifstream itemList(filePath);

	if (itemList.is_open())
	{
		int numItems;
		
		itemList >> numItems;

		for (int i = 0; i < numItems; i++)
		{
			std::string id;
			std::string itemFile;

			itemList >> id;
			itemList >> itemFile;

			Utility::log(Utility::I, "Loading item data : " + itemFile);
			std::ifstream iitem(itemFile);

			if (iitem.is_open())
			{
				std::string spritesheetPath;
				std::string itemName;

				Vec2 itemDimensions;

				float mass;

				iitem >> spritesheetPath;
				iitem >> itemName;
				iitem >> itemDimensions.x;
				iitem >> itemDimensions.y;

				iitem >> mass;
				


				

				Texture* itemSpriteSheet = new Texture(spritesheetPath, renderer);

				itemTypesID[id] = new ItemType(itemSpriteSheet, id, itemName, itemDimensions, mass);
				itemTypesName[itemName] = itemTypesID[id];


				iitem.close();

				//File loaded message
				Utility::log(Utility::I, "Item data loaded.");

			}
			else {
				//Error message
				Utility::log(Utility::E, "Unable to open item file : " + itemFile);
			}
		}
		itemList.close();
	}
	else {
		//failed
		return false;
	}
}

ItemType* ItemManager::getItemTypeByID(std::string ID)
{
	return itemTypesID[ID];
}

ItemType* ItemManager::getItemTypeByName(std::string itemName)
{
	return itemTypesName[itemName];
}
