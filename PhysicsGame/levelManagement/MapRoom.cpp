#include "MapRoom.h"
#include "Tile.h"
#include "../Utility.h"
#include "../Collision.h"

MapRoom::MapRoom()
{
	//m = new Manifold;
}


MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int index)
{
	RoomTemplate *rt = mpmng->getRandomMapFromIndex(index);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;
//	m = new Manifold;
}

MapRoom::MapRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, ItemManager *imng, AssetManager *a, std::string id)
{
	RoomTemplate *rt = mpmng->getMap(id);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	//roomPos = pos;

	roomTilesStrings = rt->getRoomTileData();
	roomCreatureStrings = rt->getCreatureData();

	roomItemDataSeries = rt->getItemData();

	roomMovPlatDataSeries = rt->getMovPlatData();
	roomPadSwitchDataSeries = rt->getPadSwitchdata();
	doorDataSeries = rt->getDoorData();
	roomPhysicsObjectDataSeries = rt->getPhysicsObjectData();
	creatureObjectDataSeries = rt->getCreaturesObjectData();

	asmng = a;
	

	exists = true;
	//m = new Manifold;

	playerSpawn = rt->getPlayerSpawn();

	createRoom(mpmng, ttmng, cmng, imng);

	Vec2 ppos = player->getPosition();
	Vec2 pdim = player->getDimensions();

	jumphitbox = new Square(Vec2(ppos.x, ppos.y + pdim.y), Vec2(pdim.x, 0.01));
	jumphitbox->setGravityOn(false);
}



MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int e, int index)
{
	RoomTemplate *rt = mpmng->getRandomMapFromIndex(index);
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = e;
	//m = new Manifold;
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


	for (unsigned int i = 0; i < roomItems.size(); i++)
	{
		delete roomItems[i];
	}

	for (int i = 0; i < roomPressurePads.size(); i++)
	{
		delete roomPressurePads[i];
	}

	for (int i = 0; i < roomItemSwitches.size(); i++)
	{
		delete roomItemSwitches[i];
	}

	for (int i = 0; i < roomDoors.size(); i++)
	{
		delete roomDoors[i];
	}

	for (int i = 0; i < roomMovePlats.size(); i++)
	{
		delete roomMovePlats[i];
	}


	for (int i = 0; i < squares.size(); i++)
	{
		delete squares[i];
	}

	delete me;




	for (int i = 0; i < grunts.size(); i++)
	{
		delete grunts[i];
	}

	for (int i = 0; i < sentinels.size(); i++)
	{
		delete sentinels[i];
	}


	delete player;



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


//this one
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

					Tile *t = new Tile(Vec2((x * 32), (y * 32)), Vec2(32, 32), tileType);
					if (!t->haveBlankID() && !t->getClimbable())
					{

						t->setSideL(true);
						t->setSideR(true);
						t->setSideU(true);
						t->setSideD(true);
					}


					if (t->getTileTypeID() == "L2")
					{
						t->setSideU(true);
					}

					roomTiles[layerID][y].push_back(t);

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
		ItemType *thisItemData = imng->getItemTypeByID(id);

		if (id == "ME")
		{
			me = new MapExit(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions());
		}
	}

	for (int i = 0; i < roomMovPlatDataSeries.size(); i++)
	{
		MovPlatData mvp = roomMovPlatDataSeries[i];

		std::string id = mvp.ID;
		Vec2 pos = mvp.pos;
		Vec2 end = mvp.endPos;
		int speed = mvp.speed;
		bool activated = mvp.activated;
		bool reversing = mvp.reversing;
		std::string instID = mvp.instanceID;
		ItemType *thisItemData = imng->getItemTypeByID(id);



		//MovingPlatform *mp = new MovingPlatform(thisItemData->getSpriteSheet(), pos, end, thisItemData->getSpriteDimensions(), speed, activated, reversing);

		MovingPlatformWithEnds *mpwe = new MovingPlatformWithEnds(asmng->getTexture("platend"), asmng->getTexture("dash"), thisItemData->getSpriteSheet(), pos, end, thisItemData->getSpriteDimensions(), speed, activated, reversing);



		roomMovePlats.push_back(mpwe);

		MovingPlatform *mp = mpwe->getMovingPlatform();
		roomActItemUM[instID] = mp;
	}


	for (int i = 0; i < doorDataSeries.size(); i++)
	{
		DoorData dd = doorDataSeries[i];

		std::string id = dd.ID;
		Vec2 pos = dd.pos;
		std::string instID = dd.instanceID;
		bool activated = dd.activated;
		ItemType *thisItemData = imng->getItemTypeByID(id);

		Door *d = new Door(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions(), activated);

		roomDoors.push_back(d);
		roomActItemUM[instID] = d;

	}

	for (int i = 0; i < roomPadSwitchDataSeries.size(); i++)
	{
		PadSwitchdata psd = roomPadSwitchDataSeries[i];

		std::string id = psd.ID;
		Vec2 pos = psd.pos;
		std::string linkedItemID = psd.linkedItemID;
		ItemType *thisItemData = imng->getItemTypeByID(id);

		if (id == "PP")
		{
			PressurePad *pps = new PressurePad(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions(), roomActItemUM[linkedItemID]);
			roomPressurePads.push_back(pps);
		}
		else if (id == "IS")
		{
			ItemSwitch *nis = new ItemSwitch(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions(), roomActItemUM[linkedItemID]);
			roomItemSwitches.push_back(nis);
		}
	}


	for (int i = 0; i < roomPhysicsObjectDataSeries.size(); i++)
	{
		ObjectsData pod = roomPhysicsObjectDataSeries[i];

		std::string id = pod.ID;
		Vec2 pos = pod.pos;
		ItemType *thisItemData = imng->getItemTypeByID(id);
		if (id == "SQ")
		{
			Square *sq = new Square(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions());
			squares.push_back(sq);
		}
		else if (id == "CI") {
			Circle *ci = new Circle(thisItemData->getSpriteSheet(), pos, thisItemData->getSpriteDimensions());
			circles.push_back(ci);
		}
		
	}

	for (int i = 0; i < creatureObjectDataSeries.size(); i++)
	{
		ObjectsData creatData = creatureObjectDataSeries[i];
		std::string id = creatData.ID;
		Vec2 pos = creatData.pos;
		CreatureType *thisCreatureData = cmng->getCreatureType(id);

		if (id == "GR")
		{
			Grunt *gr = new Grunt(thisCreatureData->getTexture(), pos, thisCreatureData->getSpriteDimensions(), thisCreatureData, 40);
			grunts.push_back(gr);
		}
		if (id == "SE")
		{
			Sentinel *se = new Sentinel(thisCreatureData->getTexture(), asmng->getTexture("lasersight"), pos, thisCreatureData->getSpriteDimensions(), thisCreatureData);
			sentinels.push_back(se);
		}
	}

	player = new Character(playerSpawn, cmng->getCharacterType("G1"));

	player->setGravityOn(true);

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
			

			/*if (befX > -1 && befY > -1 &&
				afX < l && afY < h)*/
			{
				if (!thisTile->haveBlankID() || !thisTile->getCollidable())
				{
					if (befX > -1)
					{
						//check left side
						if (thisTile->getSideL() && objectLayerTiles[i][j - 1]->getSideR())
						{
							thisTile->setSideL(false);
							objectLayerTiles[i][j - 1]->setSideR(false);
						}
					}
					
					if (afX < l)
					{
						//check right side
						if (thisTile->getSideR() && objectLayerTiles[i][j + 1]->getSideL())
						{
							thisTile->setSideR(false);
							objectLayerTiles[i][j + 1]->setSideL(false);
						}
					}
					
					if (befY < -1)
					{
						//check above
						if (thisTile->getSideU() && objectLayerTiles[i - 1][j]->getSideD())
						{
							thisTile->setSideU(false);
							objectLayerTiles[i - 1][j]->setSideD(false);
						}
					}
				
					
					if (afY < h)
					{
						//check below
						if (thisTile->getSideD() && objectLayerTiles[i + 1][j]->getSideU())
						{
							thisTile->setSideD(false);
							objectLayerTiles[i + 1][j]->setSideU(false);
						}
					}
					
				}
			}
		}
	}

	int d = 0;
}

