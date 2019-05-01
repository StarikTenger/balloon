#include "SDL.h"
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>

#include "getMilliCount.h"
#include "keys.h"
#include "Draw.h"
#include "DrawSystem.h"
#include "random.h"
#include "System.h"
#include "geometry.h"


int main(int, char**){
	random::start();
	System sys;
	sys.dt = 0.003;
	sys.frictionK = 0.1;
	sys.g = {0, 10};
	sys.border = {500, 700};

	double side = 120;
	sys.walls.push_back(Wall({
		Vector2d(0, sys.border.y - side),
		Vector2d(side, sys.border.y)
		}));
	sys.walls.push_back(Wall({
		Vector2d(sys.border.x, sys.border.y - side),
		Vector2d(sys.border.x-side, sys.border.y)
		}));

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 6; y++) {
			sys.bubble(
				Vector2d(60 + x * 100, 60 + y * 100 ),
				50,
				{ 0, 0 },
				4,
				0.002,
				0,
				50,
				Color(random::intRandom(190, 255), random::intRandom(190, 255), random::intRandom(190, 255)));
			sys.balls.back().pv *= 2;
		}
	}
	/*sys.bubble(
		Vector2d( 250, 500), //pos
		100, //r 
		{ 0, 0 }, //vel
		500, //m
		1, //k
		0, //l0
		50, //k
		Color(255, 255, 255));
	sys.balls.back().pv *= 1;*/
	//sys.balls.back().points[0].m = 100;
	//sys.balls.back().points[25].m = 100;

	sys.pressure = 0;
	

	int size = 500;
	Draw draw(sys.border.x, sys.border.y, "This is a window");

	DrawSystem drawSys(&draw);
	
	//time
	int dt = 0;
	int timePrev = getMilliCount();

	bool stop = 0;
	while (!stop) {
		int timeMs = getMilliCount();
		if (timeMs - timePrev > dt) {
			timePrev = timeMs;

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					stop = 1;
					break;
				case SDL_KEYDOWN:
					if (getKey(event.key.keysym.sym) == SPACE) {
						stop = 1;
					}
					break;
				case SDL_KEYUP:
					break;
				}

			}
			for(int i=0; i<30; i++)
				sys.step();
			drawSys.draw(sys);
			
		}
	}
	return 0;
}