#pragma once
#include"Actor.h"

class Item : public Actor
{
public:
	Item(int& x_, int& y_) : Actor(x_, y_) {}
	virtual char Symbol() = 0;
	virtual ~Item() {};
	virtual void Act(Map& map) {}
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Fireball* target);
	virtual void Collide(Map& map, Character* target) = 0;
private:
};

class Medkit : public Item
{
public:
	Medkit(int& x_, int& y_) : Item(x_, y_) {}
	virtual char Symbol() { return Cfg::GetInstance().get_medkit_symbol(); }
	~Medkit() {};
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target);
	int HealPower() { return Cfg::GetInstance().get_medkit_heal_power(); }
private:
};