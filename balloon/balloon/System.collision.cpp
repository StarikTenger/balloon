#include "System.h"
#include "Geometry.h"
#include <iostream>

using namespace std;
void System::collision(Ball& object, Ball& subject) {
	vector<Vector2d> polygon;
	for (auto& p : subject.points) {
		polygon.push_back(p.pos);
	}
	for (auto& p : object.points) {
		if (!geom::inPolygon(p.pos, polygon))
			continue;
		pair<Body*, Body*> line;
		double dist = 10000000000;
		for (int i = 0; i < subject.points.size() - 1; i++) {
			double currentDist = geom::distance(p.pos, subject.points[i].pos, subject.points[i + 1].pos);
			if (currentDist < dist) {
				dist = currentDist;
				line.first = &subject.points[i];
				line.second = &subject.points[i + 1];
			}
		}
		double k = 1000;
		p.vel += geom::rotate(geom::direction(line.first->pos, line.second->pos), M_PI/2)*k * dt;
		line.first->vel += geom::rotate(geom::direction(line.first->pos, line.second->pos), M_PI/2)*k * dt * (-0.5);
		line.second->vel += geom::rotate(geom::direction(line.first->pos, line.second->pos), M_PI/2)*k * dt * (-0.5);
	}
}