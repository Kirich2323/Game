#include"Map.h"
#include"Actor.h"
#include"Character.h"
#include"Item.h"
#include"Object.h"
#include"Spawner.h"
#include<queue>
#include"RemoteSpawner.h"
//#include"Cfg.h"


Map::Map()
{
	actors.resize(1);
	actors[0].resize(1);
	remote_spawners.push_back(new MedkitSpawner());
}

Map::Map(std::vector<std::vector<char>>& map_)
{
	funcs[Cfg::GetInstance().get_knight_symbol()] = &Map::CreateKnight;
	funcs[Cfg::GetInstance().get_princess_symbol()] = &Map::CreatePrincess;
	funcs[Cfg::GetInstance().get_zombie_symbol()] = &Map::CreateZombie;
	funcs[Cfg::GetInstance().get_dragon_symbol()] = &Map::CreateDragon;
	funcs[Cfg::GetInstance().get_cemetery_symbol()] = &Map::CreateCemetery;
	funcs[Cfg::GetInstance().get_dragon_nest_symbol()] = &Map::CreateDragonNest;
	funcs[Cfg::GetInstance().get_wizard_symbol()] = &Map::CreateWizard;
	funcs[Cfg::GetInstance().get_wall_symbol()] = &Map::CreateWall;
	funcs[Cfg::GetInstance().get_emptiness_symbol()] = &Map::CreateEmptiness;
	funcs[Cfg::GetInstance().get_medkit_symbol()] = &Map::CreateMedkit;

	actors.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		actors[i].resize(map_[i].size(), nullptr);
		for (int j = 0; j < map_[i].size(); j++)
		{
			auto it = funcs.find(map_[i][j]);
			if (it != funcs.end())
				(this->*(it->second))(vec2i(j, i));
		}
	}

	if (princess == nullptr)
		throw(std::runtime_error("No princess found"));

	if (player == nullptr)
		throw(std::runtime_error("No knight found"));

	visited.resize(map_.size());
	paths.resize(map_.size());
	acted.resize(map_.size());
	distances.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		visited[i].resize(map_[i].size());
		paths[i].resize(map_[i].size());
		acted[i].resize(map_[i].size());
		distances[i].resize((map_[i].size()));
	}

	remote_spawners.push_back(new MedkitSpawner());
}

void Map::AddPlayer(Actor* c)
{
	player = c;
	AddActor(c);
}

void Map::AddPrincess(Actor* c)
{
	princess = c;
	AddActor(c);
}

void Map::AddActor(Actor* c)
{
	actors[c->position().y][c->position().x] = c;
}

void Map::CreateKnight(vec2i pos)
{
	if (player == nullptr)
		AddPlayer(new Knight(Cfg::GetInstance().get_knight_hp(), pos.x, pos.y));
	else
		throw(std::runtime_error("Too many knights"));
}

void Map::CreatePrincess(vec2i pos)
{
	if (princess == nullptr)
		AddPrincess(new Princess(Cfg::GetInstance().get_princess_hp(), pos.x, pos.y));
	else
		throw(std::runtime_error("Too many princesses"));
}

void Map::CreateZombie(vec2i pos)
{
	AddActor(new Zombie(Cfg::GetInstance().get_zombie_hp(), pos.x, pos.y));
}

void Map::CreateDragon(vec2i pos)
{
	AddActor(new Dragon(Cfg::GetInstance().get_dragon_hp(), pos.x, pos.y));
}

void Map::CreateCemetery(vec2i pos)
{
	AddActor(new Cemetery(pos.x, pos.y, Cfg::GetInstance().get_cemetery_symbol()));
}

void Map::CreateDragonNest(vec2i pos)
{
	AddActor(new DragonNest(pos.x, pos.y, Cfg::GetInstance().get_dragon_nest_cooldown()));
}

void Map::CreateWizard(vec2i pos)
{
	AddActor(new Wizard(Cfg::GetInstance().get_wizard_hp(), pos.x, pos.y));
}

void Map::CreateEmptiness(vec2i pos)
{
	AddActor(new Emptiness(pos.x, pos.y));
}

void Map::CreateWall(vec2i pos)
{
	AddActor(new Wall(pos.x, pos.y));
}

void Map::CreateMedkit(vec2i pos)
{
	AddActor(new Medkit(pos.x, pos.y));
}

Map::Map(const Map &map_)
{
	actors = map_.actors;
	visited = map_.visited;
	paths = map_.paths;
}

void Map::Display()
{
	if (actors[princess->position().y][princess->position().x]->Symbol() == Cfg::GetInstance().get_emptiness_symbol())
	{
		delete actors[princess->position().y][princess->position().x];
		actors[princess->position().y][princess->position().x] = princess;
	}

	for (int i = 0; i < actors.size(); i++)
	{
		for (int j = 0; j < actors[i].size(); j++)
				printf("%c", actors[i][j]->Symbol());

		printf("\n");
	}
}

std::vector<std::vector<Actor*>>& Map::GetMap()
{
	return actors;
}

std::vector<std::vector<Actor*>> Map::GetBufMap()
{
	return actors;
}

std::vector<std::vector<vec2i>>& Map::GetPaths()
{
	return paths;
}

std::vector<std::vector<bool>>& Map::GetVisited()
{
	return visited;
}

void Map::SetActed(vec2i& pos)
{
	acted[pos.y][pos.x] = true;
}

void Map::ClearActed()
{
	for (int i = 0; i < acted.size(); i++)
	{
		for (int j = 0; j < acted[i].size(); j++)
			acted[i][j] = false;
	}
}

void Map::UpdateDistances()
{
	ClearVisited();

	std::queue< std::pair< vec2i, int> > queue;
	queue.push(std::pair< vec2i, int>(player->position(), 0));

	visited[player->position().y][player->position().x] = true;

	while (!queue.empty())
	{
		vec2i pos_ = queue.front().first;
		int dist = queue.front().second;
		distances[pos_.y][pos_.x] = dist;
		queue.pop();

		for (int i = 0; i < ways.size(); i++)
		{
			vec2i new_pos = pos_ + ways[i];
			if (PathExist(new_pos) && actors[new_pos.y][new_pos.x]->Symbol() != Cfg::GetInstance().get_wall_symbol() && visited[new_pos.y][new_pos.x] == false)
			{
				queue.push(std::pair< vec2i, int>(new_pos, dist + 1));
				visited[new_pos.y][new_pos.x] = true;
			}
		}
	}
}

std::vector<std::vector<bool>>& Map::GetActed()
{
	return acted;
}

void Map::ClearVisited()
{
	for (int i = 0; i < visited.size(); i++)
		for (int j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
}

bool Map::PathExist(vec2i pos)
{
	return pos.y >= 0 && pos.x >= 0 && pos.y < actors.size() && pos.x < actors[pos.y].size();
}

void Map::Erase(vec2i pos)
{
	delete actors[pos.y][pos.x];
}

void Map::Insert(Actor* actor)
{
	actors[actor->position().y][actor->position().x] = actor;
}
