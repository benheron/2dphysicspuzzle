#pragma once
#include "../Texture.h"
#include "../Vec2.h"
#include "../entities/Entity.h"
#include "../levelManagement/Level.h"
#include "../Utility.h" 
#include "../Text.h"
#include "../entities/Button.h"

/**
@brief A slider that holds values between a min and max. Uses SliderSquare
*/
class LevelIcon : public Button {
public:


	LevelIcon(Vec2 pos, Vec2 dimensions, Texture* li, Vec2 textSize, Level *levelData, SDL_Renderer *renderer, TextImageManager *timng, Texture *bg);

	~LevelIcon();

	void render(SDL_Renderer* renderer);

	void update(float dt);
	
	std::string getLevelID();

	void changeIconPosition(Vec2 cip);

private:

	Texture *levelImage;
	std::string levelTime;
	Vec2 timePos;
	Vec2 timeScale;
	bool complete;

	std::string levelID;


	Vec2 imgPos;
	Vec2 imgSize;

	//Texture *timeText;
	//TTF_Font *font = NULL;

	Text* levelIDText;
	Text* completeText;

	Text* fastestTime;
	Text *timeText;

	Texture* background;

	Level *levelData;
};