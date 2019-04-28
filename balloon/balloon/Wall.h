#pragma once
#include "Body.h"
#include "Geometry.h"
#include "Color.h"

class Wall{
public:
	std::vector<Vector2d> points;
	Wall();
	Wall(std::vector<Vector2d> _points);
	~Wall();
};

