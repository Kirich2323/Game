#pragma once
#include<exception>
#include<iostream>

class vec2i
{
public:
	int x, y;
	vec2i(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	~vec2i() {}
	friend vec2i operator+(const vec2i& left, const vec2i& right);
	int& operator[](const int& i);
};