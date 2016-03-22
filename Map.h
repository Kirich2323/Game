#pragma once
#include<vector>
#include<string>
#include<iostream>

class Map {
public:
	Map();
	Map(std::vector<std::vector<char>> map_);
	Map(const Map &map_);
	void Display();
	void SetChar(std::pair<int, int> pos, char c);
	std::vector<std::vector<char>>& GetMap();
	std::vector<std::vector<std::pair<int, int>>>& GetPaths();
	std::vector<std::vector<bool>>& GetVisited();
	void ClearVisited();
private:
	std::vector<std::vector<char>> map;
	std::vector<std::vector<std::pair<int, int>>> paths;
	std::vector<std::vector<bool>> visited;
};
