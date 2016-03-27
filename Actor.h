#pragma once
#include<iostream>
#include"Map.h"
#include<vector>
#include"Constants.h"

class Character;
class Knight;
class Princess;
class Monster;

class Item;
class Medkit;

class Object;
class Wall;
class Emptiness;


class Actor
{
public:
	Actor(int& x_, int& y_) : pos(std::pair<int, int>(x_, y_)) {}
	virtual char Symbol() = 0;
	std::pair<int, int> position() { return pos; }
	virtual void replace(std::pair<int, int>& new_pos, Map& map);
	virtual ~Actor() {}
	virtual void Act(Map& map) = 0;
	virtual void Collide(Map& map, Actor* target) = 0;
	virtual void Collide(Map& map, Character* target) {}
	virtual void Collide(Map& map, Item* target) {}
	virtual void Collide(Map& map, Object* target) {}
	virtual void Collide(Map& map, Fireball* target) {}
protected:
	std::pair<int, int> pos;
};