bool MapRoom::getLevelComplete()
{
	return levelComplete;
}

void MapRoom::update(float dt)
{
	bool crush = false;

	//update entities
	player->update(dt);
	Vec2 ppos = player->getPosition();
	Vec2 pdim = player->getDimensions();

	jumphitbox->setPosition(Vec2(ppos.x, ppos.y + pdim.y));
	player->setOnFloor(false);
	player->setOnMovingPlatform(false);
	Manifold m;
	
	for (int i = 0; i < roomDoors.size(); i++)
	{
		roomDoors[i]->update(dt);

		m.A = player;
		m.B = roomDoors[i];
		if (Collision::boxBoxCollisionM(&m))
		{
			Collision::resolve(&m);
			Collision::correctPositions(&m);
		}

		m.A = jumphitbox;
		if (Collision::boxBoxCollisionM(&m))
		{
			if (m.normal == Vec2(0, 1))
			{
				player->setOnFloor(true);
				
			}
		}
	}


	int kl = 0;

	for (int i = 0; i < roomMovePlats.size(); i++)
	{
		roomMovePlats[i]->update(dt);
		m.B = roomMovePlats[i]->getMovingPlatform();
		if (player->getAlive())
		{
			m.A = player;
			//m.B = roomMovePlats[i];

			if (roomMovePlats[i]->checkPlatformCollision(&m))
			{

				if (m.normal == Vec2(0, -1))
				{
					if (roomMovePlats[i]->getMovingPlatform()->velocity.y > 0)
					{
						crush = true;
					}

				}

				Collision::resolve(&m);
				Collision::correctPositions(&m);


			}
		}
		

		

		m.A = jumphitbox;
		if (Collision::boxBoxCollisionM(&m))
		{
			if (m.normal == Vec2(0, 1))
			{
				player->setOnFloor(true);
				player->setOnMovingPlatform(true, roomMovePlats[i]->getMovingPlatform());
			}
		}
	}


	for (int i = 0; i < roomPressurePads.size(); i++)
	{
		roomPressurePads[i]->update(dt);
		roomPressurePads[i]->setActivate(false);

		m.A = player;
		
		m.B = roomPressurePads[i];
		if (Collision::boxBoxCollisionM(&m))
		{
			Collision::resolve(&m);
			Collision::correctPositions(&m);
		}

		m.A = jumphitbox;
		if (Collision::boxBoxCollisionM(&m))
		{
			if (m.normal == Vec2(0, 1))
			{
				player->setOnFloor(true);
				roomPressurePads[i]->setActivate(true);
			}
		}
		
	}

	for (int i = 0; i < roomItemSwitches.size(); i++)
	{
		roomItemSwitches[i]->update(dt);

		m.A = player;
		m.B = roomItemSwitches[i];
		if (Collision::boxBoxCollisionM(&m))
		{
			Collision::resolve(&m);
			Collision::correctPositions(&m);
		}

		m.A = jumphitbox;
		if (Collision::boxBoxCollisionM(&m))
		{
			if (m.normal == Vec2(0, 1))
			{
				player->setOnFloor(true);
			}
		}
	}


	

	
	bool playerOnBody = false;

	//collision
	
	ManifoldTile mt;
	for (int i = 0; i < squares.size(); i++)
	{
		squares[i]->update(dt);

		m.A = squares[i];

		Vec2 normal = 0;
		float penetration;

		for (int j = 0; j < squares.size(); j++)
		{
		

			m.B = squares[j];

			//check not comparing to self
			if (squares[i] != squares[j])
			{
				if (Collision::boxBoxCollisionM(&m))
				{
					Collision::resolve(&m);
					Collision::correctPositions(&m);
				}
			}
		}

		for (int j = 0; j < circles.size(); j++)
		{

			m.B = circles[j];
			//Vec2 normal = 0;
			//float penetration;

			//check not comparing to self
			if (Collision::circleCircleCollisionM(&m))
			{
				//	Utility::log(Utility::I, "Collide with another circle");
				Collision::resolve(&m);
				Collision::correctPositions(&m);
			}
		}

		m.B = jumphitbox;
		if (Collision::boxBoxCollisionM(&m))
		{
			if (m.normal == Vec2(0, -1))
			{
				player->setOnFloor(true);
				player->setOnBody(true, squares[i]);
				playerOnBody = true;
			}


		}


		m.B = player;


		if (Collision::boxBoxCollisionM(&m))
		{
			if (player->getCarryingBody())
			{
				if (player->getBodyCarrying() == squares[i])
				{
					squares[i]->velocity = 0;
				}
				else {
					Collision::resolve(&m);
					Collision::correctPositions(&m);
				}
				
				/*if (player->getBodyOnTopOf() == squares[i])
				{
					squares[i]->velocity = 0;

				}
				else {
					//Collision::resolve(&m);
					//Collision::correctPositions(&m);
				}*/
				

			}
			else {
				Collision::resolve(&m);
				Collision::correctPositions(&m);
				//	Utility::log(Utility::I, "Collide with player");
			}
		}
		

		for (int j = 0; j < roomPressurePads.size(); j++)
		{
			m.B = roomPressurePads[j];
			if (Collision::boxBoxCollisionM(&m))
			{
				Collision::resolve(&m);
				Collision::correctPositions(&m);
				if (m.normal == Vec2(0, 1))
				{
					roomPressurePads[j]->setActivate(true);
				}
			}
		}

		for (int j = 0; j < roomItemSwitches.size(); j++)
		{
			m.B = roomItemSwitches[j];
			if (Collision::boxBoxCollisionM(&m))
			{
				if (m.normal == Vec2(1, 0) || m.normal == Vec2(-1, 0))
				{
					if (abs(squares[i]->velocity.x) > 130)
					{
						roomItemSwitches[j]->activate();
					}
				}
				if (m.normal == Vec2(0, 1) || m.normal == Vec2(0, -1))
				{
					if (abs(squares[i]->velocity.y) > 130)
					{
						roomItemSwitches[j]->activate();
					}
				}
				
				/*if (squares[i]->velocity.getLength() > 140)
				{
					roomItemSwitches[j]->activate();
				}*/
				Collision::resolve(&m);
				Collision::correctPositions(&m);
			}
		}

		for (int j = 0; j < roomDoors.size(); j++)
		{
			m.B = roomDoors[j];
			if (Collision::boxBoxCollisionM(&m))
			{
				Collision::resolve(&m);
				Collision::correctPositions(&m);
			}
		}

		for (int j = 0; j < roomMovePlats.size(); j++)
		{
			//m.B = roomMovePlats[j];
			if (roomMovePlats[j]->checkPlatformCollision(&m))
			{
				Collision::resolve(&m);
				Collision::correctPositions(&m);
			}
		}

		for (int j = 0; j < grunts.size(); j++)
		{
			m.B = grunts[j];
			if (Collision::boxBoxCollisionM(&m))
			{
				Collision::resolve(&m);
				Collision::correctPositions(&m);
				if (m.normal == Vec2(1, 0) || m.normal == Vec2(-1, 0))
				{
					grunts[j]->changeDirection();
				}
			}
		}





		
		

		//tile collision
		mt.A = squares[i];
		checkCollideM4(&mt);

		mt.A = jumphitbox;
		if (checkCollideM3(&mt))
		{
			if (mt.normal == Vec2(0, -1))
			{
				player->setOnFloor(true);
			}
		}
		/*if (squares[i]->getPosition().y > 540)
		{
			squares[i]->setPosition(Vec2(80, 170));
			squares[i]->velocity = Vec2(0, 0);
		}*/

	}

	for (int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->update(dt);

		mt.A = roomCreatures[i];

		checkCollideM(&mt);
	}

	for (int i = 0; i < sentinels.size(); i++)
	{
		sentinels[i]->update(dt);
	}

	lineOfSight(player);

	for (int i = 0; i < grunts.size(); i++)
	{
		grunts[i]->update(dt);

		mt.A = grunts[i];

		int norm = checkCollideM4(&mt);

		m.A = player;
		m.B = grunts[i];

		if (Collision::boxBoxCollisionM(&m))
		{
			player->setAlive(false);
		}

		/*if (norm == 2)
		{
			grunts[i]->changeDirection();
		}*/
	}

	mt.A = jumphitbox;

	if (checkCollideM3(&mt) == 2)
	{
		player->setOnFloor(true);
	}

	
	checkCollidePlayerTile(player);

	mt.A = player;
	checkCollideM3(&mt);

	player->setOnBody(playerOnBody);

	if (player->getOnFloor() && crush)
	{
		player->setAlive(false);
	}


	m.A = player;
	m.B = me;
	if (Collision::boxBoxCollisionM(&m))
	{
		levelComplete = true;
	}

	
}

