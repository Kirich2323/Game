#pragma once

#include"Actor.h"
#include"Character.h"

class Object : public Actor
{
public:
	Object(int x_, int y_) : Actor(x_, y_) {}
	virtual void Act(Map& map) {}
	virtual ~Object() {}
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target) {}
	virtual void Collide(Map& map, Fireball* target) {}
private:

};

class Wall : public Object
{
public:
	Wall(int x_, int y_) : Object(x_, y_) {}
	~Wall() {}
	virtual void Collide(Map& map, Fireball* target);
	char Symbol() { return WALL_SYMBOL; }
private:
};

class Emptiness : public Object
{
public:
	Emptiness(int x_, int y_) : Object(x_, y_) {}
	~Emptiness() {}
	virtual void Collide(Map& map, Character* target) { target->replace(pos, map); }
	virtual void Collide(Map& map, Fireball* target);
	char Symbol() { return EMPTINESS_SYMBOL; }
};