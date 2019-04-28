#include "System.h"

void System::bubble(Vector2d pos, double r, Vector2d vel, double pv, double k, double l0, double n, Color c) {
	Ball b;
	b.pv = pv;
	b.k = k*n;
	b.color = c;
	b.l0 = l0;
	for (int i = 0; i < n; i++) {
		b.points.push_back(Body(pos+geom::direction(2 * M_PI*i / n)*r, vel, 1));
	}
	b.pv = b.k * 2 * M_PI *b.square()*pv;
	balls.push_back(b);
}