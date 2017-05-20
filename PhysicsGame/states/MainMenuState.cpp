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
		stateManager->addState(new ShowControlsState(stateManager, platform, dtmng));
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < mainMenuButtons.size(); i++)
	{
		mainMenuButtons[i]->render(platform->getRenderer());
	}

	

	//playTexture->pushToScreen(platform->getRenderer(), Vec2(20, 20), 20);
}

void MainMenuState::load()
{
	playTexture = new Texture("res/img/buttons/playBtn.png", platform->getRenderer());

	//background
	redPlay = new Button(playTexture, Vec2(60, 40), Vec2(250, 115), Vec2(0,0));
	controls = dtmng->getAssetManager()->getTexture("controls");

	controlsBtn = new Button(playTexture, Vec2(60, 250), Vec2(250, 115), 0);

	dtmng->getAudioManager()->getMusicByName("TitleScreen")->playAudio(-1);



	mainMenuButtons.push_back(redPlay);
	mainMenuButtons.push_back(controlsBtn);
}

void MainMenuState::unload()
{
	delete playTexture;
	delete redPlay;
}