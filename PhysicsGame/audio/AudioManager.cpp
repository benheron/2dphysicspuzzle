#include "AudioManager.h"

AudioManager::AudioManager(std::string filePath)
{
	loadAudio(filePath);
}

AudioManager::~AudioManager()
{

}

bool AudioManager::loadAudio(std::string filePath)
{
	Utility::log(Utility::I, "Loading all audio list data : " + filePath);

	std::ifstream audioList(filePath);

	if (audioList.is_open())
	{
		for (int i = 0; i < 2; i++)
		{
			int numItems;

			audioList >> numItems;

			for (int j = 0; j< numItems; j++)
			{
				std::string id;
				std::string name;
				std::string audioFileTxt;

				audioList >> id;
				audioList >> name;
				audioList >> audioFileTxt;

				Utility::log(Utility::I, "Loading audio data : " + audioFileTxt);
				//std::ifstream audioFile(audioFileTxt);

				Audio *a = new Audio(audioFileTxt, i);

				if (i == 0)
				{
					bgMusicID[id] = a;
					bgMusicString[name] = a;

					bgMusicList.push_back(a);
				}
				else if (i == 1)
				{
					soundEffectsID[id] = a;
					soundEffectsString[name] = a;

					soundEffectsList.push_back(a);
				}

				


			}
		}
		
		audioList.close();
	}
	else {
		//failed
		Utility::log(Utility::I, "Failed to load audio data list: " + filePath);
		return false;
	}
	return true;
}


Audio* AudioManager::getSFXByID(std::string id)
{
	return soundEffectsID[id];
}

Audio* AudioManager::getSFXByName(std::string name)
{
	return soundEffectsString[name];
}

Audio* AudioManager::getSFXByIndex(int i)
{
	return soundEffectsList[i];
}

Audio* AudioManager::getMusicByID(std::string id)
{
	return bgMusicID[id];
}

Audio* AudioManager::getMusicByName(std::string name)
{
	return bgMusicString[name];
}

Audio* AudioManager::getMusicByIndex(int i)
{
	return bgMusicList[i];
}

