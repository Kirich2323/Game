#pragma once
#include<string>
#include<map>
#include<list>
#include<set>
#include"Actor.h"
#include"Item.h"
#include"Constants.h"

class Character : public Actor {
public:
	Character(int h, int x_, int y_) : hitpoints(h), max_hp(h), Actor(x_, y_) {}
	void TakeDamage(const int& amount) { hitpoints -= amount; }
	virtual int Damage() = 0;
	virtual int HitPoint() { return hitpoints; }
	void Heal(int amount);
	virtual ~Character() {};
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target) {};
	virtual void Collide(Map& map, Knight* target) {};
	virtual void Collide(Map& map, Princess* target) {};
	virtual void Collide(Map& map, Monster* target) {};
	virtual void Collide(Map& map, Fireball* target);
	virtual void Act(Map& map) { Move(map); }
protected:
	int hitpoints;
	int max_hp;
	virtual void Move(Map& map) = 0;
	virtual bool PathExist(Map& map, std::pair<int, int>& target);
};

class Knight : public Character {
public:
	Knight(int h, int x, int y): Character(h, x, y) {}
	char Symbol() { return KNIGHT_SYMBOL; }
	int Damage() { return 10; }
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Monster* target);
	virtual void Collide(Map& map, Princess* target);
private:
	void Move(Map& map);
};

class Princess : public Character {
public:
	Princess(int h, int x, int y) : Character(h, x, y) {}
	char Symbol() { return PRINCESS_SYMBOL; }
	int Damage() { return 0; }
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target) { target->Collide(map, this); }
private:
	void Move(Map& map) {};
};

class Monster : public Character {
public:
	Monster(int h, int x, int y) : Character(h, x, y) {}
	virtual char Symbol() = 0;
	virtual int Damage() = 0;
	virtual void Collide(Map& map, Actor* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Character* target) { target->Collide(map, this); }
	virtual void Collide(Map& map, Knight* target);
	virtual void Collide(Map& map, Princess* target);
protected:
	bool PathExist(Map &map, std::pair<int, int>& target);
private:
	std::pair<int, int>& SearchForPath(Map &map);
	virtual void Move(Map& map);
};

class Zombie : public Monster {
public:
	Zombie(int h, int x, int y): Monster(h, x, y) {}
	char Symbol() { return ZOMBIE_SYMBOL; }
	int Damage() { return 5; }
};

class Dragon : public Monster {
public:
	Dragon(int h, int x, int y): Monster(h, x, y){}
	char Symbol() { return DRAGON_SYMBOL; }
	int Damage() { return 7; }
};

class Wizard : public Monster
{
public:
	Wizard(int h_, int x_, int y_) : Monster(h_, x_, y_) {}
	~Wizard() {}
	virtual void Act(Map& map);
	char Symbol() { return WIZARD_SYMBOL; }
	int Damage() { return 2; }
private:
	int fireball_damage = FIREBALL_DMG;
	void LaunchFireball(Map& map);
	void Move(Map& map);
};