#include "MainMenuState.h"
#include "../Utility.h"
#include "../Collision.h"

MainMenuState::MainMenuState(StateManager* manager, Platform *platform, DataManager *d)
	: State(manager, platform)
{
	stateName = "MainMenuState";
	dtmng = d;
}

MainMenuState::~MainMenuState()
{

}

bool MainMenuState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Event events;
	mousePos = Vec2(mouseX, mouseY);

	/*for (int i = 0; i < mainMenuButtons.size(); i++)
	{
		mainMenuButtons[i]->setIdle();
	}

	for (int i = 0; i < mainMenuButtons.size(); i++)
	{
		if (Collision::pointBoxCollision(mousePos, mainMenuButtons[i]->getPosition(), mainMenuButtons[i]->getDimensions()))
		{
			mainMenuButtons[i]->setHover(true);
		}
	}
*/

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			//hovering

			for (int i = 0; i < mainMenuButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, mainMenuButtons[i]->getPosition(), mainMenuButtons[i]->getDimensions()))
				{
					if (!mainMenuButtons[i]->getHover())
					{
						mainMenuButtons[i]->setHover(true);
						dtmng->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
					}
					
				}
				else {
					mainMenuButtons[i]->setIdle();
				}
			}

		/*	for (int i = 0; i < mainMenuButtons.size(); i++)
			{
				if (!mainMenuButtons[i]->getHover())
				{
					if (mainMenuButtons[i]->mouseCollide(mouseX, mouseY))
					{
						mainMenuButtons[i]->setHover(true);
						dtmng->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
						//sf->playAudio(0);
					}
					else {
						mainMenuButtons[i]->setHover(false);
					}
				}
				else {
					if (!mainMenuButtons[i]->mouseCollide(mouseX, mouseY))
					{
						mainMenuButtons[i]->setHover(false);
					}
				}
			}*/
			break;

		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:

				for (int i = 0; i < mainMenuButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, mainMenuButtons[i]->getPosition(), mainMenuButtons[i]->getDimensions()))
					{
						//pauseMenuButtons[i]->setHover(false);
						mainMenuButtons[i]->setSelected(true);
					}
					else {
						//	pauseMenuButtons[i]->setSelected(false);
					}
				}
				if (quitgamebtn->getSelected())
				{
					return true;
				}

				/*Utility::log(Utility::I, Utility::intToString(mouseX));
				//sf->playAudio(0);
				if (Collision::pointBoxCollision(Vec2(mouseX, mouseY), redPlay->getPosition(), redPlay->getDimensions()))
				{
					redDown = true;
				}*/
				
				
			break;

			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				//do same as quit
				return true;
				break;
				//temporary movement
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void MainMenuState::update(float dt)
{
	/*if (redDown)
	{
		//stateManager->changeState(new GameState(stateManager, platform, ttmng, cmng, mmng, 0, pms));
		stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
		return;
	}
*/

	if (redPlay->getSelected())
	{
		stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
		return;
	}
	
	if (controlsBtn->getSelected())
	{
		controlsBtn->setIdle();
		stateManager->addState(new ShowControlsState(stateManager, platform, dtmng));
	}

	if (creditsBtn->getSelected())
	{
		creditsBtn->setIdle();
		stateManager->addState(new CreditsState(stateManager, platform, dtmng));
	}
}

void MainMenuState::render()
{
	dtmng->getAssetManager()->getTexture("gamelogo")->pushSpriteToScreen(platform->getRenderer(), logoPosition, logoDimensions);

	for (int i = 0; i < mainMenuButtons.size(); i++)
	{
		mainMenuButtons[i]->render(platform->getRenderer());
	}

	

	//playTexture->pushToScreen(platform->getRenderer(), Vec2(20, 20), 20);
}

void MainMenuState::load()
{
	logoPosition = Vec2(platform->getWindowSize().x / 2 - 334, 35.f);
	logoDimensions = Vec2(668, 141);



	//background
	redPlay = new Button(dtmng->getAssetManager()->getTexture("playgamebtn"), Vec2(60, 140), Vec2(250, 100), Vec2(0,0));
	controls = dtmng->getAssetManager()->getTexture("controls");

	controlsBtn = new Button(dtmng->getAssetManager()->getTexture("controlsbtn"), Vec2(60, 240), Vec2(250, 100), 0);

	creditsBtn = new Button(dtmng->getAssetManager()->getTexture("creditsbtn"), Vec2(60, 340), Vec2(250, 100), 0);

	quitgamebtn = new Button(dtmng->getAssetManager()->getTexture("mmquit"), Vec2(60, 440), Vec2(250, 100), 0);

	dtmng->getAudioManager()->getMusicByName("TitleScreen")->playAudio(-1);



	mainMenuButtons.push_back(redPlay);
	mainMenuButtons.push_back(controlsBtn);
	mainMenuButtons.push_back(creditsBtn);
	mainMenuButtons.push_back(quitgamebtn);
}

void MainMenuState::unload()
{
	for (int i = 0; i < mainMenuButtons.size(); i++)
	{
		delete mainMenuButtons[i];
	}

}