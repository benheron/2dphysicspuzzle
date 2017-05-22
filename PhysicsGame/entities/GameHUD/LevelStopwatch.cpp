#include "LevelStopwatch.h"


LevelStopwatch::LevelStopwatch(Vec2 pos, Vec2 dimensions, TextImageManager *timng) : Entity(pos, dimensions)
{
	startTime = SDL_GetTicks();
	now = startTime;
	lastTime = SDL_GetTicks();

	elapsedTime = 0;



	//Text *minText = new Text(pos, dimensions, "Arial", 32, "00", timng);
	//Text *secText = new Text(pos, dimensions, "Arial", 32, "00", timng);
	//Text *milText = new Text(pos, dimensions, "Arial", 32, "000", timng);

	//Text *spaceColonSpace = new Text(pos, dimensions, "Arial", 32, " : ", timng);
	
	elapsedTimeString = "00 : 00 : 000";
	elapsedTimeText = new Text(pos, dimensions, "Arial", 32, elapsedTimeString, timng);
	
}

LevelStopwatch::LevelStopwatch(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	startTime = SDL_GetTicks();
	now = startTime;
	lastTime = SDL_GetTicks();
	elapsedTime = 0;
}


LevelStopwatch::LevelStopwatch(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{
	startTime = SDL_GetTicks();
	now = startTime;

	elapsedTime = 0;
}

LevelStopwatch::~LevelStopwatch()
{
	delete elapsedTimeText;
}

void LevelStopwatch::update(float dt)
{

	if (!stopped)
	{
		elapsedTime += dt * 1000;

		lastTime = now;

		int min = (elapsedTime / 1000) / 60;
		int sec = (elapsedTime / 1000) % 60;
		int mil = elapsedTime % 1000;

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


		elapsedTimeString = stringMin + " : " + stringSec + " : " + stringMil;

		std::string curDisplayTime = elapsedTimeText->getText();
		for (int i = 0; i < elapsedTimeString.length(); i++)
		{
			std::string cdt = curDisplayTime.substr(i, 1);
			std::string ets = elapsedTimeString.substr(i, 1);

			if (cdt != ets)
			{
				elapsedTimeText->changeCharacter(i, elapsedTimeString.substr(i, 1));
			}
		}
	}
	
	
}


void LevelStopwatch::render(SDL_Renderer *renderer)
{
	/*Texture *nTex = new Texture(renderer, elapsedTimeString, font, { 255,255,255 });
	Texture *oldTex = texture;

	texture = nTex;
	//delete oldTex;

	texture->renderText(renderer, pos, 1);*/

	elapsedTimeText->render(renderer);
}


void LevelStopwatch::stop()
{
	stopped = true;
}

void LevelStopwatch::start()
{
	stopped = false;
}

bool LevelStopwatch::isRunning()
{
	return running;
}

unsigned int LevelStopwatch::getTime()
{
	return elapsedTime;
}

std::string LevelStopwatch::getTimeString()
{
	return elapsedTimeString;
}

Text* LevelStopwatch::getTimeText()
{
	return elapsedTimeText;
}