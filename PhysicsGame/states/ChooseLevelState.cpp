#include "ChooseLevelState.h"
#include "../Utility.h"
#include "../Collision.h"




ChooseLevelState::ChooseLevelState(StateManager* manager, Platform *platform, DataManager *d)
	: State(manager, platform)
{
	stateName = "ChooseLevelState";
	dtmng = d;
}

ChooseLevelState::~ChooseLevelState()
{

}

bool ChooseLevelState::eventHandler()
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
			//while mouse is moving
			
			if (levelGrid->iconSelect(mousePos) == 2)
			{
				dtmng->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			}


			//buttons
			for (int i = 0; i < levelButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, levelButtons[i]))
				{
					if (!levelButtons[i]->getSelected())
					{
						levelButtons[i]->setHover(true);
					}
				}
				else {
					levelButtons[i]->setHover(false);
				}
			}


			break;
		case SDL_QUIT:
			//return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
				//while mouse is down

				//left click
			case SDL_BUTTON_LEFT:
				//buttons
				/*for (int i = 0; i < levelButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, levelButtons[i]))
					{
						if (!levelButtons[i]->getSelected())
						{

							playLevel = true;
						}
					}
				}*/

				if (Collision::pointBoxCollision(mousePos, levelGrid))
				{
					levelToPlay = levelGrid->getLevelToPlay(mousePos);

					if (levelToPlay != "No Level")
					{
						playLevel = true;
					}
				}

				/*for (int i = 0; i < levelIcons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, levelIcons[i]))
					{
						playLevel = true;
						levelToPlay = levelIcons[i]->getLevelID();
					}
				}*/
				

				break;


			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				

				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//pause menu
				//stateManager->addState(pms);
				stateManager->changeState(new MainMenuState(stateManager, platform, dtmng));
				break;
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

void ChooseLevelState::update(float dt)
{
	if (playLevel)
	{
		stateManager->changeState(new GameState(stateManager, platform, dtmng, dtmng->getSaveDataManager()->getLevelFromID(levelToPlay)));
	}
}

void ChooseLevelState::render()
{

	/*for (int i = 0; i < levelButtons.size(); i++)
	{
		levelButtons[i]->render(platform->getRenderer());
	}*/

	/*for (int i = 0; i < levelIcons.size(); i++)
	{
	levelIcons[i]->render(platform->getRenderer());
	}*/

	chooseStateTex->pushSpriteToScreen(platform->getRenderer(), Vec2((platform->getWindowSize().x / 2) - 192.f, 30.f), 0, Vec2(384, 41));



	levelGrid->render(platform->getRenderer());

}

void ChooseLevelState::load()
{
	//generate-map button
	//white texture
	//white = new Texture(platform->getRenderer(), 255, 255, 255);

	chooseStateTex = new Texture("res/img/chooselevel.png", platform->getRenderer());

	levelGrid = new LevelGrid(Vec2(50, 100), 5, 3, dtmng, platform->getRenderer());

	float lgx = (platform->getWindowSize().x / 2) -(levelGrid->getDimensions().x / 2);

	Vec2 tmp = levelGrid->getPosition();

	levelGrid->setNewPosition(Vec2(lgx, tmp.y));
}

void ChooseLevelState::unload()
{

	delete levelGrid;
	delete chooseStateTex;



}
