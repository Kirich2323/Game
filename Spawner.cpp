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
	map.GetMap()[target->position().y][target->position().x] = new Emptiness(target->position().x, target->position().y);
	delete target;
}

bool Spawner::PathExist(Map & map, vec2i pos)
{
	return pos.y >= 0 &&
		   pos.x >= 0 &&
		   pos.y < map.GetMap().size() &&
		   pos.x < map.GetMap()[pos.y].size() &&
		   (map.GetMap()[pos.y][pos.x]->Symbol() == Cfg::GetInstance().get_emptiness_symbol());
}


void Cemetery::Spawn(Map & map)
{
	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		vec2i new_pos = pos + ways[(i + offset) % 4];
		if (PathExist(map, new_pos) && map.GetMap()[new_pos.y][new_pos.x] != map.GetPlayer())
		{
			map.SetActed(pos);
			delete map.GetMap()[new_pos.y][new_pos.x];
			map.GetMap()[new_pos.y][new_pos.x] = new Zombie(Cfg::GetInstance().get_zombie_hp(), new_pos.x, new_pos.y);
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
		vec2i new_pos = pos + ways[(i + offset) % 4];
		if (PathExist(map, new_pos) && map.GetMap()[new_pos.y][new_pos.x] != map.GetPlayer())
		{
			map.SetActed(pos);
			delete map.GetMap()[new_pos.y][new_pos.x];
			map.GetMap()[new_pos.y][new_pos.x] = new Dragon(Cfg::GetInstance().get_dragon_hp(), new_pos.x, new_pos.y);
			map.SetActed(new_pos);
			break;
		}
	}
}
