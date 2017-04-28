#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Vec2 pos, Vec2 dimensions);
	Bullet(Texture* texture, Vec2 pos, Vec2 dimensions);
	~Bullet();

	void setDamageValue();
	int getDamageValue();

protected:

	void update(float dt);
	void render(SDL_Renderer* renderer);

	int damageValue;
	float speed;
	Vec2 direction;

};