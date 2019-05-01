#pragma once
#include <vector>
#include "Ball.h"
#include "Wall.h"
#include "Vector2d.h"
#include <string>

class System {
public:

	double dt = 0.001;
	long double time = 0;
	double frictionK = 1;
	double pressure = 5;

	std::vector<Ball> balls;
	std::vector<Wall> walls;
	Vector2d border;
	Vector2d g;

	System();
	~System();

	void step();
	void bubble(Vector2d pos, double r, Vector2d vel, double m, double k, double l0, double n, Color c);
	void checkWall(Body& b);
	void collision(Ball& object, Ball& subject);
};

