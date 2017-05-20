#include "OnDeathState.h"

OnDeathState::OnDeathState(StateManager* manager, Platform *platform, DataManager *d,bool &retry) : State(manager, platform), retry(retry)
{
	stateName = "OnDeathState";
	dtmng = d;
}

OnDeathState::~OnDeathState()
{

}

bool OnDeathState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;
	/*for (int i = 0; i < deathStateButtons.size(); i++)
	{
		deathStateButtons[i]->setIdle();
	}

	for (int i = 0; i < deathStateButtons.size(); i++)
	{
		if (Collision::pointBoxCollision(mousePos, deathStateButtons[i]->getPosition(), deathStateButtons[i]->getDimensions()))
		{
			deathStateButtons[i]->setHover(true);
		}
	}*/

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			for (int i = 0; i < deathStateButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, deathStateButtons[i]->getPosition(), deathStateButtons[i]->getDimensions()))
				{
					if (!deathStateButtons[i]->getHover())
					{
						dtmng->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
					}
					deathStateButtons[i]->setHover(true);


				}
				else {
					deathStateButtons[i]->setIdle();
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
				for (int i = 0; i < deathStateButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, deathStateButtons[i]->getPosition(), deathStateButtons[i]->getDimensions()))
					{
					
						deathStateButtons[i]->setSelected(true);
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

				stateManager->popLastStateWithoutDelete();
				return false;
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


void OnDeathState::update(float dt)
{
	if (retryButton->getSelected())
	{
		retry = true;
		retryButton->setIdle();
		stateManager->popLastState();
	} else 

	if (quitMenuBtn->getSelected())
	{
		quitMenuBtn->setIdle();
		stateManager->changeState(new ChooseLevelState(stateManager, platform, dtmng));
	}
}

void OnDeathState::render()
{
	for (int i = 0; i < deathStateButtons.size(); i++)
	{
		deathStateButtons[i]->render(platform->getRenderer());
	}
}

void OnDeathState::load()
{
	Vec2 btnSize = Vec2(320, 72);

	int xPos = (platform->getWindowSize().x / 2) - (btnSize.x / 2);


	retryButton = new Button(dtmng->getAssetManager()->getTexture("retry"), Vec2(xPos, 30), btnSize, 0);

	quitMenuBtn = new Button(dtmng->getAssetManager()->getTexture("levelselect"), Vec2(xPos, 120), btnSize, 0);

	quitDesktopBtn = new Button(dtmng->getAssetManager()->getTexture("quittodesktop"), Vec2(xPos, 210), btnSize, 0);

	deathStateButtons.push_back(retryButton);
	deathStateButtons.push_back(quitMenuBtn);
	deathStateButtons.push_back(quitDesktopBtn);

}

void OnDeathState::unload()
{

}