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
	map.GetMap()[target->position().y][target->position().x] = new Emptiness(target->position().x, target->position().y);
	delete target;
}
