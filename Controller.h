#pragma once
#include<vector>
#include<list>
#include"Map.h"
#include"Actor.h"
#include"Character.h"

class Controller {
public:
	Controller(Map map_);
	void Start();
private:
	Map map;
	bool gameover;
	std::list<Actor*> characters;
	std::vector<std::vector<Actor*>> actors;
	Actor* player;
	Actor* princess;
	void AddPlayer(Actor* c);
	void AddPrincess(Actor* c);
	void AddCharacter(Actor* c);
	void Win();
	void Lose();
	auto Find(std::pair<int, int> pos);
	void NextMove();
	void ShowMap();
};
