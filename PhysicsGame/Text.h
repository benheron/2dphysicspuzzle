#pragma once
#include <string>
#include "entities/Entity.h"
#include "TextImageManager.h"
#include "TextCharacter.h"

enum Align {
	leftAlign,
	centreAlign
};

class Text : public Entity {
public:


	Text(Vec2 pos, Vec2 dimensions, std::string fontName, int fontSize, std::string theText, TextImageManager *timng);
	~Text();

	

	void update(float dt);

	void render(SDL_Renderer* renderer);

	void changeCharacter(int index, std::string textChar);

	std::string getText();

	void setAlign(Align a);

	void changeTextPosition(Vec2 changeVec);

	

protected:
	void writeText();

	std::string theText;
	std::string fontName;
	int fontSize;
	TextImageManager *timng;

	int spacing;

	std::vector<TextCharacter*> textString;

	

	Align alignment;
	Vec2 origPos;

	Vec2 diffX;
};