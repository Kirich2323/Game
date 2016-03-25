#pragma once
#include"Actor.h"

#define MEDKIT_SYMBOL '+'

class Item : public Actor
{
public:
	Item(int& x_, int& y_) : Actor(x_, y_) {}
	virtual char Symbol() = 0;
	virtual ~Item() {};
	virtual void Collide(Actor* target) { target->Collide(this); }
	virtual void Collide(Character* target) = 0;
	virtual void Collide(Knight* target) = 0;
	virtual void Collide(Princess* target) = 0;
	virtual void Collide(Monster* target) = 0;
	virtual void Collide(Item* target) = 0;
	virtual void Collide(Medkit* target) = 0;
private:
};

class Medkit : public Item
{
public:
	Medkit(int& x_, int& y_) : Item(x_, y_) {}
	virtual char Symbol() { return MEDKIT_SYMBOL; }
	~Medkit() {};
	virtual void Collide(Actor* target) { target->Collide(this); }
	virtual void Collide(Character* target);
	virtual void Collide(Knight* target);
	virtual void Collide(Princess* target) {}
	virtual void Collide(Monster* target) {}
	virtual void Collide(Item* target) {}
	virtual void Collide(Medkit* target) {}
	int HealPower() { return 10; }
private:
};