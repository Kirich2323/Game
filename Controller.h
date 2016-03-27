#pragma once
#include<vector>
#include<list>
#include"Map.h"
#include"Actor.h"
#include"Character.h"
#include"Item.h"

class Controller {
public:
	Controller(Map& map_);
	void Start();
private:
	Map map;
	bool gameover;
	void Win();
	void Lose();
	void NextMove();
	void ShowMap();
};
