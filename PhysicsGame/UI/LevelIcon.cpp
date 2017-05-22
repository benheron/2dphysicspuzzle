#include "LevelIcon.h"

LevelIcon::LevelIcon(Vec2 pos, Vec2 dimensions, Texture* li, Vec2 textSize, Level *levelData, SDL_Renderer *renderer, TextImageManager *timng, Texture*bg) : Button(pos, dimensions), background(bg), levelData(levelData)
{
	levelImage = li;
	imgSize = textSize;

	levelID = levelData->getID();

	unsigned int timeInt = levelData->getFastestTime();

	int min = (timeInt / 1000) / 60;
	int sec = (timeInt / 1000) % 60;
	int mil = timeInt % 1000;

	std::string stringMin = min < 10 ? "0" + Utility::intToString(min) : Utility::intToString(min);
	std::string stringSec = sec < 10 ? "0" + Utility::intToString(sec) : Utility::intToString(sec);
	std::string stringMil;

	if (mil < 10)
	{
		stringMil = "00" + Utility::intToString(mil);

	}
	else if (mil < 100)
	{
		stringMil = "0" + Utility::intToString(mil);
	}
	else {
		stringMil = Utility::intToString(mil);
	}


	levelTime = stringMin + ":" + stringSec + ":" + stringMil;
	int numChar = levelTime.length();
	timeScale = Vec2(numChar * 10, 20);
	timeScale /= 1.5f;

	complete = levelData->hasComplete();

	int imgX = pos.x + (dimensions.x / 2) - imgSize.x/2;
	int imgY = pos.y + 5;// (dimensions.y / 2) - imgSize.y / 2;

	imgPos = Vec2(imgX, imgY);

	int timeX = pos.x + dimensions.x / 2;
	int timeY = imgPos.y + imgSize.y + 5;
	timePos = Vec2(timeX, timeY);


	//font = TTF_OpenFont("res/fonts/ariblk.ttf", 20);


	//timeText = new Texture(renderer, levelTime, font, { 255,255,255 });

	timeText = new Text(Vec2(timePos.x, timePos.y + 45), 2, "Arial", 20, levelTime, timng);

	timeText->setAlign(centreAlign);


	fastestTime = new Text(Vec2(timePos.x, timePos.y + 25), 2, "Arial", 20, "Fastest Time:", timng);
	fastestTime->setAlign(centreAlign);

	levelIDText = new Text(timePos, 2, "Arial", 20, levelData->getID(), timng);
	levelIDText->setAlign(centreAlign);

	completeText = new Text(Vec2(timePos.x, timePos.y + 75), 2, "Arial", 20, "Complete!", timng);
	completeText->setAlign(centreAlign);
}

LevelIcon::~LevelIcon()
{

}

void LevelIcon::update(float dt)
{

}

void LevelIcon::render(SDL_Renderer* renderer)
{
	switch (bState)
	{
	case Button::buttonHover:
		background->pushSpriteToScreen(renderer, pos, dimensions, Vec2(0, 200), Vec2(200, 200));
		break;
	case Button::buttonSelected:
		background->pushSpriteToScreen(renderer, pos, dimensions, 0, Vec2(200, 200));
		//texture->pushSpriteToScreen(renderer, pos, Vec2(spritePos.x, spriteDimensions.y * 2), spriteDimensions);
		break;
	case Button::buttonIdle:
		background->pushSpriteToScreen(renderer, pos, dimensions, 0, Vec2(200, 200));
		break;
	default:
		background->pushSpriteToScreen(renderer, pos, dimensions, 0, Vec2(200, 200));
		break;
	}


	levelImage->pushSpriteToScreen(renderer, imgPos, Vec2(0, 0), imgSize);
	//timeText->renderText(renderer, timePos, timeScale);
	levelIDText->render(renderer);
	fastestTime->render(renderer);
	

	if (levelData->hasComplete())
	{
		completeText->render(renderer);
		timeText->render(renderer);
	}

	

}

std::string LevelIcon::getLevelID()
{
	return levelID;
}

void LevelIcon::changeIconPosition(Vec2 cip)
{
	imgPos += cip;
	pos += cip;
	timeText->changeTextPosition(cip);
	fastestTime->changeTextPosition(cip);
	levelIDText->changeTextPosition(cip);
	completeText->changeTextPosition(cip);
}