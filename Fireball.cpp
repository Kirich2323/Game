#include"Fireball.h"
#include"Character.h"
#include"Object.h"

void Fireball::Collide(Map & map, Character* target)
{
	target->TakeDamage(damage);
	map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
	delete this; //???
}

void Fireball::Act(Map & map)
{
	std::pair<int, int> new_pos = pos + direction;
	if (PathExist(map, new_pos))
		Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
	else
	{
		map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
		delete this;
	}
}

bool Fireball::PathExist(Map & map, std::pair<int, int> pos)
{
	return pos.second >= 0 && pos.first >= 0 && pos.second < map.GetMap().size() && pos.first < map.GetMap()[pos.second].size();
}
