#include"Character.h"
#include"Object.h"
#include<conio.h>
#include<queue>
#include"Fireball.h"

void Character::Heal(int amount)
{
	hitpoints += amount;
	if (hitpoints > max_hp)
		hitpoints = max_hp;
}

void Character::Collide(Map & map, Fireball * target)
{
	map.GetMap()[target->position().second][target->position().first] = new Emptiness(target->position().first, target->position().second);
	hitpoints -= target->GetDamage();
	delete target;
}

bool Character::PathExist(Map & map, std::pair<int, int>& target)
{
	return (target.second >= 0 &&
			target.first >= 0 &&
			target.second < map.GetMap().size() &&
			target.first < map.GetMap()[target.second].size() &&
			map.GetMap()[target.second][target.first]->Symbol() != WALL_SYMBOL);
}

void Knight::Move(Map& map)
{
	char direction = _getch();
	
	if (directions.find(direction) == directions.end())
		return;

	std::pair<int, int> new_pos = pos + directions[direction];
	if (PathExist(map, new_pos))
		Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
}

void Knight::Collide(Map& map, Monster * target)
{
	target->TakeDamage(Damage());
	if (target->HitPoint() <= 0)
		replace(target->position(), map);
}

void Knight::Collide(Map & map, Princess * target)
{
	map.SetActed(pos);
	pos = target->position();
	map.SetActed(pos);
}

void Monster::Move(Map &map)
{
	//BFS
	/*std::pair<int, int> next_position = SearchForPath(map);
	if (next_position != std::pair<int, int>(-1, -1))
		Collide(map, map.GetMap()[next_position.second][next_position.first]);*/

	//Just random moving
	/*int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		if (PathExist(map, pos + ways[(i + offset) % ways.size()]))
		{
			//return pos + ways[(i + offset) % ways.size()];
		}
	}*/

	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		std::pair<int, int> new_pos = pos + ways[(i + offset) % ways.size()];
		if (Character::PathExist(map, new_pos) && map.GetDistances()[pos.second][pos.first] > map.GetDistances()[new_pos.second][new_pos.first])
			if (monsters.find(map.GetMap()[new_pos.second][new_pos.first]->Symbol()) == monsters.end())
				return Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
			else
				for (int j = 0; j < ways.size(); j++)
				{
					new_pos = pos + ways[i];
					if (PathExist(map, new_pos))
						return Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
				}
	}
}

void Monster::Collide(Map& map, Knight * target)
{
	target->TakeDamage(Damage());
}

void Monster::Collide(Map & map, Princess * target)
{
	map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
	map.SetActed(pos);
	pos = target->position();
	map.SetActed(pos);
	map.GetMap()[pos.second][pos.first] = this;
}

std::pair<int, int>& Monster::SearchForPath(Map &map)
{
	std::pair<int, int> next_point = std::pair<int, int>(-1, -1);
	std::pair<int, int> target = map.GetPlayer()->position();

	if (target == std::pair<int, int>(-1, -1))
		return target;

	std::pair<int, int> new_pos;
	std::pair<int, int> current_loc;

	map.ClearVisited();

	std::queue<std::pair<int, int>> queue;
	queue.push(pos);

	while (!queue.empty())
	{
		current_loc = queue.front();
		queue.pop();

		if (current_loc == target)
			break;
		
		int offset = rand() % ways.size();
		for (int i = 0; i < ways.size(); i++)
		{
			new_pos = current_loc + ways[(i + offset) % 4];
			if (PathExist(map, new_pos) && map.GetVisited()[new_pos.second][new_pos.first] == false)
			{
				queue.push(new_pos);
				map.GetPaths()[new_pos.second][new_pos.first] = current_loc;
				map.GetVisited()[new_pos.second][new_pos.first] = true;
			}
		}
	}

	if (map.GetVisited()[target.second][target.first] == true)
	{
		while (target != pos)
		{
			next_point = target;
			target = map.GetPaths()[target.second][target.first];
		}
	}
	else
	{
		//Random moving
		/*int offset = rand() % ways.size();
		for (int i = 0; i < ways.size(); i++)
		{
			new_pos = ways[(i + offset) % 4] + pos;
			if (PathExist(map, new_pos) && visited[new_pos.second][new_pos.first])
			{
				return new_pos;
			}
		}*/
	}
	return next_point;
}

bool Monster::PathExist(Map &map, std::pair<int, int>& target)
{
	if (Character::PathExist(map, target))
		if (monsters.find(map.GetMap()[target.second][target.first]->Symbol()) == monsters.end())
			return true;
	return false;
}

void Wizard::Act(Map& map)
{
	if (rand() % 4 == 0)
		LaunchFireball(map);
	else
		Monster::Act(map);
}

void Wizard::LaunchFireball(Map & map)
{
	map.SetActed(pos);
	int offset = rand();
	for (int i = 0; i < ways.size(); i++)
	{
		std::pair<int, int> dir = ways[(i + offset) % 4];
		std::pair<int, int> new_pos = dir + pos;
		
		if (PathExist(map, new_pos))
		{
			map.SetActed(new_pos);
			delete map.GetMap()[new_pos.second][new_pos.first];
			map.GetMap()[new_pos.second][new_pos.first] = new Fireball(fireball_damage, dir, new_pos.first, new_pos.second);
			return;
		}
	}
}

void Wizard::Move(Map & map)
{
	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		std::pair<int, int> new_pos = pos + ways[(i + offset) % ways.size()];
		if (PathExist(map, new_pos))
		{
			Collide(map, map.GetMap()[new_pos.second][new_pos.first]);
			break;
		}
	}
}
