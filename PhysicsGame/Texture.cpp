#include "Texture.h"
#include "Utility.h"


//creates basic texture
Texture::Texture(SDL_Renderer* renderer, int r, int g, int b)
{
	//Creates the surface
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, (Uint8)r, (Uint8)g, (Uint8)b));
	
	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//delete the surface from memory
	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Renderer* renderer, SDL_Colour colour)
{
	//Creates the surface
	SDL_Surface *surface;
	surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);

	//Fills the surface with the color
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, colour.r, colour.g, colour.b));

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//delete the surface from memory
	SDL_FreeSurface(surface);
}

Texture::Texture(std::string fileLocation, SDL_Renderer* renderer)
{
	//Loads the image as a surface
	SDL_Surface* image = IMG_Load(fileLocation.c_str());

	//Image load check
	if (!image)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Utility::log(Utility::E, message);
		return;
	}

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, image);

	//delete the surface from memory
	SDL_FreeSurface(image);

	//store the size of the texture
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);
}

Texture::Texture(std::string fileLocation, SDL_Renderer* renderer, bool magentaAlpha)
{
	//Loads the image as a surface
	SDL_Surface* image = SDL_LoadBMP(fileLocation.c_str());

	//Image load check
	if (!image)
	{
		//Error message
		std::string message = "Unable to load image from: " + fileLocation + ", Error is: " + IMG_GetError();
		Utility::log(Utility::E, message);
		return;
	}

	//Check if the images magenta is to be used as the alpha
	if (magentaAlpha)
	{
		//Replaces magenta with alpha
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 0, 255));
	}

	//Converts the surface into texture data
	textureData = SDL_CreateTextureFromSurface(renderer, image);

	//delete the surface from memory
	SDL_FreeSurface(image);

	//store the size of the texture
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);
}

Texture::Texture(SDL_Renderer *renderer, std::string text, TTF_Font *font, int r, int g, int b)
{
	SDL_Colour colour = { r, g, b };
	//Render text surface
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), colour);
	
	//Create texture from surface pixels
	textureData = SDL_CreateTextureFromSurface(renderer, surface);
		
	//Get image dimensions
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);

	/*mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_QueryTexture(textureData, NULL, NULL, )*/
}

Texture::Texture(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Colour colour)
{



	//Render text surface
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), colour);

	//Create texture from surface pixels
	textureData = SDL_CreateTextureFromSurface(renderer, surface);

	//Get image dimensions
	int textureWidth, textureHeight;
	SDL_QueryTexture(textureData, NULL, NULL, &textureWidth, &textureHeight);
	dimensions = Vec2(textureWidth, textureHeight);

}







Texture::~Texture()
{
	//deletes the texture from memory
	SDL_DestroyTexture(textureData);
}

SDL_Texture* Texture::getTexture()
{
	return textureData;
}

Vec2 Texture::getDimensions()
{
	return dimensions;
}

void Texture::pushToScreen(SDL_Renderer* renderer, Vec2 pos)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Texture::pushToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)scale.x;
	destRect.h = (int)scale.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)dimensions.x;
	destRect.h = (int)dimensions.y;

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = (int)dimensions.x;
	srcRect.h = (int)dimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);
}

void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)abs(scale.x);
	destRect.h = (int)abs(scale.y);

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = (int)dimensions.x;
	srcRect.h = (int)dimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);
}

void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 spritePos, Vec2 spriteDimensions)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)spriteDimensions.x;
	destRect.h = (int)spriteDimensions.y;

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);
}

void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale, Vec2 spritePos, Vec2 spriteDimensions)
{
	//Create the destination rectangle of the texture
	SDL_RendererFlip flipType;
	if (scale.x < 0)
	{
		flipType = SDL_FLIP_HORIZONTAL;
	}
	else {
		flipType = SDL_FLIP_NONE;
	}

	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)abs(scale.x);
	destRect.h = (int)abs(scale.y);

	//destRect.w = (int)abs(scale.x);
	//destRect.h = (int)abs(scale.y);

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	//SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);

	SDL_RenderCopyEx(renderer, textureData, &srcRect, &destRect, 0.0, NULL, flipType);

}

void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale, Vec2 spritePos, Vec2 spriteDimensions, SDL_RendererFlip flipType)
{
/*
	//Create the destination rectangle of the texture
	SDL_RendererFlip flipType;
	if (scale.x < 0)
	{
		flipType = SDL_FLIP_HORIZONTAL;
	}
	else {
		flipType = SDL_FLIP_NONE;
	}*/

	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)abs(scale.x);
	destRect.h = (int)abs(scale.y);

	//destRect.w = (int)abs(scale.x);
	//destRect.h = (int)abs(scale.y);

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	//SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);

	SDL_RenderCopyEx(renderer, textureData, &srcRect, &destRect, 0.0, NULL, flipType);

}




void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale, Vec2 spritePos, Vec2 spriteDimensions, float angle)
{
	//Create the destination rectangle of the texture
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)abs(scale.x);
	destRect.h = (int)abs(scale.y);

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	//SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);

	SDL_RenderCopyEx(renderer, textureData, &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);

}





/*
void Texture::pushSpriteToScreen(SDL_Renderer* renderer, Vec2 pos, Vec2 scale, double angle, SDL_Point *centre, Vec2 spritePos, Vec2 spriteDimensions)
{
	//Create the destination rectangle of the texture
	SDL_RendererFlip flipType;
	if (scale.x < 0)
	{
		flipType = SDL_FLIP_HORIZONTAL;
	}
	else {
		flipType = SDL_FLIP_NONE;
	}

	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (unsigned int)scale.x;
	destRect.h = (unsigned int)scale.y;

	//Create the source rectangle of the texture
	SDL_Rect srcRect;
	srcRect.x = (int)spritePos.x;
	srcRect.y = (int)spritePos.y;
	srcRect.w = (int)spriteDimensions.x;
	srcRect.h = (int)spriteDimensions.y;

	//Copy the texture to the renderer at the destination rectangle
	//SDL_RenderCopy(renderer, textureData, &srcRect, &destRect);

	SDL_RenderCopyEx(renderer, textureData, &srcRect, &destRect, 0.0, NULL, flipType);

}*/


void Texture::renderText(SDL_Renderer* renderer, Vec2 pos, Vec2 scale) {
	SDL_Rect destRect;
	destRect.x = (int)pos.x;
	destRect.y = (int)pos.y;
	destRect.w = (int)dimensions.x * (int)scale.x;
	destRect.h = (int)dimensions.y * (int)scale.y;

	SDL_RenderCopy(renderer, textureData, NULL, &destRect);
}

void Texture::setColourTint(SDL_Colour colour)
{
	SDL_SetTextureColorMod(textureData, colour.r, colour.g, colour.b);
}