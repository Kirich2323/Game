#include<iostream>
#include<vector>
#include<string>
#include"Controller.h"
//#include"vec2.h"

using namespace std;

int main(void)
{
	vector<string> map_ = {
		"Z...............................###......................Z.",
		"................................###........................",
		"...............W..................#............W.........$.",
		"............................#.......#......................",
		"####...........$............#..............................",
		"..###..............###.......@.....#.#..................Z..",
		"P..###.............#D#...................................##",
		"...####............#.#Z............#.##....................",
		"Z....................#Z...................................K"
	};

	vector<vector<char>> char_map(map_.size());
	for (int i = 0; i < map_.size(); i++)
	{
		char_map[i].resize(map_[i].size());
		for (int j = 0; j < map_[i].size(); j++)
			char_map[i][j] = map_[i][j];
	}

	Map map(char_map);
	system("Color 0B");
	Controller controller(map);
	controller.Start();
	return 0;
}