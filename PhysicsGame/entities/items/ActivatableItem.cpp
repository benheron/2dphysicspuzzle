#include "ActivatableItem.h"

ActivatableItem::ActivatableItem(Texture *texture, Vec2 pos, Vec2 dimens, bool activated) : Entity(texture, pos, dimens), activated(activated)
{

}


ActivatableItem::~ActivatableItem()
{

}

void ActivatableItem::setActivated(bool a)
{
	activated = a;
}

bool ActivatableItem::getActivated()
{
	return activated;
}