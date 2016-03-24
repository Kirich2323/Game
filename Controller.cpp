#include"Controller.h"
#include<exception>

Controller::Controller(Map map_){
	map = map_;
	gameover = false;
	for (int i = 0; i < map.GetMap().size(); i++)
	{
		for (int j = 0; j < map.GetMap()[i].size(); j++)
		{
			switch (map.GetMap()[i][j]) {
			case 'K': {
				if (player == NULL)
					AddPlayer(new Knight(100, j, i));
				else
					throw(std::runtime_error("Too many knights"));
				break;
			}
			case 'P': 
			{
				if (princess == NULL)
					AddPrincess(new Princess(100, j, i));
				else
					throw(std::runtime_error("Too many princesses"));
				break;
			}
			case 'Z': AddCharacter(new Zombie(10, j, i));
				break;
			case 'D': AddCharacter(new Dragon(50, j, i));
			}
		}
	}

	if (princess == NULL)
	{
		throw(std::runtime_error("No princess found"));
	}

	if (player == NULL)
	{
		throw(std::runtime_error("No knight found"));
	}
}

void Controller::Start() {
	while (!gameover)
	{
		ShowMap();
		NextMove();

		if (player->position() == princess->position())
			Win();
		else if (((Character*)player)->HitPoint() <= 0)
			Lose();
	}
}

void Controller::AddPlayer(Actor * c)
{
	characters.push_front(c);
	player = c;
}

void Controller::AddPrincess(Actor * c)
{
	characters.push_back(c);
	princess = c;
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

auto Controller::Find(std::pair<int, int> pos)
{
	for (auto iter = characters.begin(); iter != characters.end(); iter++)
		if ((*iter)->position() == pos)
			return iter;
	return characters.end();
}

void Controller::NextMove()
{
	for (auto i = characters.begin(); i != characters.end(); i++)
	{
		std::pair<int, int> pos = (*i)->Move(map);
		if (pos == std::pair<int, int>(-1, -1))
			continue;

		auto target = Find(pos);
		if (target == i)
			continue;

		if (target == characters.end())
		{
			(*i)->replace(pos, map);
		}
		else
		{
			map.SetChar((*i)->position(), '.');
			(*target)->Collide(*i);
			if (((Character*)(*target))->HitPoint() <= 0)
			{
				characters.erase(target);
			}
			map.SetChar((*i)->position(), (*i)->Symbol());
		}
	}
}

void Controller::ShowMap()
{
	map.SetChar(princess->position(), princess->Symbol()); // показать принцессу

	for (auto i = characters.begin(); i != characters.end(); i++)
		map.SetChar((*i)->position(), (*i)->Symbol());     // показать монстров

	map.SetChar(player->position(), player->Symbol());     //  показать игрока

	system("CLS");
	printf("%d HP\n", ((Character*)player)->HitPoint());  // показать HP
	map.Display();
}