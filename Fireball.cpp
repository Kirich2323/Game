#include"Fireball.h"
#include"Character.h"
#include"Object.h"

void Fireball::Collide(Map & map, Fireball * target)
{
	map.Insert(new Emptiness(target->position().first, target->position().second), target->position());
	delete target;
	map.Insert(new Emptiness(pos.first, pos.second), pos);
	delete this;
}

void Fireball::Collide(Map & map, Character* target)
{
	target->TakeDamage(damage);
	map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
	delete this;
}

void Fireball::Act(Map & map)
{
	std::pair<int, int> new_pos = pos + direction;
	if (map.PathExist(new_pos))
		Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
	else
	{
		map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
		delete this;
	}
}

