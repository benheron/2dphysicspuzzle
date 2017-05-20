#pragma once
#include "../Entity.h"

class ActivatableItem : public Entity
{
public:
	ActivatableItem(Texture *texture, Vec2 pos, Vec2 dimens, bool activated);
	~ActivatableItem();



	void setActivated(bool a);
	bool getActivated();
protected:

	bool activated;
};