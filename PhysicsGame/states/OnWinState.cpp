#include "OnWinState.h"

OnWinState::OnWinState(StateManager* manager, Platform *platform, DataManager *d, bool &retry, LevelStopwatch *levelTime, Level* curLevel) : State(manager, platform), retry(retry), levelTime(levelTime), curLevel(curLevel)
{
	stateName = "OnWinState";
	dtmng = d;
}

OnWinState::~OnWinState()
{

}

bool OnWinState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;


	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			for (int i = 0; i < winStateButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, winStateButtons[i]->getPosition(), winStateButtons[i]->getDimensions()))
				{
					if (!winStateButtons[i]->getHover())
					{
						dtmng->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
					}
					winStateButtons[i]->setHover(true);


				}
				else {
					winStateButtons[i]->setIdle();
				}
			}


			break;
		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
				//while mouse is down

				//left click
			case SDL_BUTTON_LEFT:
				leftDown = true;
				for (int i = 0; i < winStateButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, winStateButtons[i]->getPosition(), winStateButtons[i]->getDimensions()))
					{

						winStateButtons[i]->setSelected(true);
					}

				}

				if (Collision::pointBoxCollision(mousePos, quitDesktopBtn->getPosition(), quitDesktopBtn->getDimensions()))
				{
					return true;
				}

				break;


			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				/*leftDown = false;
				for (int i = 0; i < pauseMenuButtons.size(); i++)
				{
				if (Collision::pointBoxCollision(mousePos, pauseMenuButtons[i]->getPosition(), pauseMenuButtons[i]->getDimensions()))
				{
				pauseMenuButtons[i]->setSelected(false);
				pauseMenuButtons[i]->setHover(true);
				}
				}*/
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:


				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
				//letting go of a key
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}


void OnWinState::update(float dt)
{
	if (nextlevelBtn->getSelected())
	{
		int levelIndex = curLevel->getLevelIndex();
		Level *nextLevel = dtmng->getSaveDataManager()->getLevelFromIndex(levelIndex + 1);
		nextlevelBtn->setIdle();
		stateManager->changeState(new GameState(stateManager, platform, dtmng, nextLevel));
	}
	else
	if (retryButton->getSelected())
	{
		retry = true;
		retryButton->setIdle();
		stateManager->popLastState();
	}
	else

		if (quitMenuBtn->getSelected())
		{
			quitMenuBtn->setIdle();
			stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
		}
}

void OnWinState::render()
{
	dtmng->getAssetManager()->getTexture("menubg")->pushSpriteToScreen(platform->getRenderer(), bgPos);
	levelComplete->render(platform->getRenderer());
	levTimeEnd->render(platform->getRenderer());
	
	for (int i = 0; i < winStateButtons.size(); i++)
	{
		winStateButtons[i]->render(platform->getRenderer());
	}
}

void OnWinState::load()
{
	Vec2 btnSize = Vec2(320, 72);

	int xPos = (platform->getWindowSize().x / 2) - (btnSize.x / 2);

	nextlevelBtn = new Button(dtmng->getAssetManager()->getTexture("nextlevel"), Vec2(xPos, 187), btnSize, 0);

	retryButton = new Button(dtmng->getAssetManager()->getTexture("retry"), Vec2(xPos, 269), btnSize, 0);

	quitMenuBtn = new Button(dtmng->getAssetManager()->getTexture("levelselect"), Vec2(xPos, 351), btnSize, 0);

	quitDesktopBtn = new Button(dtmng->getAssetManager()->getTexture("quittodesktop"), Vec2(xPos, 433), btnSize, 0);

	winStateButtons.push_back(nextlevelBtn);
	winStateButtons.push_back(retryButton);
	winStateButtons.push_back(quitMenuBtn);
	winStateButtons.push_back(quitDesktopBtn);

	bgPos = platform->getWindowSize() / 2 - Vec2(365, 250);

	levelComplete = new Text(Vec2(platform->getWindowSize().x / 2, 35.f), 0, "arial", 34, "LEVEL COMPLETE!", dtmng->getTextImageManager());
	levelComplete->setAlign(centreAlign);


	levTimeString = levelTime->getTimeString();
	
	levTimeEnd = new Text(Vec2(platform->getWindowSize().x / 2, 80.f), 0, "arial", 32, "Time: " + levTimeString, dtmng->getTextImageManager());
	levTimeEnd->setAlign(centreAlign);

	

	

}

void OnWinState::unload()
{
	for (int i = 0; i < winStateButtons.size(); i++)
	{
		delete winStateButtons[i];
	}

	delete levelComplete;
	delete levTimeEnd;
}