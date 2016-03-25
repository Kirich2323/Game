#pragma once
#include<iostream>
#include"Map.h"

class Character;
class Knight;
class Princess;
class Monster;
class Item;
class Medkit;

class Actor
{
public:
	Actor(int& x_, int& y_) : pos(std::pair<int, int>(x_, y_)) {}
	virtual char Symbol() = 0;
	std::pair<int, int> position() { return pos; }
	void replace(std::pair<int, int>& new_pos, Map &map); //delete
	virtual ~Actor() {}
	virtual void Collide(Actor* target) = 0;
	virtual void Collide(Character* target) = 0;
	virtual void Collide(Knight* target) = 0;
	virtual void Collide(Princess* target) = 0;
	virtual void Collide(Monster* target) = 0;
	virtual void Collide(Item* target) = 0;
	virtual void Collide(Medkit* target) = 0;
protected:
	std::pair<int, int> pos;
};

inline void Actor::replace(std::pair<int, int>& new_pos, Map& map)
{
	map.SetChar(pos, '.');
	pos = new_pos;
	map.SetChar(pos, Symbol());

}