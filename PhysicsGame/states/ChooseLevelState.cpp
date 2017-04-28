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
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
				//while mouse is down

				//left click
			case SDL_BUTTON_LEFT:
				//buttons
				for (int i = 0; i < levelButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, levelButtons[i]))
					{
						if (!levelButtons[i]->getSelected())
						{

							playLevel = true;
						}
					}
				}

				for (int i = 0; i < levelIcons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, levelIcons[i]))
					{
						playLevel = true;
						levelToPlay = levelIcons[i]->getLevelID();
					}
				}
				

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


	for (int i = 0; i < levelIcons.size(); i++)
	{
		levelIcons[i]->render(platform->getRenderer());
	}

}

void ChooseLevelState::load()
{
	//generate-map button
	//white texture
	white = new Texture(platform->getRenderer(), 255, 255, 255);

	levTex1 = new Texture("res/img/lev1.png", platform->getRenderer());
	levTex2 = new Texture("res/img/lev2.png", platform->getRenderer());
	levTex3 = new Texture("res/img/lev3.png", platform->getRenderer());


	LevelIcon *li1 = new LevelIcon(Vec2(25, 25), Vec2(114, 95), levTex1, Vec2(104, 65), dtmng->getSaveDataManager()->getLevelFromID("M01"), platform->getRenderer(), dtmng->getTextImageManager());
	LevelIcon *li2 = new LevelIcon(Vec2(175, 25), Vec2(114, 95), levTex2, Vec2(104, 65), dtmng->getSaveDataManager()->getLevelFromID("M02"), platform->getRenderer(), dtmng->getTextImageManager());
	LevelIcon *li3 = new LevelIcon(Vec2(325, 25), Vec2(114, 95), levTex3, Vec2(104, 65), dtmng->getSaveDataManager()->getLevelFromID("M03"), platform->getRenderer(), dtmng->getTextImageManager());

	levelIcons.push_back(li1);
	levelIcons.push_back(li2);
	levelIcons.push_back(li3);

	//Button *level1 = new Button(levTex1, Vec2(25, 25), Vec2(104, 65), Vec2(0, 0));
	//Button *level2 = new Button(levTex2, Vec2(175, 25), Vec2(104, 65), Vec2(0, 0));


	//levelButtons.push_back(level1);
	//levelButtons.push_back(level2);




}

void ChooseLevelState::unload()
{





}
