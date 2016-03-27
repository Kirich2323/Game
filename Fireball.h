#pragma once
#include"Actor.h"
#include"Constants.h"

class Fireball : public Actor
{
public:
	Fireball(int dmg, std::pair<int, int> dir, int x_, int y_) : Actor(x_, y_), damage(dmg), direction(dir) {}
	~Fireball() {}
	void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	void Collide(Map& map, Character* target);
	char Symbol() { return fb_dir[direction]; }
	int& GetDamage() { return damage; }
	void Act(Map& map);
private:
	std::pair<int, int> direction;
	bool PathExist(Map& map, std::pair<int, int> pos);
	int damage;
};