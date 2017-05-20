#include "LevelGrid.h"

LevelGrid::LevelGrid(Vec2 pos, int columns, int rows, DataManager* dtmng, SDL_Renderer* renderer) : Entity(pos)
{
	SaveDataManager *smng = dtmng->getSaveDataManager();
	theLevelIDs = smng->getTheLevelIDs();
	numLevels = smng->getNumLevels();
	//iconTexturesID = smng->getLevelIconFromID(levelID);
	Vec2 iconDimens = Vec2(114, 125);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if ((i*columns + j) < numLevels)
			{
				std::string levelID = theLevelIDs[i*columns + j];
				Texture *iconTexture = smng->getLevelIconFromID(levelID);


				

				Vec2 iconPos;

				float iconPosX = (j * iconDimens.x) + pos.x;
				float iconPosY = (i * iconDimens.y) + pos.y;

				iconPos = Vec2(iconPosX, iconPosY);


				LevelIcon *li = new LevelIcon(iconPos, iconDimens, iconTexture, Vec2(104, 65), smng->getLevelFromID(levelID), renderer, dtmng->getTextImageManager(), dtmng->getAssetManager()->getTexture("gridselection"));

				levelIcons.push_back(li);
			}
			else {
				break;
			}
		}

	}
	dimensions = Vec2(iconDimens.x*columns, iconDimens.y*rows);

}

LevelGrid::~LevelGrid()
{

}
void LevelGrid::update(float dt)
{

}

void LevelGrid::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < levelIcons.size(); i++)
	{
		levelIcons[i]->render(renderer);
	}
}

std::string LevelGrid::getLevelToPlay(Vec2 mousePos)
{
	bool valid = false;
	std::string levelToPlay;
	for (int i = 0; i < levelIcons.size(); i++)
	{
		if (Collision::pointBoxCollision(mousePos, levelIcons[i]))
		{
			valid = true;
			levelToPlay = levelIcons[i]->getLevelID();
		}
	}

	if (valid)
	{
		return levelToPlay;
	}
	return "No Level";
}

int LevelGrid::iconSelect(Vec2 mousePos)
{
	int returnValue = 0;
	for (int i = 0; i < levelIcons.size(); i++)
	{
		if (Collision::pointBoxCollision(mousePos, levelIcons[i]))
		{
			if (!levelIcons[i]->getHover())
			{
				levelIcons[i]->setHover(true);
				returnValue = 2;
			}
			else {
				//returnValue = 1;
			}
		}
		else {
			levelIcons[i]->setIdle();
			//returnValue = 0;
		}
	}
	return returnValue;
}

void LevelGrid::setNewPosition(Vec2 nPos)
{
	Vec2 diff = nPos - pos;

	for (int i = 0; i < levelIcons.size(); i++)
	{
	//	Vec2 liPos = levelIcons[i]->getPosition();
	//	liPos += diff;
	//	levelIcons[i]->setPosition(liPos);
		levelIcons[i]->changeIconPosition(diff);
	}
	pos = nPos;
}