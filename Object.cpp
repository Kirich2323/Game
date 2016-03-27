#include"Object.h"
#include"Actor.h"
#include"Character.h"
#include"Fireball.h"

void Emptiness::Collide(Map & map, Fireball * target)
{
	target->replace(pos, map);
}

void Wall::Collide(Map & map, Fireball * target)
{
	map.GetMap()[target->position().second][target->position().first] = new Emptiness(target->position().first, target->position().second);
	delete target;
}
