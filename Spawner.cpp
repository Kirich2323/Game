#include"Spawner.h"
#include"Character.h"
#include"Fireball.h"
#include"Object.h"

void Spawner::Act(Map & map)
{
	if (--cooldown == 0)
	{
		cooldown = max_cooldown;
		Spawn(map);
	}
}

void Spawner::Collide(Map & map, Fireball * target)
{
	map.GetMap()[target->position().second][target->position().first] = new Emptiness(target->position().first, target->position().second);
	delete target;
}

bool Spawner::PathExist(Map & map, std::pair<int, int> pos)
{
	return pos.second >= 0 &&
		   pos.first >= 0 &&
		   pos.second < map.GetMap().size() &&
		   pos.first < map.GetMap()[pos.second].size() &&
		   (map.GetMap()[pos.second][pos.first]->Symbol() == EMPTINESS_SYMBOL);
}


void Cemetery::Spawn(Map & map)
{
	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		std::pair<int, int> new_pos = pos + ways[(i + offset) % 4];
		if (PathExist(map, new_pos) && map.GetMap()[new_pos.second][new_pos.first] != map.GetPlayer())
		{
			map.SetActed(pos);
			delete map.GetMap()[new_pos.second][new_pos.first];
			map.GetMap()[new_pos.second][new_pos.first] = new Zombie(ZOMBIE_HP, new_pos.first, new_pos.second);
			map.SetActed(new_pos);
			break;
		}
	}
}

void DragonNest::Spawn(Map & map)
{
	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		std::pair<int, int> new_pos = pos + ways[(i + offset) % 4];
		if (PathExist(map, new_pos) && map.GetMap()[new_pos.second][new_pos.first] != map.GetPlayer())
		{
			map.SetActed(pos);
			delete map.GetMap()[new_pos.second][new_pos.first];
			map.GetMap()[new_pos.second][new_pos.first] = new Dragon(DRAGON_HP, new_pos.first, new_pos.second);
			map.SetActed(new_pos);
			break;
		}
	}
}
