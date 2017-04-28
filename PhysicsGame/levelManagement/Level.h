#pragma once

#include <string>
#include <vector>
#include "RoomTemplate.h"
#include "MapRoom.h"

class Level {
public:
	Level(RoomTemplate *rt,std::string ID, unsigned int fastestTime, int numSecrets, bool complete);
	~Level();

	void loadLevel(std::string levelID);

	void setID(std::string ID);
	std::string getID();
	void setFastestTime(unsigned int ft);
	unsigned int getFastestTime();
	void setNumSecrets(int n);
	int getNumSecrets();
	void setComplete(bool c);
	bool hasComplete();

protected:
	std::string ID;
	RoomTemplate *rt;
	MapRoom* room;
	unsigned int fastestTime;
	int numSecrets;
	bool complete;
};