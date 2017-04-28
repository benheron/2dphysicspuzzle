#include "MapRoom.h"
#include "Tile.h"
#include "../Utility.h"
#include "../Collision.h"

MapRoom::MapRoom()
{
	m = new Manifold;
}


MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int index)
{
	RoomTemplate *rt = mpmng->getRandomMapFromIndex(index);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;
	m = new Manifold;
}

MapRoom::MapRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, ItemManager *imng, std::string id)
{
	RoomTemplate *rt = mpmng->getMap(id);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	//roomPos = pos;

	roomTilesStrings = rt->getRoomTileData();
	roomCreatureStrings = rt->getCreatureData();

	roomItemDataSeries = rt->getItemData();

	createRoom(mpmng, ttmng, cmng, imng);

	exists = true;
	m = new Manifold;
}



MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int e, int index)
{
	RoomTemplate *rt = mpmng->getRandomMapFromIndex(index);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = e;
	m = new Manifold;
}




MapRoom::~MapRoom()
{

	for (int i = 0; i < layerIDs.size(); i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTiles["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTiles["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{

				for (int x = 0; x < xSize; x++)
				{
					delete  roomTiles[layerID][y][x];
				}
			}
		}
	}

	for (int j = 0; j < roomCreatures.size(); j++)
	{
		delete roomCreatures[j];
	}



}

void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 pos, int type, bool fromlevel, int index)
{
	//generate new room from the template data
	//this allows the same room to be used but hold different data incase some is changed mid-gameplay
	RoomTemplate *rt;

	if (fromlevel)
	{
		rt = mpmng->getRandomMapFromIndex(index);
	}
	else {
		if (index > -1)
		{
			rt = mpmng->getRandomMapFromIndex(index);
		}
		else {
			rt = mpmng->getRandomMap();
		}
	}
	





	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> tmpR = rt->getRoomTiles();

	
	//roomTiles = rt->getRoomTiles();
	//roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = true;



	int numLayers = layerIDs.size();


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomData = rt->getRoomTileData();
	std::vector<std::string> creatureData = rt->getCreatureData();

	roomTilesStrings = roomData;
	roomCreatureStrings = creatureData;


	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomys;
	std::vector<std::string> creatureys;

	int c = 0;

	for (int i = 0; i < numLayers; i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomData["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomData["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{
				std::vector<Tile*> tiles;
				roomTiles[layerID].push_back(tiles);

				for (int x = 0; x < xSize; x++)
				{
					//Get the tile
					std::string tileID = roomData[layerID][y][x];

					//Get the data to load into the new tile
					TileType* tileType = ttmng->getTileType(tileID);
					Vec2 spriteDimensions = tileType->getSpriteDimensions();
					Vec2 spritePos = tileType->getSpritePos();
					Texture* tileTexture = tileType->getTexture();

					//Store tile
					/*roomTiles[layerID][y].push_back(
						new Tile(tileTexture, Vec2((x * 32), (y *32)), Vec2(32, 32), spritePos, spriteDimensions, tileType)
					);*/


					roomTiles[layerID][y].push_back(
						new Tile(Vec2((x * 32), (y * 32)), Vec2(32, 32), tileType)
					);

				}
			}
			else if (layerID == "C")
			{
				//std::vector<Creature*> creatures;
				//mapCreatures[layerID].push_back(creatures);
				for (int x = 0; x < xSize; x++)
				{
					//Get the creature
					std::string creatureID = creatureData[c];

					if (creatureID != "XX")
					{

						CreatureType* creatureType = cmng->getCreatureType(creatureID);
						Vec2 pos = Vec2((x * 32 + 16 - (creatureType->getSpriteDimensions().x / 2)), (y * 32 + 16 - (creatureType->getSpriteDimensions().y / 2)));
						Vec2 spriteDimensions = creatureType->getSpriteDimensions();
						Texture* creatureTexture = creatureType->getTexture();

						roomCreatures.push_back(
							new Creature(creatureTexture, pos, spriteDimensions, creatureType));
						
					}
					c++;
				}
			}

		}
	}


	//randomise creature placements
/*
	for (int i = 0; i < roomCreatures.size(); i++)
	{
		int a = Utility::randomInt(50, 600);
		int b = Utility::randomInt(50, 420);

		roomCreatures[i]->setPosition(Vec2(a, b));

		//Utility::log(Utility::I, Utility::intToString(a) + ", " + Utility::intToString(b));
	}*/

	if (type == 1)
	{
		changeTileType("O", Vec2(13, 1), "S0", ttmng);
	}
}



