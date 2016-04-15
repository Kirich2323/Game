#pragma once
#include<map>
#include<set>
#include<vector>
#include"vec2i.h"
#include"Json_importer.h"

class Cfg
{
public:
	static Cfg& GetInstance();
	void Parse(char* _filename);
	void SetVariables();
	char get_knight_symbol() { return knight_symbol; }
	char get_princess_symbol() { return princess_symbol; }
	char get_zombie_symbol() { return zombie_symbol; }
	char get_dragon_symbol() { return dragon_symbol; }
	char get_cemetery_symbol() { return cemetery_symbol; }
	char get_dragon_nest_symbol() { return dragon_nest_symbol; }
	char get_wizard_symbol() { return wizard_symbol; }
	char get_wall_symbol() { return wall_symbol; }
	char get_emptiness_symbol() { return emptiness_symbol; }
	char get_medkit_symbol() { return medkit_symbol; }

	int get_knight_hp() { return knight_hp; }
	int get_zombie_hp() { return zombie_hp; }
	int get_dragon_hp() { return dragon_hp; }
	int get_wizard_hp() { return wizard_hp; }
	int get_princess_hp() { return princess_hp; }

	int get_knight_dmg() { return knight_dmg; }
	int get_zombie_dmg() { return zombie_dmg; }
	int get_dragon_dmg() { return dragon_dmg; }
	int get_fireball_dmg(){ return fireball_dmg; }
	int get_wizard_dmg() { return wizard_dmg; }

	int get_cemetery_cooldown() { return cemetery_cooldown; }
	int get_dragon_nest_cooldown() { return dragon_nest_cooldown; }
	int get_medkit_cooldown() { return medkit_cooldown; }

	int get_medkit_max_count() { return medkit_max_count; }

	int get_medkit_heal_power() { return medkit_heal_power; }

	~Cfg();

private:
	json_importer* importer;
	Cfg(void);

	char knight_symbol;
	char princess_symbol;
	char zombie_symbol;
	char dragon_symbol;
	char cemetery_symbol;
	char dragon_nest_symbol;
	char wizard_symbol;
	char wall_symbol;
	char emptiness_symbol;
	char medkit_symbol;

	int knight_hp;
	int zombie_hp;
	int dragon_hp;
	int wizard_hp;
	int princess_hp;

	int knight_dmg;
	int zombie_dmg;
	int dragon_dmg;
	int fireball_dmg;
	int wizard_dmg;

	int cemetery_cooldown;
	int dragon_nest_cooldown;
	int medkit_cooldown;

	int medkit_max_count;

	int medkit_heal_power;
};

static std::map<vec2i, char> fb_dir = {
	{vec2i( 0,-1), '^' },
	{vec2i( 0, 1), 'v' },
	{vec2i(-1, 0), '<'},
	{vec2i( 1, 0), '>' }
};

static std::vector<vec2i> ways = {
	vec2i(1, 0),
	vec2i(-1, 0),
	vec2i(0, 1),
	vec2i(0,-1)
};

static std::map<char, vec2i> directions = {
	{ 'w', vec2i(0,-1) },
	{ 's', vec2i(0, 1) },
	{ 'a', vec2i(-1, 0) },
	{ 'd', vec2i(1, 0) } };


static std::set<char> monsters = { Cfg::GetInstance().get_zombie_symbol(),
                                   Cfg::GetInstance().get_dragon_symbol(),
	                               Cfg::GetInstance().get_wizard_symbol() };
