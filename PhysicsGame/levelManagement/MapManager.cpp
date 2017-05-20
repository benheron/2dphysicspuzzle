#include "MapManager.h"




MapManager::MapManager(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager, int type, SDL_Renderer *renderer)
{
	int c = 1;
	if (type == 0)
	{
	
		bool done = false;
		while (!done)
		{
			std::ostringstream oss;
			oss << c;
			std::string newFilePath = filePath + "/map" + oss.str() + ".txt";
			done = !loadMapData(newFilePath, tileTypeManager, creatureManager, renderer);

			Utility::log(Utility::I, "Using file path : " + newFilePath);


			c++;
		}
			
	}
	else if (type == 1)
	{
		//loadMapDataForLevel(filePath, tileTypeManager, creatureManager);
	}
}

MapManager::~MapManager()
{
	for (int i = 0; i < rMaps.size(); i++)
	{
		delete rMaps[i];
	}

	for (int i = 0; i < levelIcons.size(); i++)
	{
		delete levelIcons[i];
	}
}

bool MapManager::loadMapData(std::string filePath, TileTypeManager* tileTypeManager, CreatureManager* creatureManager, SDL_Renderer *renderer)
{
	//A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;

	//A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles;
	//std::unordered_map<std::string, std::vector<std::vector<Creature*>>> mapCreatures;
	std::vector<Creature*> mapCreatures;


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTileStrings;
	std::vector<std::string> mapCreatureStrings;
	std::vector<ItemData> itemDataSeries;
	std::vector<MovPlatData> movPlatDataSeries;
	std::vector<PadSwitchdata> padSwitchDataSeries;
	std::vector<DoorData> doorDataSeries;
	std::vector<ObjectsData> physicsObjectDataSeries;
	std::vector<ObjectsData> creatureObjectDataSeries;

	Utility::log(Utility::I, "Loading map data : " + filePath);

	std::ifstream mapFile(filePath);

	if (mapFile.is_open())
	{
		std::string roomID;
		std::string iconPath;
		Vec2 mapIndexDimensions;
		int numberOfLayers;
		Vec2 tileDimensions;

		mapFile >> roomID;
		mapFile >> iconPath;
		mapFile >> mapIndexDimensions.x;
		mapFile >> mapIndexDimensions.y;
		mapFile >> numberOfLayers;
		mapFile >> tileDimensions.x;
		mapFile >> tileDimensions.y;

		Texture* icn = new Texture(iconPath, renderer);
		levelIcons.push_back(icn);
		levelIconsUM[roomID] = icn;

		//store the map ID
		roomIDs.push_back(roomID);

		for (int i = 0; i < numberOfLayers; i++)
		{
			//Store the ID of the layer
			std::string layerID;
			mapFile >> layerID;
			layerIDs.push_back(layerID);

			for (int y = 0; y < mapIndexDimensions.y; y++)
			{
				if (layerID == "O" || layerID == "B")
				{
					std::vector<Tile*> tiles;
					mapTiles[layerID].push_back(tiles);

					//text version
					std::vector<std::string> tileStrings;
					mapTileStrings[layerID].push_back(tileStrings);

					for (int x = 0; x < mapIndexDimensions.x; x++)
					{


						//Get the tile
						std::string tileID;
						mapFile >> tileID;

						//Get the data to load into the new tile
						TileType* tileType = tileTypeManager->getTileType(tileID);
						Vec2 spriteDimensions = tileType->getSpriteDimensions();
						Vec2 spritePos = tileType->getSpritePos();
						Texture* tileTexture = tileType->getTexture();

						//Store tile
						mapTiles[layerID][y].push_back(
							new Tile(tileTexture, Vec2((x * tileDimensions.x), (y * tileDimensions.y)), tileDimensions, spritePos, spriteDimensions, tileType)
						);
						



						//store tile text version
						mapTileStrings[layerID][y].push_back(tileID);
					}
				}
				else if (layerID == "C")
				{
					//std::vector<Creature*> creatures;
					//mapCreatures[layerID].push_back(creatures);
					for (int x = 0; x < mapIndexDimensions.x; x++)
					{
						//Get the creature
						std::string creatureID;
						mapFile >> creatureID;
						
						mapCreatureStrings.push_back(creatureID);
					}
				}
				
			}
		}

		std::string items;
		int numItems;
		

		mapFile >> items;
		mapFile >> numItems;
		

		if (items == "I")
		{
			for (int i = 0; i < numItems; i++)
			{
				std::string iID;

				mapFile >> iID;

				if (iID == "PP" || iID == "IS")
				{
					PadSwitchdata psDat;
					//mapFile >> psDat.ID;
					psDat.ID = iID;
					mapFile >> psDat.pos.x;
					mapFile >> psDat.pos.y;
					mapFile >> psDat.linkedItemID;

					padSwitchDataSeries.push_back(psDat);
				}
				else if(iID == "MP") {
					MovPlatData mpData;
					mpData.ID = iID;
					mapFile >> mpData.instanceID;
					mapFile >> mpData.pos.x;
					mapFile >> mpData.pos.y;
					mapFile >> mpData.endPos.x;
					mapFile >> mpData.endPos.y;

					mapFile >> mpData.speed;
					mapFile >> mpData.activated;
					mapFile >> mpData.reversing;

					movPlatDataSeries.push_back(mpData);

				}
				else if (iID == "DR") {
					DoorData ddData;
					ddData.ID = iID;
					mapFile >> ddData.instanceID;
					mapFile >> ddData.pos.x;
					mapFile >> ddData.pos.y;
					mapFile >> ddData.activated;
					doorDataSeries.push_back(ddData);
				} else {

					ItemData iDat;

					//mapFile >> iDat.ID;
					iDat.ID = iID;
					mapFile >> iDat.instanceID;
					mapFile >> iDat.pos.x;
					mapFile >> iDat.pos.y;

					itemDataSeries.push_back(iDat);
				}
			
			}
			
		}
		else {
			//failed to read map data properly
			//or not formatted correctly
		}

		std::string physics;
		int numPhysics;


		mapFile >> physics;
		mapFile >> numPhysics;

		if (physics == "PHY")
		{
			for (int i = 0; i < numPhysics; i++)
			{
				ObjectsData pod;
				mapFile >> pod.ID;
				mapFile >> pod.pos.x;
				mapFile >> pod.pos.y;

				physicsObjectDataSeries.push_back(pod);

			}
		}

		std::string creatures;
		int numCreatures;

		mapFile >> creatures;
		mapFile >> numCreatures;

		

		for (int i = 0; i < numCreatures; i++)
		{
			ObjectsData creatData;
			mapFile >> creatData.ID;
			mapFile >> creatData.pos.x;
			mapFile >> creatData.pos.y;

			creatureObjectDataSeries.push_back(creatData);
		}


		std::string playerCheck;
		Vec2 playerCoords;
		mapFile >> playerCheck;

		if (playerCheck == "P")
		{
			mapFile >> playerCoords.x;
			mapFile >> playerCoords.y;
			Utility::log(Utility::I, "Player spawn coordinates: X: " + Utility::floatToString(playerCoords.x) + " Y: " + Utility::floatToString(playerCoords.y));
		}
		else {
			Utility::log(Utility::E, "No player data");
		}
		mapFile.close();

		//Store the map
	/*	roomTemplates[roomID] = new RoomTemplate(mapTiles, mapCreatures, layerIDs, playerCoords);*/

		//rMaps.push_back(new RoomTemplate(mapTiles, mapCreatures, layerIDs, playerCoords));

		roomTemplates[roomID] = new RoomTemplate(mapTileStrings, mapCreatureStrings, layerIDs, itemDataSeries, movPlatDataSeries, padSwitchDataSeries, doorDataSeries, physicsObjectDataSeries, creatureObjectDataSeries, playerCoords);
		rMaps.push_back(roomTemplates[roomID]);
		

		Utility::log(Utility::I, "Map data loaded");

		return true;
	}
	else 
	{
		//Error
		Utility::log(Utility::E, "Unable to open map file : " + filePath);
		return false;
	}
}

RoomTemplate* MapManager::getMap(std::string mapID)
{
	return roomTemplates[mapID];
}

RoomTemplate* MapManager::getRandomMap()
{
	return rMaps[Utility::randomInt(0, (rMaps.size() - 1))];
}

RoomTemplate* MapManager::getRandomMapFromIndex(int i)
{
	return rMaps[i];
}


std::vector<Vec2> MapManager::getRoomPositions()
{
	return roomPositions;
}

int MapManager::getNumberMaps()
{
	return rMaps.size();
}

Texture* MapManager::getLevelIcon(std::string id)
{
	return levelIconsUM[id];
}