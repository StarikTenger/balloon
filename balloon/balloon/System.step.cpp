#include "System.h"
#include "geometry.h"
#include "random.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace geom;
using namespace random;



void System::step() {
	//deleting defective balls
	for (auto& ball : balls) {
		for (int i = 0; i < ball.points.size() - 1; i++) {
			if (distance(ball.points[i].pos, ball.points[i + 1].pos) > 150) 
			//if (geom::distance({}, ball.points[i].vel) > 100)
				ball.defect = 1;
			
		}
	}
	for (int i = 0; i < balls.size(); i++) {
		if (balls[i].defect) {
			balls.erase(balls.begin() + i);
			i--;
		}
	}

	//calculating
	for (auto& ball : balls) {
		ball.circle();
		int l = ball.points.size();
		double v = ball.square();

		for (int i = 0; i < l; i++) {
			int a = (i + 1 + l) % l;
			int b = (i - 1 + l) % l;
			Vector2d f(0, 0);

			//spring
			double k = ball.k*ball.points.size();
			f += geom::direction(ball.points[i].pos, ball.points[a].pos)*(geom::distance(ball.points[i].pos, ball.points[a].pos) - ball.l0)*k *(-1);
			f += geom::direction(ball.points[i].pos, ball.points[b].pos)*(geom::distance(ball.points[i].pos, ball.points[b].pos) - ball.l0)*k *(-1);

			//gas pressure
			f += geom::rotate(
				(ball.points[a].pos - ball.points[i].pos) * (ball.pv / v - pressure) * (-1)*0.5,
				M_PI / 2
			);
			f += geom::rotate(
				(ball.points[b].pos - ball.points[i].pos) * (ball.pv / v - pressure) * (-1)*0.5,
				-M_PI / 2
			);

			//friction
			f += ball.points[i].vel*frictionK*(-1);

			//acceleration
			ball.points[i].vel += f / ball.points[i].m * dt;
		}
	}

	//gravity
	for (auto& ball : balls) {
		for (auto& p : ball.points) {
			p.vel += g * dt;
		}
	}

	//border collision
	for (auto& ball : balls) {
		for (auto& p : ball.points) {
			if (p.pos.x < 0 && p.vel.x < 0) {
				p.vel.x *= -1;
			}
			if (p.pos.x > border.x && p.vel.x > 0) {
				p.vel.x *= -1;
			}
			if (p.pos.y < 0 && p.vel.y < 0) {
				p.vel.y *= -1;
			}
			if (p.pos.y > border.y && p.vel.y > 0) {
				p.vel.y *= -1;
			}
		}
	}

	//ball collision
	for (int i = 0; i < balls.size(); i++) {
		for (int j = 0; j < balls.size(); j++) {
			if (i == j)
				continue;
			if(balls[i].r + balls[j].r > geom::distance(balls[i].centre, balls[j].centre))
			collision(balls[i], balls[j]);
		}
	}

	//wall collision
	for (auto& ball : balls) {
		for (auto& p : ball.points) {
			checkWall(p);
		}
	}



	//movement
	for (auto& ball : balls) {
		for (auto& p : ball.points) {
			p.posPrev = p.pos;
			p.pos += p.vel*dt;
		}
	}


	time += dt;
}