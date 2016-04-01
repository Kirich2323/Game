#include"Actor.h"
#include"Object.h"

void Actor::replace(vec2i& new_pos, Map& map)
{
	map.Insert(new Emptiness(pos.x, pos.y));
	map.SetActed(pos);
	pos = new_pos;
	map.SetActed(pos);
	map.Erase(new_pos);
	map.Insert(this);
}