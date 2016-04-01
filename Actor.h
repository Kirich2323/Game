#pragma once
#include<iostream>
#include"Map.h"
#include<vector>
#include"Constants.h"
#include"vec2i.h"

class Character;
class Knight;
class Princess;
class Monster;

class Item;
class Medkit;

class Object;
class Wall;
class Emptiness;

class Fireball;

class Spawner;

class Actor
{
public:
	Actor(int& x_, int& y_) : pos(x_, y_) {}
	virtual char Symbol() = 0;
	vec2i position() { return pos; }
	virtual void replace(vec2i& new_pos, Map& map);
	virtual ~Actor() {}
	virtual void Act(Map& map) = 0;
	virtual void Collide(Map& map, Actor* target) {};
	virtual void Collide(Map& map, Character* target) {}
	virtual void Collide(Map& map, Item* target) {}
	virtual void Collide(Map& map, Object* target) {}
	virtual void Collide(Map& map, Fireball* target) {}
	virtual void Collide(Map& map, Spawner* target) {}
protected:
	vec2i pos;
};