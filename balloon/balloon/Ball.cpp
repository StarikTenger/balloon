#include "Ball.h"

Ball::Ball(){
}

Ball::Ball(std::vector<Body> _points, double _pv, double _k, double _l0, Color _color) {
	points = _points;
	pv = _pv;
	k = _k;
	l0 = _l0;
	color = _color;

}

Ball::~Ball(){
}

double Ball::square() {
	std::vector<Vector2d> polygon;
	for (auto p : points) {
		polygon.push_back(p.pos);
	}
	return geom::square(polygon);
}

int Ball::circle() {
	centre = Vector2d(0, 0);
	for (auto& p : points) {
		centre += p.pos;
	}
	centre = centre / points.size();
	r = 0;
	for (auto& p : points) {
		double dist = geom::distance(centre, p.pos);
		if (dist > r)
			r = dist;
	}
	return 0;
}