void MapRoom::render(SDL_Renderer* renderer)
{



	for (unsigned int i = 0; i < roomItems.size(); i++)
	{
		roomItems[i]->render(renderer);
	}

	

	for (int i = 0; i < roomDoors.size(); i++)
	{
		roomDoors[i]->render(renderer);
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
	
	for (int i = 0; i < squares.size(); i++)
	{
		squares[i]->render(renderer);
	}
	me->render(renderer);

	for (int i = 0; i < roomMovePlats.size(); i++)
	{
		roomMovePlats[i]->render(renderer);
	}



	for (int i = 0; i < grunts.size(); i++)
	{
		grunts[i]->render(renderer);
	}
	for (int i = 0; i < sentinels.size(); i++)
	{
		sentinels[i]->render(renderer);
	}


	//load in the creature data

	for (unsigned int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->render(renderer);
	}

	for (int i = 0; i < roomPressurePads.size(); i++)
	{
		roomPressurePads[i]->render(renderer);
	}

	for (int i = 0; i < roomItemSwitches.size(); i++)
	{
		roomItemSwitches[i]->render(renderer);
	}
	
	

	//load in the player data

	if (!levelComplete)
	{
		player->render(renderer);
	}
	



}

void MapRoom::renderDebug(SDL_Renderer *renderer, Texture* red)
{
	std::vector<std::vector<Tile*>> objectLayerTiles = roomTiles["O"];
	int h = objectLayerTiles.size();
	int l = objectLayerTiles[0].size();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{
			Tile *thisTile = objectLayerTiles[i][j];

			if (thisTile->getSideL())
			{
				red->pushToScreen(renderer, thisTile->getPosition(), Vec2(1.f, thisTile->getDimensions().y));
			}

			if (thisTile->getSideR())
			{
				red->pushToScreen(renderer, Vec2(thisTile->getPosition().x + thisTile->getDimensions().x, thisTile->getPosition().y), Vec2(1.f, thisTile->getDimensions().y));
			}

			if (thisTile->getSideU())
			{
				red->pushToScreen(renderer, thisTile->getPosition(), Vec2(thisTile->getDimensions().x, 1.f));
			}

			if (thisTile->getSideD())
			{
				red->pushToScreen(renderer, Vec2(thisTile->getPosition().x, thisTile->getPosition().y + +thisTile->getDimensions().y), Vec2(thisTile->getDimensions().x, 1.f));
			}
		}

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
			//Utility::log(Utility::I, "Same as another creature");
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
				//Utility::log(Utility::I, "Same as another tile");
				
			}
		}
	}

	if (!sameAsAnother)
	{
		roomCreatures.push_back(new Creature(creatureTexture, nnp, Vec2(13, 19), ct));
		roomCreatureStrings[(y/32)*29 + (x/32)] = ct->getID();
		//Utility::log(Utility::I, "Not same as another creature or tile");
	}

	//Utility::log(Utility::I, Utility::intToString(roomCreatures.size()));
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

