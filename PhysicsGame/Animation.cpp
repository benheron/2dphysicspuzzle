#include "Animation.h"
Animation::Animation(std::string name, int numFrames, std::vector<Frame*> frames) : name(name), numFrames(numFrames), frames(frames)
{

}

Animation::~Animation()
{

}

Frame* Animation::getFrame(int index)
{
	return frames[index];
}

int Animation::getNumFrames()
{
	return numFrames;
}

void Animation::pauseAnimation() {

}

void Animation::playAnimation()
{

}

void Animation::setFrameRate(int fr)
{
	frameRate = fr;
}

int Animation::getFrameRate()
{
	return frameRate;
}

