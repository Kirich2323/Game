#pragma once
#include<vector>
#include<list>
#include"Map.h"
#include"Character.h"

class Controller {
public:
	Controller(Map map_);
	void Start();
private:
	Map map;
	bool gameover;
	std::list<Character*> characters;
	Character* player;
	Character* princess;

	void AddPlayer(Character* c) { player = c; }
	void AddPrincess(Character* c) { princess = c; }
	void AddMonster(Character* c) { characters.push_back(c); }
	void Win();
	void Lose();
	auto Find(std::pair<int, int> pos);
	void NextMove();
	void ShowMap();
	void PlayerAction();
	void MonsterAction(std::list<Character*>::iterator initiator);
};