void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, ItemManager *imng)
{
	//generate new room from the template data
	//this allows the same room to be used but hold different data incase some is changed mid-gameplay


	//temp
	ttm = ttmng;

	int numLayers = layerIDs.size();

	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomys;
	std::vector<std::string> creatureys;

	int c = 0;

	for (int i = 0; i < numLayers; i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTilesStrings["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTilesStrings["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{
				std::vector<Tile*> tiles;
				roomTiles[layerID].push_back(tiles);

				for (int x = 0; x < xSize; x++)
				{
					//Get the tile
					std::string tileID = roomTilesStrings[layerID][y][x];

					//Get the data to load into the new tile
					TileType* tileType = ttmng->getTileType(tileID);
					Vec2 spriteDimensions = tileType->getSpriteDimensions();
					Vec2 spritePos = tileType->getSpritePos();
					Texture* tileTexture = tileType->getTexture();

					//Store tile
					/*roomTiles[layerID][y].push_back(
					new Tile(tileTexture, Vec2((x * 32), (y *32)), Vec2(32, 32), spritePos, spriteDimensions, tileType)
					);*/

					roomTiles[layerID][y].push_back(
						new Tile(Vec2((x * 32), (y * 32)), Vec2(32, 32), tileType)
					);

				}
			}
			else if (layerID == "C")
			{
				//std::vector<Creature*> creatures;
				//mapCreatures[layerID].push_back(creatures);
				for (int x = 0; x < xSize; x++)
				{
					//Get the creature
					std::string creatureID = roomCreatureStrings[c];

					if (creatureID != "XX")
					{

						CreatureType* creatureType = cmng->getCreatureType(creatureID);
						Vec2 pos = Vec2((x * 32 + 16 - (creatureType->getSpriteDimensions().x / 2)), (y * 32 + 16 - (creatureType->getSpriteDimensions().y / 2)));
						Vec2 spriteDimensions = creatureType->getSpriteDimensions();
						Texture* creatureTexture = creatureType->getTexture();

						roomCreatures.push_back(
							new Creature(creatureTexture, pos, spriteDimensions, creatureType));

					}
					c++;
				}
			}

		}
	}

	labelTileSides();

	for (int i = 0; i < roomItemDataSeries.size(); i++)
	{
		std::string id = roomItemDataSeries[i].ID;
		Vec2 pos = roomItemDataSeries[i].pos;
		if (id == "II0")
		{
			ItemType *thisItemData = imng->getItemTypeByID(id);
			pp = new PressurePad(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions());
			pp->mass = thisItemData->getMass();
			pp->itemID = id;

			//roomItems.push_back(pp);
		}

		if (id == "II1")
		{
			ItemType *thisItemData = imng->getItemTypeByID(id);
			me = new MapExit(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions());
			me->itemID = id;
		}
	}


}


void MapRoom::labelTileSides()
{
	std::vector<std::vector<Tile*>> objectLayerTiles = roomTiles["O"];
	int h = objectLayerTiles.size();
	int l = objectLayerTiles[0].size();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{

			Tile *thisTile = objectLayerTiles[i][j];

			int befX = j - 1;
			int befY = i - 1;
			int afX = j + 1;
			int afY = i + 1;
			
			

			befX += 1 - 1;

			if (befX > -1 && befY > -1 &&
				afX < l && afY < h)
			{
				//check left side
				if (thisTile->getSideL() && objectLayerTiles[i][j - 1]->getSideR())
				{
					thisTile->setSideL(false);
					objectLayerTiles[i][j - 1]->setSideR(false);
				}
				//check right side
				if (thisTile->getSideR() && objectLayerTiles[i][j + 1]->getSideL())
				{
					thisTile->setSideR(false);
					objectLayerTiles[i][j - 1]->setSideL(false);
				}
				//check above
				if (thisTile->getSideU() && objectLayerTiles[i - 1][j]->getSideD())
				{
					thisTile->setSideU(false);
					objectLayerTiles[i][j - 1]->setSideD(false);
				}
				//check below
				if (thisTile->getSideD() && objectLayerTiles[i + 1][j]->getSideU())
				{
					thisTile->setSideD(false);
					objectLayerTiles[i][j - 1]->setSideU(false);
				}
			}
			
		}
	}
}

