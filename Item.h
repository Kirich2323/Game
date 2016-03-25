#pragma once
#include"Actor.h"

class Item : public Actor
{
public:
	Item(int& x_, int& y_) : Actor(x_, y_) {}
	virtual ~Item() {};
private:
};

class Medkit : public Item
{
public:
	Medkit(int& x_, int& y_) : Item(x_, y_) {}
	~Medkit() {};
private:
};