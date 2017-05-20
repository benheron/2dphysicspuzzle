#include "ShowControlsState.h"

ShowControlsState::ShowControlsState(StateManager* manager, Platform *platform, DataManager *d) : State(manager, platform), dtmng(d)
{

}




ShowControlsState::~ShowControlsState()
{

}

bool ShowControlsState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Vec2 mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;


	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:


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
				
				break;
			}
			break;
		}
	}
	return false;
}

void ShowControlsState::update(float dt)
{

}


void ShowControlsState::render() {
	controls->pushSpriteToScreen(platform->getRenderer(), 0);
}

void ShowControlsState::load()
{
	controls = dtmng->getAssetManager()->getTexture("controls");

}
void ShowControlsState::unload()
{

}