#pragma once
#include <iostream>
#include "../dependencies/SDL_mixer.h"
#include <SDL_mixer.h>
#include "../Utility.h"

class Audio
{
public:
	Audio(std::string filePath, int type);
	~Audio();

	void playAudio(int loops);

	void stopAudio();

	bool loadMusic(std::string filePath);

	bool loadSoundEffect(std::string filePath);


protected:
	Mix_Music *music;
	Mix_Chunk *sfx;

	int type;
};