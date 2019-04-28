#pragma once
#include "Body.h"
#include "Geometry.h"
#include "Color.h"

class Ball {
public:
	std::vector<Body> points;
	double pv = 10; //conts P * V
	double k = 1;
	double l0 = 0;
	Color color;
	Ball();
	Ball(std::vector<Body> _points, double _pv, double _k, double _l0, Color _color);
	~Ball();
	double square();
};

