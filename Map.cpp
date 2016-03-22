#include"Map.h"

Map::Map()
{
	map.resize(1);
	map[0].resize(1);
	map[0][0] = '.';
}

Map::Map(std::vector<std::vector<char>> map_)
{
	map = map_;
	visited.resize(map_.size());
	paths.resize(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		visited[i].resize(map_[i].size());
		paths[i].resize(map_[i].size());
	}
}

Map::Map(const Map &map_)
{
	map = map_.map;
	visited = map_.visited;
	paths = map_.paths;
}

void Map::Display()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
}

void Map::SetChar(std::pair<int, int> pos, char c)
{
	map[pos.second][pos.first] = c;
}

std::vector<std::vector<char>>& Map::GetMap()
{
	return map;
}

std::vector<std::vector<std::pair<int, int>>>& Map::GetPaths()
{
	return paths;
}

std::vector<std::vector<bool>>& Map::GetVisited()
{
	return visited;
}

void Map::ClearVisited()
{
	for (int i = 0; i < visited.size(); i++)
		for (int j = 0; j < visited[i].size(); j++)
			visited[i][j] = false;
}
