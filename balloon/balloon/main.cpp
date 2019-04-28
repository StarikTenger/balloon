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
	sys.dt = 0.001;
	sys.frictionK = 0.8;
	sys.g = {0, 10};
	sys.border = {500, 700};
	
	double k = 100;
	double l = 20;

	/*sys.walls.push_back(Wall({
		{ 50, 400-k },
		{ 250 - l, 400 },
		{ 250 - l, 420 },
		{ 50, 420 }
	}));

	sys.walls.push_back(Wall({
		{ 500-50, 400-k },
		{ 500 - (250 - l), 400 },
		{ 500 - (250 - l), 420 },
		{ 500 - 50, 420 }
	}));*/
	

	/*double h = 300;
	double l = 1;


	sys.walls.push_back(Wall({
		{ 0, sys.border.y },
		{ sys.border.x / 2 - l / 2, sys.border.y - h },
		{ sys.border.x / 2 + l / 2, sys.border.y - h },
		{ sys.border.x, sys.border.y },
	}));*/



	sys.bubble({ 160,440 }, 150, { 10, -10 }, 1, 0.01, 0, 50, Color(0, 255, 0));
	sys.bubble({ 300, 200 }, 120, { 0, 0 }, 1, 0.01, 0, 50, Color(255, 0, 0));
	sys.bubble({ 110, 110 }, 100, { 0, 0 }, 1, 1, 0, 50, Color(0, 0, 255));
	//sys.bubble({ 30, 60 }, 70, { 0, 0 }, 1, 0.05, 0, 50, Color(255, 255, 00));

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