#pragma once
#include "../levelManagement/SaveDataManager.h"
#include "../DataManager.h"
#include "LevelIcon.h"

class LevelGrid : public Entity
{
public:
	LevelGrid(Vec2 pos, int columns, int rows, DataManager* dtmng, SDL_Renderer* renderer);
	~LevelGrid();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	std::string getLevelToPlay(Vec2 mousePos);

	int iconSelect(Vec2 mousePos);

	void setNewPosition(Vec2 nPos);

protected:
	int numLevels;

	std::vector<LevelIcon*> levelIcons;
	std::vector<std::string> theLevelIDs;
	std::unordered_map<std::string, Texture*> iconTexturesID;
};