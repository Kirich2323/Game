#pragma once
#include<iostream>

class Actor
{
public:
	Actor(int& h, int& x_, int& y_) : hitpoints(h), pos(std::pair<int, int>(x_, y_)) {}
	virtual char Symbol() = 0;
	virtual std::pair<int, int> Move(Map& map) = 0;
	virtual int HitPoint() = 0;
	virtual int Damage() = 0;
	void TakeDamage(const int& amount) { hitpoints -= amount; }
	std::pair<int, int> position() { return pos; }
	void replace(std::pair<int, int>& new_pos, Map &map);
	virtual ~Actor() {}
protected:
	std::pair<int, int> pos;
	int hitpoints;
};

inline void Actor::replace(std::pair<int, int>& new_pos, Map& map)
{
	map.SetChar(pos, '.');
	pos = new_pos;
	map.SetChar(pos, Symbol());

}