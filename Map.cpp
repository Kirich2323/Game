#include"Map.h"
#include"Actor.h"
#include"Character.h"
#include"Item.h"
#include"Object.h"

Map::Map()
{
	actors.resize(1);
	actors[0].resize(1);
}

Map::Map(std::vector<std::vector<char>>& map_)
{
	actors.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		actors[i].resize(map_[i].size(), nullptr);
		for (int j = 0; j < map_[i].size(); j++)
		{
			switch (map_[i][j]) {
			case KNIGHT_SYMBOL: {
				if (player == nullptr)
					AddPlayer(new Knight(100, j, i));
				else
					throw(std::runtime_error("Too many knights"));
				break;
			}
			case PRINCESS_SYMBOL:
			{
				if (princess == nullptr)
					AddPrincess(new Princess(100, j, i));
				else
					throw(std::runtime_error("Too many princesses"));
				break;
			}
			case ZOMBIE_SYMBOL: AddActor(new Zombie(10, j, i));
				break;
			case DRAGON_SYMBOL: AddActor(new Dragon(50, j, i));
				break;
			case MEDKIT_SYMBOL: AddActor(new Medkit(j, i));
				break;
			case WALL_SYMBOL: AddActor(new Wall(j, i));
				break;
			case EMPTINESS_SYMBOL: AddActor(new Emptiness(j, i));
				break;
			case WIZARD_SYMBOL: AddActor(new Wizard(15, j, i));
			}
		}
	}

	if (princess == nullptr)
		throw(std::runtime_error("No princess found"));

	if (player == nullptr)
		throw(std::runtime_error("No knight found"));

	visited.resize(map_.size());
	paths.resize(map_.size());
	acted.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		visited[i].resize(map_[i].size());
		paths[i].resize(map_[i].size());
		acted[i].resize(map_[i].size());
	}
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
	actors[c->position().second][c->position().first] = c;
}

Map::Map(const Map &map_)
{
	actors = map_.actors;
	visited = map_.visited;
	paths = map_.paths;
}

void Map::Display()
{
	if (actors[princess->position().second][princess->position().first]->Symbol() == EMPTINESS_SYMBOL)
	{
		delete actors[princess->position().second][princess->position().first];
		actors[princess->position().second][princess->position().first] = princess;
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

std::vector<std::vector<std::pair<int, int>>>& Map::GetPaths()
{
	return paths;
}

std::vector<std::vector<bool>>& Map::GetVisited()
{
	return visited;
}

void Map::SetActed(std::pair<int, int>& pos)
{
	acted[pos.second][pos.first] = true;
}

void Map::ClearActed()
{
	for (int i = 0; i < acted.size(); i++)
	{
		for (int j = 0; j < acted[i].size(); j++)
			acted[i][j] = false;
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
