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

	Texture *controlBtn = new Texture("res/img/buttons/controls.png", renderer);
	miscTextures["controlsbtn"] = controlBtn;

	Texture *playgamebtn = new Texture("res/img/buttons/playgame.png", renderer);
	miscTextures["playgamebtn"] = playgamebtn;

	Texture *title = new Texture("res/img/gamelogo.png", renderer);
	miscTextures["gamelogo"] = title;

	Texture *bgmenu = new Texture("res/img/menubg2.png", renderer);
	miscTextures["menubg"] = bgmenu;

	Texture *mmcredits = new Texture("res/img/buttons/credits.png", renderer);
	miscTextures["creditsbtn"] = mmcredits;

	Texture *mmquit = new Texture("res/img/buttons/quit.png", renderer);
	miscTextures["mmquit"] = mmquit;

	Texture *creditspage = new Texture("res/img/credits.png", renderer);
	miscTextures["creditspage"] = creditspage;

	Texture *escback = new Texture("res/img/escback.png", renderer);
	miscTextures["escback"] = escback;

	Texture *mnubg = new Texture("res/img/menubg.png", renderer);
	miscTextures["pmenubg"] = mnubg;

	Texture *resumebtn = new Texture("res/img/buttons/resume.png", renderer);
	miscTextures["resumebtn"] = resumebtn;

	Texture *nextlvlbtn = new Texture("res/img/buttons/nextlevel.png", renderer);
	miscTextures["nextlevel"] = nextlvlbtn;

	Texture *deathface = new Texture("res/img/deathface.png", renderer);
	miscTextures["deathface"] = deathface;

	Texture *bg2 = new Texture("res/img/cityscape.png", renderer);
	miscTextures["cityscape"] = bg2;

	Texture *bg3 = new Texture("res/img/cityscapenight.png", renderer);
	miscTextures["cityscapenight"] = bg3;


	Texture *bg4 = new Texture("res/img/bg2.png", renderer);
	miscTextures["sky"] = bg4;

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