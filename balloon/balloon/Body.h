#pragma once
#include "Vector2d.h"


class Body{
public:
	Vector2d pos;
	Vector2d posPrev;
	Vector2d vel;
	double m;

	Body();
	Body(Vector2d _pos, Vector2d _vel, double _m);
	~Body();
};

