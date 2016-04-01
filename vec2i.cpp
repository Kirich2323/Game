#include"vec2i.h"

vec2i operator+(const vec2i& left, const vec2i& right)
{
	return vec2i(left.x + right.x, left.y + right.y);
}

int& vec2i::operator[](const int& i)
{
	if (i != 1 && i != 0)
	{
		throw(std::runtime_error("Index of vec2i must be 0 or 1"));
	}
	return i == 0 ? x : y;
}

bool operator<(const vec2i& left, const vec2i& right)
{
	return left.x < right.x && left.y < right.y;
}

bool operator==(const vec2i& left, const vec2i& right)
{
	return left.x == right.x && left.y == right.y;
}

bool operator!=(const vec2i& left, const vec2i& right)
{
	return left.x != right.x || left.y != right.y;
}