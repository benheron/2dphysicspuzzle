#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "Vec2.h"

class Frame {
public:
	Frame(Texture* spritesheet, Vec2 framePos, Vec2 frameDimens);
	~Frame();


	Vec2 getFramePos();
	Vec2 getFrameDimens();

protected:
	Texture* spritesheet;
	Vec2 framePos;
	Vec2 frameDimens;

};