#include "MapExit.h"


MapExit::MapExit(Texture* texture, Vec2 pos) : Entity(texture, pos)
{


}

MapExit::MapExit(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	spritePos = 0;
}


MapExit::MapExit(Texture* texture, Vec2 pos, Vec2 dimensions, Vec2 spritePos) : Entity(texture, pos, dimensions, spritePos)
{

}

MapExit::~MapExit()
{

}

void MapExit::buildMapExit()
{

}

void MapExit::update(float dt)
{



}


void MapExit::render(SDL_Renderer *renderer)
{
	texture->pushToScreen(renderer, pos, dimensions);
}


bool MapExit::getOpen()
{
	return opened;
}

void MapExit::setOpen(bool o)
{
	opened = o;
}