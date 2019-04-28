#include "DrawSystem.h"
#include <math.h>
#include <algorithm>

#include <iostream>

DrawSystem::DrawSystem(){}
DrawSystem::DrawSystem(Draw* _drawTools) {
	drawTools = _drawTools;
}

DrawSystem::~DrawSystem(){}

void DrawSystem::draw(System& sys) {
	drawTools->fill(Color(20, 20, 20));
	
	for (auto& ball : sys.balls) {
		int l = ball.points.size();
		for (int i = 0; i < l; i++) {
			int j = (i + 1 + l) % l;
			int j1 = (i + 2 + l) % l;
			Vector2d p1, p2, p3;
			p1 = ball.points[i].pos;
			p2 = ball.points[j].pos;
			p3 = ball.points[j1].pos;
			drawTools->drawLine(p1.x, p1.y, p2.x, p2.y, ball.color);
		}

	}

	// walls
	for (auto& w : sys.walls) {		
		for (int i = 0; i < w.points.size() - 1; i++) {
			int j = i + 1;
			drawTools->drawLine(w.points[i].x, w.points[i].y, w.points[j].x, w.points[j].y, Color(250, 250, 0));
		}
	}

	drawTools->push();
}
