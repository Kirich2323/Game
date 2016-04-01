#include "Item.h"
#include"Fireball.h"
#include"Object.h"

void Item::Collide(Map & map, Fireball * target)
{
	map.Insert(new Emptiness(pos.x, pos.y));
	pos = target->position();
	map.Erase(target->position());
	map.Insert(new Emptiness(pos.x, pos.y));
	delete this;
}