int MapRoom::checkCollideM(ManifoldTile *m)
{
	int returnVal = 0;

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

						if (Collision::boxTileEdgeCollision(m))
						{
							returnVal = 1;
						}
					}
				}
			}
		}

	}
	return returnVal;

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

int MapRoom::checkCollideM3(ManifoldTile *m)
{
	bool normalUp = false;
	bool collided = false;
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
					Tile *thisTile = roomTiles["O"][i][j];
					if (!thisTile->haveBlankID())
					{
						//if (!thisTile->getClimbable())
						{
							m->B = thisTile;

							if (Collision::boxTileEdgeCollision(m))
							{
								if (m->normal == Vec2(0, 1))
								{
									normalUp = true;
								}
								collided = true;
								if (player->getClimbing())
								{
									if (!thisTile->getClimbable())
									{
										Manifold m2;
										m2.A = m->A;
										m2.B = m->B;
										m2.normal = m->normal;
										m2.penetration = m->penetration;
										Collision::resolve(&m2);
										Collision::correctPositions(&m2);
									}
									else {
									
									}
								}
								else {
									Manifold m2;
									m2.A = m->A;
									m2.B = m->B;
									m2.normal = m->normal;
									m2.penetration = m->penetration;
									Collision::resolve(&m2);
									Collision::correctPositions(&m2);
								}
								
								


							}
						}
						
					}
				}
			}
		}

		if (normalUp && collided)
		{
			return 2;
		}
		if (collided && !normalUp)
		{
			return 1;
		}

		return 0;
	}
}

