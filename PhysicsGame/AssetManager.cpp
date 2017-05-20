#include "AssetManager.h"

AssetManager::AssetManager(SDL_Renderer *renderer)
{
	Texture* t = new Texture("res/img/movplatdash.png", renderer);
	miscTextures["dash"] = t;

	Texture* t2 = new Texture("res/img/movplatend.png", renderer);
	miscTextures["platend"] = t2;

	Texture* t3 = new Texture("res/img/lasersight2.png", renderer);
	miscTextures["lasersight"] = t3;

	Texture* t4 = new Texture("res/img/sentinel.png", renderer);
	miscTextures["sentinel"] = t4;

	Texture *t5 = new Texture("res/img/buttons/quittodesktop.png", renderer);
	miscTextures["quittodesktop"] = t5;

	Texture *t6 = new Texture("res/img/buttons/levelselect.png", renderer);
	miscTextures["levelselect"] = t6;

	Texture *t7 = new Texture("res/img/buttons/retrybutton.png", renderer);
	miscTextures["retry"] = t7;

	Texture *t8 = new Texture("res/img/gridselection.png", renderer);
	miscTextures["gridselection"] = t8;

	Texture *controls = new Texture("res/img/controls.png", renderer);
	miscTextures["controls"] = controls;
}

AssetManager::~AssetManager()
{

}

Texture* AssetManager::getTexture(std::string id)
{
	//if (miscTextures.find(id) == miscTextures.end())
	{
		return miscTextures[id];
	}
	
}