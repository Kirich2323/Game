#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"vec2i.h"
#include<map>

class Actor;
class RemoteSpawner;

class Map {
public:
	Map();
	Map(std::vector<std::vector<char>>& map_);
	Map(const Map &map_);
	void Display();
	std::vector<std::vector<Actor*>>& GetMap();
	std::vector<std::vector<Actor*>> GetBufMap();
	std::vector<std::vector<vec2i>>& GetPaths();
	std::vector<std::vector<bool>>& GetVisited();
	std::vector<RemoteSpawner*>& GetRemoteSpawners() { return remote_spawners; }
	void SetActed(vec2i& pos);
	void ClearActed();
	void UpdateDistances();
	std::vector<std::vector<bool>>& GetActed();
	Actor* GetPlayer() { return player; }
	Actor* GetPrincess() { return princess; }
	std::vector<std::vector<int>>& GetDistances() { return distances; }
	void ClearVisited();
	bool PathExist(vec2i pos);
	void Erase(vec2i pos);
	void Insert(Actor* actor);
private:
	Actor* player;
	Actor* princess;
	std::vector<std::vector<Actor*>> actors;
	void AddPlayer(Actor* c);
	void AddPrincess(Actor* c);
	void AddActor(Actor* c);
	std::vector<std::vector<vec2i>> paths;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<bool>> acted;
	std::vector<std::vector<int>> distances;
	std::vector<RemoteSpawner*> remote_spawners;
	void CreateKnight(vec2i pos);
	void CreatePrincess(vec2i pos);
	void CreateZombie(vec2i pos);
	void CreateDragon(vec2i pos);
	void CreateCemetery(vec2i pos);
	void CreateDragonNest(vec2i pos);
	void CreateWizard(vec2i pos);
	void CreateEmptiness(vec2i pos);
	void CreateWall(vec2i pos);
	void CreateMedkit(vec2i pos);
	std::map<char, void (Map::*)(vec2i c)> funcs;
};
