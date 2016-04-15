#pragma once
#include"Actor.h"
#include"Cfg.h"

class Fireball : public Actor
{
public:
	Fireball(int dmg, vec2i dir, int x_, int y_) : Actor(x_, y_), damage(dmg), direction(dir) {}
	~Fireball() {}
	void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	void Collide(Map& map, Fireball* target);
	void Collide(Map& map, Character* target);
	char Symbol() { return fb_dir[direction]; }
	int& GetDamage() { return damage; }
	void Act(Map& map);
private:
	vec2i direction;
	int damage;
};