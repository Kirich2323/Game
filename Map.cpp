#include"Map.h"
#include"Actor.h"
#include"Character.h"
#include"Item.h"
#include"Object.h"
#include"Spawner.h"
#include<queue>

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
					AddPlayer(new Knight(KNIGHT_HP, j, i));
				else
					throw(std::runtime_error("Too many knights"));
				break;
			}
			case PRINCESS_SYMBOL:
			{
				if (princess == nullptr)
					AddPrincess(new Princess(PRINCESS_HP, j, i));
				else
					throw(std::runtime_error("Too many princesses"));
				break;
			}
			case ZOMBIE_SYMBOL: AddActor(new Zombie(ZOMBIE_HP, j, i));
				break;
			case DRAGON_SYMBOL: AddActor(new Dragon(DRAGON_HP, j, i));
				break;
			case MEDKIT_SYMBOL: AddActor(new Medkit(j, i));
				break;
			case WALL_SYMBOL: AddActor(new Wall(j, i));
				break;
			case EMPTINESS_SYMBOL: AddActor(new Emptiness(j, i));
				break;
			case WIZARD_SYMBOL: AddActor(new Wizard(WIZARD_HP, j, i));
				break;
			case CEMETRY_SYMBOL: AddActor(new Cemetery(j, i, CEMETERY_COOLDOWN));
				break;
			case DRAGONNEST_SYMBOL: AddActor(new DragonNest(j, i, DRAGONNEST_COOLDOWN));
				break;
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
	distances.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		visited[i].resize(map_[i].size());
		paths[i].resize(map_[i].size());
		acted[i].resize(map_[i].size());
		distances[i].resize((map_[i].size()));
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
	actors[c->position().y][c->position().x] = c;
}

Map::Map(const Map &map_)
{
	actors = map_.actors;
	visited = map_.visited;
	paths = map_.paths;
}

void Map::Display()
{
	if (actors[princess->position().y][princess->position().x]->Symbol() == EMPTINESS_SYMBOL)
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
			if (PathExist(new_pos) && actors[new_pos.y][new_pos.x]->Symbol() != WALL_SYMBOL && visited[new_pos.y][new_pos.x] == false)
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

void Map::Insert(Actor* actor, vec2i pos)
{
	actors[pos.y][pos.x] = actor;
}
