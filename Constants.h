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

#define KNIGHT_HP 150
#define ZOMBIE_HP 10
#define DRAGON_HP 50
#define PRINCESS_HP 25
#define WIZARD_HP 15

#define KNIGHT_DMG 10
#define ZOMGIE_DMG 5
#define DRAGON_DMG 7
#define WIZARD_DMG 2
#define FIREBALL_DMG 15

#define DRAGONNEST_COOLDOWN 24

static std::map<std::pair<int, int>, char> fb_dir = {
	{std::pair<int, int>( 0,-1), '^' },
	{std::pair<int, int>( 0, 1), 'v' },
	{std::pair<int, int>(-1, 0), '<'},
	{std::pair<int, int>( 1, 0), '>' }
};
static std::vector<std::pair<int, int>> ways = {
	std::pair<int, int>(1, 0),
	std::pair<int, int>(-1, 0),
	std::pair<int, int>(0, 1),
	std::pair<int, int>(0,-1)
};

static std::map<char, std::pair<int, int>> directions = {
	{ 'w', std::pair<int, int>(0,-1) },
	{ 's', std::pair<int, int>(0, 1) },
	{ 'a', std::pair<int, int>(-1, 0) },
	{ 'd', std::pair<int, int>(1, 0) } };


static std::set<char> monsters = { ZOMBIE_SYMBOL, DRAGON_SYMBOL, WIZARD_SYMBOL };

inline std::pair<int, int> operator+(const std::pair<int, int> &left, const std::pair<int, int> &right)
{
	return std::pair<int, int>(left.first + right.first, left.second + right.second);
}

