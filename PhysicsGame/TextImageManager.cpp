#include "TextImageManager.h"

TextImageManager::TextImageManager(std::string filePath, SDL_Renderer* renderer)
{
	loadTextImageData(filePath, renderer);
}

TextImageManager::~TextImageManager()
{

}

bool TextImageManager::loadTextImageData(std::string filePath, SDL_Renderer* renderer)
{

	Utility::log(Utility::I, "Loading Text Image Data : " + filePath);

	std::ifstream textImgFile(filePath);

	if (textImgFile.is_open())
	{
		std::string fontName;
		std::string imgFile;
		int fontSize;
		bool bold;
		bool italic;
		int numOfLetters;


		textImgFile >> fontName;
		textImgFile >> imgFile;
		textImgFile >> fontSize;
		textImgFile >> bold;
		textImgFile >> italic;
		textImgFile >> numOfLetters;

		Utility::log(Utility::I, "Loading the font image : " + imgFile);
		Texture *t = new Texture(imgFile, renderer);
		

		for (int i = 0; i < numOfLetters; i++)
		{
			int asciiID;
			Vec2 pos;
			Vec2 dimens;

			textImgFile >> asciiID;
			textImgFile >> pos.x;
			textImgFile >> pos.y;
			textImgFile >> dimens.x;
			textImgFile >> dimens.y;

		

			

			std::stringstream ss;
			char c = asciiID;
			std::string textChar;
			ss << c;
			ss >> textChar;

			if (textChar == "")
			{
				std::string tmp = "a b";
				
				textChar = tmp.substr(1, 1);
			}
			Utility::log(Utility::I, "Text character is: " + textChar);
			
			//std::string ID = Utility::intToString(asciiID);

			TextCharacterType *tct = new TextCharacterType(t, asciiID, textChar, pos, dimens);

			TextCharacterTypesAsciiID[asciiID] = tct;
			TextCharacterTypesAsciiLetter[textChar] = tct;
			
		}

		textImgFile.close();

		Utility::log(Utility::I, "Text Image data loaded");

		return true;
	}
	else
	{
		//Error
		Utility::log(Utility::E, "Unable to open Text Image data file : " + filePath);
		return false;
	}
}

TextCharacterType* TextImageManager::getTextCharacterTypeByAscii(int ID)
{
	return TextCharacterTypesAsciiID[ID];
}

TextCharacterType* TextImageManager::getTextCharacterTypeByLetter(std::string l)
{
	return TextCharacterTypesAsciiLetter[l];
}