bool MapRoom::getLevelComplete()
{
	return levelComplete;
}

void MapRoom::update(float dt)
{
	for (int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->update(dt);
		
		m->A = roomCreatures[i]; 

		checkCollideM2(m);
	}

	if (pp->getActivate())
	{
		me->setOpen(true);
	}


	



	
}

void MapRoom::render(SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < roomItems.size(); i++)
	{
		roomItems[i]->render(renderer);
	}

	if (me)
	{
		me->render(renderer);
	}
	
	if (pp)
	{
		pp->render(renderer);
	}
	

	//Load in all the map data
	//Loop through all of the Layer ID's
	for (unsigned int i = 0; i < layerIDs.size(); i++)
	{
		//Loop through all the map tiles
		for (unsigned int y = 0; y < roomTiles[layerIDs[i]].size(); y++)
		{
			for (unsigned int x = 0; x < roomTiles[layerIDs[i]][y].size(); x++)
			{
				roomTiles[layerIDs[i]][y][x]->render(renderer);
			}
		}
	}

	//load in the creature data

	for (unsigned int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->render(renderer);
	}


	

	//load in the player data

	if (playerLoaded)
	{
		player->render(renderer);
	}
}

void MapRoom::loadPlayer(CharacterType *pt)
{
	player = new Character(pt->getTexture(), Vec2(25,25), pt);

	playerLoaded = true;
}

void MapRoom::addCreature(Vec2 p, CreatureType *ct)
{
	Texture* creatureTexture = ct->getTexture();



	int x = (p.x / 32);
	x *= 32;
	int y = (p.y / 32);
	y *= 32;

	Vec2 np = Vec2(x, y);


	int nx = np.x + 16 - (ct->getSpriteDimensions().x / 2);
	int ny = np.y + 16 - (ct->getSpriteDimensions().y / 2);

	Vec2 nnp = Vec2(nx, ny);

	bool sameAsAnother = false;
	for (int i = 0; i < roomCreatures.size(); i++)
	{
		if (nnp == roomCreatures[i]->getPosition())
		{
			sameAsAnother = true;
			Utility::log(Utility::I, "Same as another creature");
		}
	}


	for (int i = 0; i < roomTiles["O"].size(); i++)
	{
		for (int j = 0; j < roomTiles["O"][i].size(); j++)
		{
			std::string t = roomTiles["O"][i][j]->getTileTypeID();
			if (t != "XX" && np == roomTiles["O"][i][j]->getPosition())
			{
				sameAsAnother = true;
				Utility::log(Utility::I, "Same as another tile");
				
			}
		}
	}

	if (!sameAsAnother)
	{
		roomCreatures.push_back(new Creature(creatureTexture, nnp, Vec2(13, 19), ct));
		roomCreatureStrings[(y/32)*29 + (x/32)] = ct->getID();
		Utility::log(Utility::I, "Not same as another creature or tile");
	}

	Utility::log(Utility::I, Utility::intToString(roomCreatures.size()));
}


void MapRoom::setPos(Vec2 pos)
{

	roomPos = pos;
}

Vec2 MapRoom::getPos()
{
	return roomPos;
}

void MapRoom::setAccess(bool b)
{
	access = true;
}

bool MapRoom::getAccess()
{
	return access;
}

void MapRoom::setExists(bool e)
{
	exists = e;
}

bool MapRoom::getExists()
{
	return exists;
}



Tile* MapRoom::getTile(Vec2 xy)
{
	return roomTiles["O"][xy.y][xy.x];
}

