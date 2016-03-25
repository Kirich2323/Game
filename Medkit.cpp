#include"Item.h"
#include"Character.h"
void Medkit::Collide(Character * target)
{
	std::cout << "Collision";
}

void Medkit::Collide(Knight * target)
{
	target->TakeDamage(-5);
}
