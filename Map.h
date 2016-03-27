#pragma once
#include<vector>
#include<string>
#include<iostream>

class Actor;

class Map {
public:
	Map();
	Map(std::vector<std::vector<char>>& map_);
	Map(const Map &map_);
	void Display();
	std::vector<std::vector<Actor*>>& GetMap();
	std::vector<std::vector<Actor*>> GetBufMap();
	std::vector<std::vector<std::pair<int, int>>>& GetPaths();
	std::vector<std::vector<bool>>& GetVisited();
	void SetActed(std::pair<int, int>& pos);
	void ClearActed();
	void UpdateDistances();
	std::vector<std::vector<bool>>& GetActed();
	Actor* GetPlayer() { return player; }
	Actor* GetPrincess() { return princess; }
	std::vector<std::vector<int>>& GetDistances() { return distances; }
	void ClearVisited();
	bool PathExist(std::pair<int, int> pos);
	void Erase(std::pair<int, int> pos);
	void Insert(Actor* actor, std::pair<int, int> pos);
private:
	Actor* player;
	Actor* princess;
	std::vector<std::vector<Actor*>> actors;
	void AddPlayer(Actor* c);
	void AddPrincess(Actor* c);
	void AddActor(Actor* c);
	std::vector<std::vector<std::pair<int, int>>> paths;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<bool>> acted;
	std::vector<std::vector<int>> distances;
};
