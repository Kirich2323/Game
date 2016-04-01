#pragma once
#include<map>
#include<set>

#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'
#define MEDKIT_SYMBOL '+'
#define WALL_SYMBOL '#'
#define EMPTINESS_SYMBOL '.'
#define WIZARD_SYMBOL 'W'
#define CEMETRY_SYMBOL '$'
#define DRAGONNEST_SYMBOL '@'

#define KNIGHT_HP 15000
#define ZOMBIE_HP 10
#define DRAGON_HP 50
#define PRINCESS_HP 25
#define WIZARD_HP 15

#define KNIGHT_DMG 10
#define ZOMGIE_DMG 5
#define DRAGON_DMG 7
#define WIZARD_DMG 2
#define FIREBALL_DMG 15

#define CEMETERY_COOLDOWN 14
#define DRAGONNEST_COOLDOWN 24
#define MEDKIT_SPAWN_COOLDOWN 5

#define MEDKIT_MAX_COUNT 5
#define MEDKIT_HEAL_POWER 10

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


static std::set<char> monsters = { ZOMBIE_SYMBOL, DRAGON_SYMBOL, WIZARD_SYMBOL };
