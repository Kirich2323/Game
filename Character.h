#pragma once
#include"Map.h"
#include<string>
#include<map>
#include<list>
#include<set>

static std::vector<std::pair<int, int>> ways = {
	std::pair<int, int>(1, 0),
	std::pair<int, int>(-1, 0),
	std::pair<int, int>(0, 1),
	std::pair<int, int>(0, -1) 
};

static std::map<char, std::pair<int, int>> directions = { 
	{ 'w', std::pair<int, int>(0, -1) },													  
	{ 's', std::pair<int, int>(0,  1) },													 
	{ 'a', std::pair<int, int>(-1,  0) },													  
	{ 'd', std::pair<int, int>(1,  0) } };


static std::set<char> monsters = {'Z', 'D'};

inline std::pair<int, int> operator+(const std::pair<int, int> &left, const std::pair<int, int> &right)
{
	return std::pair<int, int>(left.first + right.first, left.second + right.second);
}

class Character {
public:
	Character(int h, int x_, int y_) : hitpoints(h), pos(std::pair<int, int>(x_, y_)) {}
	void TakeDamage(int amount);
	virtual char Symbol() = 0;
	virtual std::pair<int, int> Move(Map &map) = 0;
	virtual int HitPoint() = 0;
	virtual int Damage() = 0;
	std::pair<int, int> position();
	void replace(std::pair<int, int> new_pos, Map &map);
	virtual ~Character() {};
protected:
	virtual bool PathExist(Map &map, std::pair<int, int> target);
	int hitpoints;
	std::pair<int, int> pos;
};

class Knight : public Character {
public:
	Knight(int h, int x, int y): Character(h, x, y) {}
	char Symbol();
	std::pair<int, int> Move(Map &map);
	int HitPoint();
	int Damage();
};

class Princess : public Character {
public:
	Princess(int h, int x, int y) : Character(h, x, y) {}
	char Symbol();
	std::pair<int, int> Move(Map &map);
	int HitPoint();
	int Damage();
};

class Monster : public Character {
public:
	Monster(int h, int x, int y) : Character(h, x, y) {}
	virtual char Symbol() = 0;
	std::pair<int, int> Move(Map &map);
	int HitPoint() = 0;
	virtual int Damage() = 0;
private:
	std::pair<int, int>& SearchForPath(Map &map);
	std::pair<int, int> SearchForKnight(Map &map);
	bool PathExist(Map &map, std::pair<int, int> target);
};

class Zombie : public Monster {
public:
	Zombie(int h, int x, int y): Monster(h, x, y) {}
	char Symbol();
	int HitPoint();
	int Damage();
};

class Dragon : public Monster {
public:
	Dragon(int h, int x, int y): Monster(h, x, y){}
	char Symbol();
	int HitPoint();
	int Damage();
};