#pragma once
#include"Actor.h"
#include"Cfg.h"

class Spawner : public Actor
{
public:
	Spawner(int x_, int y_, int cd) : Actor(x_, y_), max_cooldown(cd), cooldown(cd) {}
	~Spawner() {}
	virtual char Symbol() = 0;
	virtual void Act(Map& map);
	void Collide(Map& map, Fireball* target);
protected:
	virtual void Spawn(Map& map) = 0;	
	bool PathExist(Map& map, vec2i pos);
	int max_cooldown;
	int cooldown;
};

class Cemetery : public Spawner
{
public:
	Cemetery(int x_, int y_, int cd) : Spawner(x_, y_, cd) {}
	~Cemetery() {}
	char Symbol() { return Cfg::GetInstance().get_cemetery_symbol(); }
protected:
	void Spawn(Map& map);
};

class DragonNest : public Spawner
{
public:
	DragonNest(int x_, int y_, int cd) : Spawner(x_, y_, cd) {}
	~DragonNest() {}
	char Symbol() { return Cfg::GetInstance().get_dragon_nest_symbol(); }
protected:
	void Spawn(Map& map);
};