#include "Level.h"

#include "RoomTemplate.h"
#include "MapRoom.h"
Level::Level(RoomTemplate *rt, std::string ID, unsigned int fastestTime, int numSecrets, bool complete) : ID(ID), rt(rt), fastestTime(fastestTime), numSecrets(numSecrets), complete(complete)
{

}

Level::~Level()
{

}

void Level::loadLevel(std::string levelID)
{

}

void Level::setID(std::string ID)
{
	this->ID = ID;
}

std::string Level::getID()
{
	return ID;
}
void Level::setFastestTime(unsigned int ft)
{
	fastestTime = ft;
}

unsigned int Level::getFastestTime()
{
	return fastestTime;
}

void Level::setNumSecrets(int n)
{
	numSecrets = n;
}

int Level::getNumSecrets()
{
	return numSecrets;
}

void Level::setComplete(bool c)
{
	complete = c;
}

bool Level::hasComplete()
{
	return complete;
}

void Level::setLevelIndex(int i)
{
	levelIndex = i;
}

int Level::getLevelIndex()
{
	return levelIndex;
}
