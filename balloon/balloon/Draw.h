#pragma once
#include "SDL.h"
#include <string>
#include <SDL_image.h>
#include "Color.h"

class Draw {
private:

public:
	SDL_Renderer * render;
	Draw() {}
	Draw(int width, int height, const char *);
	Draw(SDL_Renderer* rend);
	SDL_Texture* loadImage(std::string path);
	void drawImage(SDL_Texture *tex, double x, double y, double width, double height, double angle);
	void drawLine(double x1, double y1, double x2, double y2, Color color);
	void drawStrokeRect(double x, double y, double width, double height, Color color);
	void drawFillRect(double x, double y, double width, double height, Color color);
	void drawCircle(double x, double y, double r, Color color);
	void clear();
	void fill(Color c);
	void push();
};

