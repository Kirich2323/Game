#pragma once
#include"Actor.h"
#include"Map.h"

class RemoteSpawner
{
public:
	virtual void Act(Map& map) = 0;
protected:
	virtual void Spawn(Map& map) = 0;
	vec2i SeekCell(Map& map, vec2i pos);
	std::vector<vec2i> children_position;
	void Swap(const int& left, const int& right);
	int max_cooldown;
	int cooldown;
};

class MedkitSpawner : public RemoteSpawner
{
public:
	virtual void Act(Map& map);
protected:
	void Spawn(Map& map);
	int max_cooldown = MEDKIT_SPAWN_COOLDOWN;
	int cooldown = max_cooldown;
};