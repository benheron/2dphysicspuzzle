#include "Frame.h"

Frame::Frame(Texture* spritesheet, Vec2 framePos, Vec2 frameDimens) : spritesheet(spritesheet), framePos(framePos), frameDimens(frameDimens)
{

}

Frame::~Frame()
{

}

Vec2 Frame::getFramePos()
{
	return framePos;
}

Vec2 Frame::getFrameDimens()
{
	return frameDimens;
}