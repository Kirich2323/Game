#pragma once
#include"Actor.h"
#include"Constants.h"

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
	bool PathExist(Map& map, std::pair<int, int> pos);
	int max_cooldown;
	int cooldown;
};

class Cemetery : public Spawner
{
public:
	Cemetery(int x_, int y_, int cd) : Spawner(x_, y_, cd) {}
	~Cemetery() {}
	char Symbol() { return CEMETRY_SYMBOL; }
protected:
	void Spawn(Map& map);
};

class DragonNest : public Spawner
{
public:
	DragonNest(int x_, int y_, int cd) : Spawner(x_, y_, cd) {}
	~DragonNest() {}
	char Symbol() { return DRAGONNEST_SYMBOL; }
protected:
	void Spawn(Map& map);
};