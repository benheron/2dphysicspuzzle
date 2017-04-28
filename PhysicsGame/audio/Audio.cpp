#include "Audio.h"

Audio::Audio(std::string filePath, int type)
{
	if (type == 0)
	{
		loadMusic(filePath);
	}
	else {
		loadSoundEffect(filePath);
	}

	this->type = type;
	
	int d = 0;
}

Audio::~Audio()
{
	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}
	if (sfx != NULL)
	{
		Mix_FreeChunk(sfx);
	}
}

bool Audio::loadMusic(std::string filePath)
{
	music = Mix_LoadMUS(filePath.c_str());

	
	if (music == NULL)
	{
		//fail
		Utility::log(Utility::W, "Problem trying to load sound.");
		return false;
	}

	return true;

}

bool Audio::loadSoundEffect(std::string filePath)
{
	sfx = Mix_LoadWAV(filePath.c_str());

	int i = 0;

	if (sfx == NULL)
	{
		return false;
	}

	return true;
}

void Audio::playAudio(int loops)
{
	if (type == 0)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			if (Mix_PlayMusic(music, loops) == -1)
			{
				Utility::log(Utility::W, "Problem trying to play sound.");
			}
		}
	}
	else if (type == 1)
	{
		if (Mix_PlayChannel(-1, sfx, loops) == -1)
		{
			Utility::log(Utility::W, "Problem trying to play sound.");
		}
	}
	
}

void Audio::stopAudio()
{
	Mix_HaltMusic();
}