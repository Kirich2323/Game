#include"Actor.h"
#include"Object.h"

void Actor::replace(std::pair<int, int>& new_pos, Map& map)
{
	map.GetMap()[pos.second][pos.first] = new Emptiness(pos.first, pos.second);
	map.SetActed(pos);
	pos = new_pos;
	map.SetActed(pos);
	delete(map.GetMap()[new_pos.second][new_pos.first]);
	map.GetMap()[pos.second][pos.first] = this;
}