#pragma once
#include<iostream>

class Actor
{
public:
	Actor(int& x_, int& y_) : pos(std::pair<int, int>(x_, y_)) {}
	virtual char Symbol() = 0;
	std::pair<int, int> position() { return pos; }
	void replace(std::pair<int, int>& new_pos, Map &map); //delete
	virtual ~Actor() {}
protected:
	std::pair<int, int> pos;
};

inline void Actor::replace(std::pair<int, int>& new_pos, Map& map)
{
	map.SetChar(pos, '.');
	pos = new_pos;
	map.SetChar(pos, Symbol());

}