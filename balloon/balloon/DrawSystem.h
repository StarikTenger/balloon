#pragma once
#include "Draw.h"
#include "System.h"

class DrawSystem{
public:
	Draw* drawTools = nullptr;
	DrawSystem();
	DrawSystem(Draw* _drawTools);
	~DrawSystem();

	void draw(System& sys);
};

