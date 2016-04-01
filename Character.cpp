#include"Character.h"
#include"Object.h"
#include<conio.h>
#include<queue>
#include"Fireball.h"
#include"RemoteSpawner.h"

void Character::Heal(int amount)
{
	hitpoints += amount;
	if (hitpoints > max_hp)
		hitpoints = max_hp;
}

void Character::Collide(Map & map, Fireball * target)
{
	map.Insert(new Emptiness(target->position().x, target->position().y));
	hitpoints -= target->GetDamage();
	delete target;
}

bool Character::PathExist(Map & map, vec2i& target)
{
	return (map.PathExist(target) && map.GetMap()[target.y][target.x]->Symbol() != WALL_SYMBOL);
}

void Knight::Move(Map& map)
{
	char direction = _getch();
	
	if (directions.find(direction) == directions.end())
		return;

	vec2i new_pos = pos + directions[direction];
	if (PathExist(map, new_pos))
		Collide(map, map.GetMap()[new_pos.y][new_pos.x]);
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
	/*vec2i next_position = SearchForPath(map);
	if (next_position != vec2i(-1, -1))
		Collide(map, map.GetMap()[next_position.y][next_position.x]);*/

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
		vec2i new_pos = pos + ways[(i + offset) % ways.size()];
		if (Character::PathExist(map, new_pos) && map.GetDistances()[pos.y][pos.x] > map.GetDistances()[new_pos.y][new_pos.x])
		{
			if (monsters.find(map.GetMap()[new_pos.y][new_pos.x]->Symbol()) == monsters.end() )
				return Collide(map, map.GetMap()[new_pos.y][new_pos.x]);
			else
				for (int j = 0; j < ways.size(); j++)
				{
					new_pos = pos + ways[i];
					if (PathExist(map, new_pos))
						return Collide(map, map.GetMap()[new_pos.y][new_pos.x]);
				}
		}
	}
}

void Monster::Collide(Map& map, Knight * target)
{
	target->TakeDamage(Damage());
}

void Monster::Collide(Map & map, Princess * target)
{
	map.Insert(new Emptiness(pos.x, pos.y));
	map.SetActed(pos);
	pos = target->position();
	map.SetActed(pos);
	map.Insert(this);
}

vec2i& Monster::SearchForPath(Map &map)
{
	vec2i next_point = vec2i(-1, -1);
	vec2i target = map.GetPlayer()->position();

	if (target == vec2i(-1, -1))
		return target;

	vec2i new_pos;
	vec2i current_loc;

	map.ClearVisited();

	std::queue<vec2i> queue;
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
			if (PathExist(map, new_pos) && map.GetVisited()[new_pos.y][new_pos.x] == false)
			{
				queue.push(new_pos);
				map.GetPaths()[new_pos.y][new_pos.x] = current_loc;
				map.GetVisited()[new_pos.y][new_pos.x] = true;
			}
		}
	}

	if (map.GetVisited()[target.y][target.x] == true)
	{
		while (target != pos)
		{
			next_point = target;
			target = map.GetPaths()[target.y][target.x];
		}
	}
	else
	{
		//Random moving
		/*int offset = rand() % ways.size();
		for (int i = 0; i < ways.size(); i++)
		{
			new_pos = ways[(i + offset) % 4] + pos;
			if (PathExist(map, new_pos) && visited[new_pos.y][new_pos.x])
			{
				return new_pos;
			}
		}*/
	}
	return next_point;
}

bool Monster::PathExist(Map &map, vec2i& target)
{
	if (Character::PathExist(map, target))
		if (monsters.find(map.GetMap()[target.y][target.x]->Symbol()) == monsters.end())
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
		vec2i dir = ways[(i + offset) % 4];
		vec2i new_pos = dir + pos;
		
		if (PathExist(map, new_pos) && map.GetMap()[new_pos.y][new_pos.x]->Symbol() == EMPTINESS_SYMBOL)
		{
			map.SetActed(new_pos);
			delete map.GetMap()[new_pos.y][new_pos.x];
			map.GetMap()[new_pos.y][new_pos.x] = new Fireball(fireball_damage, dir, new_pos.x, new_pos.y);
			return;
		}
	}
}

void Wizard::Move(Map & map)
{
	int offset = rand() % ways.size();
	for (int i = 0; i < ways.size(); i++)
	{
		vec2i new_pos = pos + ways[(i + offset) % ways.size()];
		if (PathExist(map, new_pos))
		{
			Collide(map, map.GetMap()[new_pos.y][new_pos.x]);
			break;
		}
	}
}
