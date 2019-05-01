#pragma once
#include "Body.h"
#include "Geometry.h"
#include "Color.h"

class Ball {
public:
	std::vector<Body> points;
	Vector2d centre;
	int defect = 0;
	double r = 10000000000;       // centre and r for collision
	double pv = 10; //conts P * V
	double k = 1; //spring stiffness
	double l0 = 0;
	Color color;
	Ball();
	Ball(std::vector<Body> _points, double _pv, double _k, double _l0, Color _color);
	~Ball();
	double square(); //square od ball
	int circle(); //configure r and centre
};

