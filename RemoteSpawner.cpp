#include"RemoteSpawner.h"
#include"Map.h"
#include<time.h>
#include<queue>
#include"Item.h"

vec2i RemoteSpawner::SeekCell(Map & map, vec2i pos)
{
	std::queue<vec2i> queue;
	queue.push(pos);
	map.ClearVisited();

	while (!queue.empty())
	{
		vec2i current_loc = queue.front();
		queue.pop();

		if (map.GetMap()[current_loc.y][current_loc.x]->Symbol() == Cfg::GetInstance().get_emptiness_symbol())
			return current_loc;

		int offset = rand() % ways.size();
		for (int i = 0; i < ways.size(); i++)
		{
			vec2i new_pos = current_loc + ways[(i + offset) % 4];
			if (map.PathExist(new_pos) && map.GetVisited()[new_pos.y][new_pos.x] == false)
			{
				queue.push(new_pos);
				map.GetVisited()[new_pos.y][new_pos.x] = true;
			}
		}
	}
	return vec2i(-1, -1);
}

void RemoteSpawner::Swap(const int& left, const int& right)
{
	vec2i tmp = children_position[left];
	children_position[left] = children_position[right];
	children_position[right] = tmp;
}


void MedkitSpawner::Act(Map & map)
{
	if (--cooldown == 0)
	{
		cooldown = max_cooldown;
		for (int i = 0; i < children_position.size(); i++)
		{
			if (map.GetMap()[children_position[i].y][children_position[i].x]->Symbol() != Cfg::GetInstance().get_medkit_symbol())
			{
				Swap(i, children_position.size() - 1);
				children_position.resize(children_position.size() - 1);
			}
		}

		if (children_position.size() < Cfg::GetInstance().get_medkit_max_count())
		{
			Spawn(map);
		}
	}
}

void MedkitSpawner::Spawn(Map & map)
{
	srand(time(0));
	int y = rand() % map.GetMap().size();
	int x = rand() % map.GetMap()[y].size();
	vec2i target = SeekCell(map, vec2i(x, y));
	if (target != vec2i(-1, -1))
	{
		delete map.GetMap()[target.y][target.x];
		map.GetMap()[target.y][target.x] = new Medkit(target.x, target.y);
		children_position.push_back(target);
	}
}