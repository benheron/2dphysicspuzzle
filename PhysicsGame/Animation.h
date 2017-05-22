#pragma once
#include <string>
#include "Vec2.h"
#include <vector>
#include "Frame.h"
#include "Texture.h"

class Animation {
public:
	Animation(std::string name, int numFrames, std::vector<Frame*> frames);
	~Animation();

	
	Frame* getFrame(int index);
	int getNumFrames();

	void setFrameRate(int fr);
	int getFrameRate();


	void pauseAnimation();
	void playAnimation();

protected:
	std::string name;
	int numFrames;
	std::vector<Frame*> frames;

	int frameRate;
};