int MapRoom::checkCollideM4(ManifoldTile *m)
{
	bool topbot = false;
	bool leftright = false;
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
					Tile *thisTile = roomTiles["O"][i][j];
					if (!thisTile->haveBlankID())
					{
						//if (!thisTile->getClimbable())
						{
							m->B = thisTile;

							if (Collision::boxTileEdgeCollision(m))
							{
								Manifold m2;
								m2.A = m->A;
								m2.B = m->B;
								m2.normal = m->normal;
								m2.penetration = m->penetration;
								Collision::resolve(&m2);
								Collision::correctPositions(&m2);

								if (m->normal == Vec2(1, 0) || m->normal == Vec2(-1, 0))
								{
									leftright = true;
								}

								if (m->normal == Vec2(0, 1) || m->normal == Vec2(0, -1))
								{
									topbot = true;
								}
							}
						}

					}
				}
			}
		}

		if (leftright && topbot)
		{
			return 3;
		}

		if (leftright)
		{
			return 2;
		}

		if (topbot)
		{
			return 1;
		}
		return 0;
	}
}

int MapRoom::checkCollidePlayerTile(Character *player)
{
	Manifold m;
	m.A = player;


	Vec2 localPos = player->getPosition();
	Vec2 localDimen = player->getDimensions();

	int mx = floor(localPos.x / 32);
	int my = floor(localPos.y / 32);

	//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));


	bool climb = false;
	bool damage = false;
	int c = 0;

	for (int i = my - 1; i < my + 2; i++)
	{
		for (int j = mx - 1; j < mx + 2; j++)
		{
			c++;
			if (!(j < 0 || j > 29 ||
				i < 0 || i > 16))
			{
				Tile *thisTile = roomTiles["O"][i][j];

				if (!thisTile->haveBlankID())
				{
					m.B = thisTile;

					if (Collision::boxBoxCollisionM(&m))
					{
						if (thisTile->getClimbable())
						{
							climb = true;
						}

						if (thisTile->getDamageValue() > 0)
						{
							damage = true;
						}
						//Utility::log(Utility::I, "Collide with tiles. Normal: X: " + Utility::floatToString(m->normal.x) + " Y: " + Utility::floatToString(m->normal.y) + " Penetration: " + Utility::floatToString(m->penetration) + " Velocity: X  " + Utility::floatToString(m->A->velocity.x) + " Velocity: Y  " + Utility::floatToString(m->A->velocity.y));



					}
				}
			}
		}
	}

	if (climb)
	{
		player->setCanClimb(true);
	}
	else {
		player->setCanClimb(false);
		player->setClimbing(false);
	}

	if (damage)
	{
		player->setAlive(false);
	}


	return 0;

}

