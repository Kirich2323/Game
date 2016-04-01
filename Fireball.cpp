#include"Fireball.h"
#include"Character.h"
#include"Object.h"

void Fireball::Collide(Map & map, Fireball * target)
{
	map.Insert(new Emptiness(target->position().x, target->position().y), target->position());
	delete target;
	map.Insert(new Emptiness(pos.x, pos.y), pos);
	delete this;
}

void Fireball::Collide(Map & map, Character* target)
{
	target->TakeDamage(damage);
	map.GetMap()[pos.y][pos.x] = new Emptiness(pos.x, pos.y);
	delete this;
}

void Fireball::Act(Map & map)
{
	vec2i new_pos = pos + direction;
	if (map.PathExist(new_pos))
		Collide(map, map.GetMap()[new_pos.y][new_pos.x]);
	else
	{
		map.GetMap()[pos.y][pos.x] = new Emptiness(pos.x, pos.y);
		delete this;
	}
}

