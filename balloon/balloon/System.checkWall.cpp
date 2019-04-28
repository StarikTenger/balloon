#include "System.h"

void System::checkWall(Body& b) {
	for (auto& w : walls) {
		for (int i = 0; i < w.points.size() - 1; i++) {
			int j = i + 1;
			double angle = geom::angle(w.points[i] - w.points[j]);
			Vector2d dir = geom::direction(angle + M_PI / 2);
			if (geom::isCross(b.pos, b.posPrev, w.points[i], w.points[j])) {

				Vector2d vel1 = geom::rotate(b.vel, -angle);
				vel1.y *= -1;
				b.vel = geom::rotate(vel1, angle);
				b.pos = b.posPrev;
			}
		}
	}
}