bool MapRoom::lineOfSight(Entity *e)
{
	int numLoops = 0;

	for (int i = 0; i < sentinels.size(); i++)
	{
		numLoops += 1;
		std::vector<Vec2> raypoints = sentinels[i]->getLaserPoints();
		bool seen = false;
		bool hit = false;
		int renderPoints = -1;
		int laserNumber;

		for (int j = 0; j < raypoints.size(); j++)
		{
			numLoops += 1;
			if (Collision::pointBoxCollision(raypoints[j], player))
			{
				seen = true;
				hit = true;
			}
			if (hit)
			{
				renderPoints = j;
				break;
			}

			for (int k = 0; k < squares.size(); k++)
			{
				numLoops += 1;
				if (Collision::pointBoxCollision(raypoints[j], squares[k]))
				{
					hit = true;
				}
			}
			if (hit)
			{
				renderPoints = j;
				break;
			}

			for (int k = 0; k < roomMovePlats.size(); k++)
			{
				numLoops += 1;
				MovingPlatform* mp = roomMovePlats[k]->getMovingPlatform();

				if (Collision::pointBoxCollision(raypoints[j], mp))
				{
					hit = true;
				}
			}

			if (hit)
			{
				renderPoints = j;
				break;
			}


			int px = floor(raypoints[j].x / 32);
			int py = floor(raypoints[j].y / 32);

			if (!roomTiles["O"][py][px]->haveBlankID())
			{
				hit = true;
			}
	
			

			if (hit)
			{
				renderPoints = j;
				break;
			}

		}

		if (seen)
		{
			sentinels[i]->setLockedOn(true, player);
		}
		else {
			sentinels[i]->setLockedOn(false);
		}
		if (hit)
		{
			sentinels[i]->setLaserPointsToRender(renderPoints);
		}
		

	}
	

	



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

Character* MapRoom::getPlayer()
{
	return player;
}

std::vector<Square*> MapRoom::getSquares()
{
	return squares;
}

std::vector<Circle*> MapRoom::getCircles()
{
	return circles;
}

bool MapRoom::checkNonBoxMouseCollide(Vec2 mousePos)
{
	bool hit = false;

	int px = floor(mousePos.x / 32);
	int py = floor(mousePos.y / 32);

	if (!roomTiles["O"][py][px]->haveBlankID() && !roomTiles["O"][py][px]->getClimbable())
	{

		hit = true;
	}

	for (int k = 0; k < roomMovePlats.size(); k++)
	{
		MovingPlatform* mp = roomMovePlats[k]->getMovingPlatform();

		if (Collision::pointBoxCollision(mousePos, mp))
		{
			hit = true;
		}
	}

	if (Collision::pointBoxCollision(mousePos, player))
	{
		hit = true;
	}

	return hit;

}