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
					throw(std::runtime_error("Too many princess"));
				break;
			}
			case 'Z': AddMonster(new Zombie(10, j, i));
				break;
			case 'D': AddMonster(new Dragon(50, j, i));
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
		else if (player->HitPoint() <= 0)
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

auto Controller::Find(std::pair<int, int> pos)
{
	for (auto iter = characters.begin(); iter != characters.end(); iter++)
		if ((*iter)->position() == pos)
			return iter;
	return characters.end();
}

void Controller::NextMove()
{
	PlayerAction();
	for (auto i = characters.begin(); i != characters.end(); i++)
	{
		MonsterAction(i);
	}
}

void Controller::ShowMap()
{
	map.SetChar(princess->position(), princess->Symbol()); // показать принцессу

	for (auto i = characters.begin(); i != characters.end(); i++)
		map.SetChar((*i)->position(), (*i)->Symbol());     // показать монстров

	map.SetChar(player->position(), player->Symbol());     //  показать игрока

	system("CLS");
	printf("%d HP\n", player->HitPoint());  // показать HP
	map.Display();
}

void Controller::PlayerAction()
{
	std::pair<int, int> pos = player->Move(map);

	if (player->position() == pos)
		return;
	
	if (monsters.find(map.GetMap()[pos.second][pos.first]) == monsters.end())
	{
		player->replace(pos, map);
		return;
	}

	auto target = Find(pos);
	(*target)->TakeDamage(player->Damage());

	if ((*target)->HitPoint() <= 0)
	{
		characters.erase(target);
		player->replace(pos, map);
	}
}

void Controller::MonsterAction(std::list<Character*>::iterator initiator)
{
	std::pair<int, int> pos = (*initiator)->Move(map);
	if (monsters.find(map.GetMap()[pos.second][pos.first]) == monsters.end())
	{
		if (pos == player->position())
		{
			player->TakeDamage((*initiator)->Damage());
			return;
		}
		else
			(*initiator)->replace(pos, map);
	}
}