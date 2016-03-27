#include"Controller.h"
#include<exception>

Controller::Controller(Map& map_){
	map = map_;
	gameover = false;
}

void Controller::Start() {
	while (!gameover)
	{
		ShowMap();
		NextMove();

		if (map.GetPlayer()->position() == map.GetPrincess()->position())
			Win();
		else if (((Character*)map.GetPlayer())->HitPoint() <= 0)
			Lose();
	}
}
void Controller::Win(void)
{
	gameover = true;
	system("CLS");
	std::cout << "CONGRATULATIONS, YOU WIN!!!" << std::endl;
}

void Controller::Lose(void)
{
	gameover = true;
	system("CLS");
	std::cout << ";_; GAME OVER ;_;" << std::endl;
}

void Controller::NextMove()
{
	map.ClearActed();
	map.GetPlayer()->Act(map);
	map.SetActed(map.GetPlayer()->position());
	map.UpdateDistances();
	for (int i = 0; i < map.GetMap().size(); i++)
		for (int j = 0; j < map.GetMap()[i].size(); j++)
			if (!map.GetActed()[i][j])
				map.GetMap()[i][j]->Act(map);
}

void Controller::ShowMap()
{
	system("CLS");
	printf("%d HP\n", ((Character*)map.GetPlayer())->HitPoint());  // показать HP
	map.Display();
}