int MapRoom::checkCollide(Entity *e)
{
	if (exists)
	{
		Vec2 localPos = e->getPosition();
		Vec2 localDimen = e->getDimensions();

		int mx = floor(localPos.x / 32);
		int my = floor(localPos.y / 32);

		//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));



		int c = 0;

		for (int i = my - 1; i < my + 2; i++)
		{
			for (int j = mx - 1; j < mx + 2; j++)
			{
				c++;
				if (!(j < 0 || j > 29 ||
					i < 0 || i > 16))
				{
					if (!roomTiles["O"][i][j]->haveBlankID())
					{
						Vec2 tmp = roomTiles["O"][i][j]->getPosition();
						Vec2 tmp2 = roomTiles["O"][i][j]->getDimensions();
						/*

						Utility::log(Utility::I, "Player X: " + Utility::floatToString(localPos.x) + ", Player Y: " + Utility::floatToString(localPos.y));
						Utility::log(Utility::I, "Player Width " + Utility::floatToString(localDimen.x) + ", Player Height: " + Utility::floatToString(localDimen.y));
						Utility::log(Utility::I, "Tile X: " + Utility::floatToString(tmp.x) + ", Tile Y: " + Utility::floatToString(tmp.y));
						Utility::log(Utility::I, "Tile Width " + Utility::floatToString(tmp2.x) + ", Tile Height: " + Utility::floatToString(tmp2.y));*/


						if (Collision::boxBoxCollision(localPos, localDimen, roomTiles["O"][i][j]->getPosition(), roomTiles["O"][i][j]->getDimensions()))
						{
							if (roomTiles["O"][i][j]->getTileTypeID() == "S0")
							{
								return 2;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}

		return false;
	}
	return 0;

}

int MapRoom::checkCollideM(Manifold *m)
{
	if (exists)
	{
		Vec2 localPos = m->A->getPosition();
		Vec2 localDimen = m->A->getDimensions();

		int mx = floor(localPos.x / 32);
		int my = floor(localPos.y / 32);

		//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));



		int c = 0;

		for (int i = my - 1; i < my + 2; i++)
		{
			for (int j = mx - 1; j < mx + 2; j++)
			{
				c++;
				if (!(j < 0 || j > 29 ||
					i < 0 || i > 16))
				{
					if (!roomTiles["O"][i][j]->haveBlankID())
					{
						m->B = roomTiles["O"][i][j];

						if (Collision::boxBoxCollisionM(m))
						{
							return 1;
						}
					}
				}
			}
		}

		return false;
	}
	return 0;

}

int MapRoom::checkCollideM2(Manifold *m)
{
	if (exists)
	{
		Vec2 localPos = m->A->getPosition();
		Vec2 localDimen = m->A->getDimensions();

		int mx = floor(localPos.x / 32);
		int my = floor(localPos.y / 32);

		//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));



		int c = 0;

		for (int i = my - 1; i < my + 2; i++)
		{
			for (int j = mx - 1; j < mx + 2; j++)
			{
				c++;
				if (!(j < 0 || j > 29 ||
					i < 0 || i > 16))
				{
					if (!roomTiles["O"][i][j]->haveBlankID())
					{
						m->B = roomTiles["O"][i][j];

						if (Collision::boxBoxCollisionM(m))
						{
							Collision::resolve(m);
							Collision::correctPositions(m);

							//Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));



						}
					}
				}
			}
		}

		for (int i = 0; i < roomItems.size(); i++)
		{
			m->B = roomItems[i];

			if (Collision::boxBoxCollisionM(m))
			{
				Collision::resolve(m);
				Collision::correctPositions(m);
			}

		}

		m->B = pp;
		if (Collision::boxBoxCollisionM(m))
		{
			Collision::resolve(m);
			Collision::correctPositions(m);
			pp->setActivate(true);
		}



		if (me->getOpen())
		{
			m->B = me;
			if (Collision::boxBoxCollisionM(m))
			{
				levelComplete = true;
			}

		}




		for (int i = 0; i < roomCreatures.size(); i++)
		{
			m->B = roomCreatures[i];

			if (Collision::boxBoxCollisionM(m))
			{
				Collision::resolve(m);
				Collision::correctPositions(m);
			}

		}

		return false;
	}
	return 0;

}

int MapRoom::checkCollideM3(Manifold *m)
{
	if (exists)
	{
		Vec2 localPos = m->A->getPosition();
		Vec2 localDimen = m->A->getDimensions();

		int mx = floor(localPos.x / 32);
		int my = floor(localPos.y / 32);

		//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));



		int c = 0;

		for (int i = my - 1; i < my + 2; i++)
		{
			for (int j = mx - 1; j < mx + 2; j++)
			{
				c++;
				if (!(j < 0 || j > 29 ||
					i < 0 || i > 16))
				{
					if (!roomTiles["O"][i][j]->haveBlankID())
					{
						m->B = roomTiles["O"][i][j];

						if (Collision::boxBoxCollisionM(m))
						{
							Collision::resolve(m);
							Collision::correctPositions(m);

							//Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));



						}
					}
				}
			}
		}
		return 0;
	}
}

bool MapRoom::lineOfSight(Entity *e)
{
	
	for (int i = 0; i < roomCreatures.size(); i++)
	{

		float d = Collision::distanceBetween(e->getCentre(), roomCreatures[i]->getCentre());

		Raycast r = Raycast(e->getCentre(), roomCreatures[i]->getCentre(), 1);

		std::vector<Vec2> raypoints = r.getRayPoints();
		bool seen = false;

		for (int j = 0; j < raypoints.size(); j++)
		{
			int px = floor(raypoints[j].x / 32);
			int py = floor(raypoints[j].y / 32);

			/*if (px < 29 && px > 0 && py < 14 && py > 0)
			{
				if (change % 2)
				{
					changeTileType("O", Vec2(px, py), "L0", ttm);
				}
				else {
					changeTileType("O", Vec2(px, py), "VE", ttm);
				}
			}*/
			
			
			//ray hits wall
			if (!roomTiles["O"][py][px]->haveBlankID())
			{
				roomCreatures[i]->setMoveToward(false);
				return false;
			}
			else {
				seen = true;
			}
		}
		if (seen)
		{
			if (d < 30)
			{
				roomCreatures[i]->setMoveToward(false);
			}
			else {
				roomCreatures[i]->setMoveToward(true);
				roomCreatures[i]->setMoveTowardPos(e->getCentre());
			}
			
		}
	}
	
	
	return true;
}


void MapRoom::changeTileType(std::string layer, Vec2 tilePos, std::string tileID, TileTypeManager *ttmng)
{
	if (layer != "C")
	{
		roomTiles[layer][tilePos.y][tilePos.x]->setTileType(tileID, ttmng);
		roomTilesStrings[layer][tilePos.y][tilePos.x] = tileID;
	}
	

	/*if (layer == "O" || layer == "C")
	{
		for (int i = 0; i < roomCreatures.size(); i++)
		{
			Vec2 f = roomCreatures[i]->getPosition();
			int chX = f.x / 32;
			chX *= 32;
			int chY = f.y / 32;
			chY *= 32;

			Vec2 checkPos = Vec2(chX, chY);

			Vec2 realTilePos((int)tilePos.x * 32, (int)tilePos.y * 32);

			if (checkPos == realTilePos)
			{
				delete roomCreatures[i];
				roomCreatures.erase(roomCreatures.begin() + i);
				Utility::log(Utility::I, "Same as another creature");
			}
		}
	}*/
	
}



std::unordered_map<std::string, std::vector<std::vector<std::string>>> MapRoom::getRoomTilesStrings()
{
	return roomTilesStrings;
}

std::vector<std::string> MapRoom::getRoomCreaturesStrings()
{
	return roomCreatureStrings;
}

std::vector<std::string> MapRoom::getLayerIDs()
{
	return layerIDs;
}


Creature* MapRoom::getCreatureByIndex(int index)
{
	return roomCreatures[index];
}

int MapRoom::getNumCreatures()
{
	return roomCreatures.size();
}