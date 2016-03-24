#include"Character.h"

bool Character::PathExist(Map &map, std::pair<int, int> target)
{
	return (target.second >= 0 &&
			target.first >= 0 &&
			target.second < map.GetMap().size() &&
			target.first < map.GetMap()[target.second].size() &&
			map.GetMap()[target.second][target.first] != '#');
}

std::pair<int, int> Knight::Move(Map &map)
{
	char direction;
	std::cin >> direction;

	if (directions.find(direction) == directions.end())
		return pos;

	std::pair<int, int> new_pos = pos + directions[direction];

	if (PathExist(map, new_pos))
	{
		return new_pos;
	}
	return pos;
}

int Knight::HitPoint()
{
	return hitpoints;
}

int Knight::Damage()
{
	return 10;
}

void Knight::Collide(Princess * target)
{
	pos = target->position();
}

void Knight::Collide(Monster * target)
{
	target->TakeDamage(Damage());
	if (target->HitPoint() <= 0)
	{
		pos = target->position();
	}
}

std::pair<int, int> Princess::Move(Map &map)
{
	return pos;
}

int Princess::HitPoint()
{
	return hitpoints;
}

int Princess::Damage()
{
	return 0;
}

std::pair<int, int> Monster::Move(Map &map)
{
	//BFS
	std::pair<int, int> next_position = SearchForPath(map);
	if (next_position != std::pair<int, int>(-1, -1))
	{
		return next_position;
	}

	//Just random moving
	/*int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		if (PathExist(map, pos + ways[(i + offset) % ways.size()]))
		{
			return pos + ways[(i + offset) % ways.size()];
		}
	}*/
	return pos;
}

void Monster::Collide(Knight * target)
{
	target->TakeDamage(Damage());
}

std::pair<int, int>& Monster::SearchForPath(Map &map)
{
	std::pair<int, int> next_point = std::pair<int, int>(-1, -1);
	std::pair<int, int> target = SearchForKnight(map);

	if (target == std::pair<int, int>(-1, -1))
		return target;

	std::pair<int, int> new_pos;
	std::pair<int, int> current_loc;

	map.ClearVisited();

	std::list<std::pair<int, int>> queue;
	queue.push_back(pos);

	while (!queue.empty())
	{
		current_loc = *queue.begin();
		queue.pop_front();

		if (current_loc == target)
			break;
		
		int offset = rand() % ways.size();
		for (int i = 0; i < ways.size(); i++)
		{
			new_pos = current_loc + ways[(i + offset) % 4];
			if (PathExist(map, new_pos) && map.GetVisited()[new_pos.second][new_pos.first] == false)
			{
				queue.push_back(new_pos);
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
			if (PathExist(map, new_pos) && visited[new_pos.second][new_pos.first] == true)
				return new_pos;
		}*/
	}
	return next_point;
}

std::pair<int, int> Monster::SearchForKnight(Map & map)
{
	for (int i = 0; i < map.GetMap().size(); i++)
		for (int j = 0; j < map.GetMap()[i].size(); j++)
			if (map.GetMap()[i][j] == KNIGHT_SYMBOL)
				return std::pair<int, int>(j, i);

	return std::pair<int, int>(-1, -1);
}

bool Monster::PathExist(Map &map, std::pair<int, int> target)
{
	if (Character::PathExist(map, target))
		if (monsters.find(map.GetMap()[target.second][target.first]) == monsters.end())
			return true;

	return false;
}

int Zombie::HitPoint()
{
	return hitpoints;
}

int Zombie::Damage()
{
	return 5;
}

int Dragon::HitPoint()
{
	return hitpoints;
}

int Dragon::Damage()
{
	return 7;
}