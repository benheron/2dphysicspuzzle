#include "Bullet.h"

Bullet::Bullet(Texture* texture, Vec2 pos, Vec2 dimensions) : Entity(texture, pos, dimensions)
{
	gravityOn = false;
}

Bullet::Bullet(Vec2 pos, Vec2 dimensions) : Entity(pos, dimensions)
{
	gravityOn = false;
}

Bullet::~Bullet()
{

}


void Bullet::update(float dt)
{

}

void Bullet::render(SDL_Renderer* renderer)
{

}


int Bullet::getDamageValue()
{
	return damageValue;
}