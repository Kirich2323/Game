#include"Actor.h"
#include"Object.h"

void Actor::replace(std::pair<int, int>& new_pos, Map& map)
{
	map.Insert(new Emptiness(pos.first, pos.second), pos);
	map.SetActed(pos);
	pos = new_pos;
	map.SetActed(pos);
	map.Erase(new_pos);
	map.Insert(this, pos);
}