#include "Text.h"

Text::Text(Vec2 pos, Vec2 dimensions, std::string fontName, int fontSize, std::string theText, TextImageManager *timng) : Entity(pos, dimensions), 
fontName(fontName), fontSize(fontSize), theText(theText), timng(timng)
{
	spacing = 0;
	writeText();
	origPos = pos;
}

Text::~Text()
{

}

void Text::writeText()
{
	int stringLength = theText.length();

	

	for (int i = 0; i < stringLength; i++)
	{
		TextCharacter *tc;
		std::string id = theText.substr(i, 1);
		Vec2 newPosVec;
		TextCharacterType *tct = timng->getTextCharacterTypeByLetter(id);
		if (i != 0)
		{
			float newPosX = textString[i-1]->getPosition().x + textString[i-1]->getDimensions().x + spacing;

			newPosVec = Vec2(newPosX, textString[i-1]->getPosition().y);
		}
		else {
			newPosVec = pos;
		}
		tc = new TextCharacter(newPosVec, tct->getTextCharacterDimensions()/32 * fontSize, tct);
		textString.push_back(tc);

		dimensions += tct->getTextCharacterDimensions() / 32 * fontSize;
	}
}

void Text::update(float dt)
{

}

void Text::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < textString.size(); i++)
	{
		textString[i]->render(renderer);
	}
}

void Text::changeCharacter(int index, std::string textChar)
{
	textString[index]->setTextCharacterType(timng->getTextCharacterTypeByLetter(textChar));
	theText.replace(index, 1, textChar);
}

std::string Text::getText()
{
	return theText;
}

void Text::setAlign(Align a)
{
	if (alignment != a)
	{
		alignment = a;

		if (alignment == leftAlign)
		{
			pos = origPos;
			for (int i = 0; i < textString.size(); i++)
			{
				Vec2 ts = textString[i]->getPosition();
				ts.x += dimensions.x / 2;

				textString[i]->setPosition(ts);
			}

		}
		else if (alignment == centreAlign) {
			pos.x = origPos.x - dimensions.x / 2;
			for (int i = 0; i < textString.size(); i++)
			{
				Vec2 ts = textString[i]->getPosition();
				ts.x -= dimensions.x / 2;

				textString[i]->setPosition(ts);
			}
		}
	}
}

void Text::changeTextPosition(Vec2 changeVec)
{
	for (int i = 0; i < textString.size(); i++)
	{
		Vec2 tPos = textString[i]->getPosition();
		tPos += changeVec;
		textString[i]->setPosition(tPos);
	}
}