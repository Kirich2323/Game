#include"Item.h"
#include"Character.h"

void Medkit::Collide(Map& map, Character * target)
{
	target->Heal(HealPower());
	target->replace(pos, map);
}
