#include "CreditsState.h"

CreditsState::CreditsState(StateManager* manager, Platform *platform, DataManager *d) : State(manager, platform), dtmng(d)
{
	stateName = "CreditsState";
}




CreditsState::~CreditsState()
{

}

bool CreditsState::eventHandler()
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
			return true;
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

void CreditsState::update(float dt)
{

}


void CreditsState::render() {
	credits->pushSpriteToScreen(platform->getRenderer(), 0);
	dtmng->getAssetManager()->getTexture("escback")->pushSpriteToScreen(platform->getRenderer(), Vec2(843, 508));
}

void CreditsState::load()
{
	credits = dtmng->getAssetManager()->getTexture("creditspage");

}
void CreditsState::unload()
{

}