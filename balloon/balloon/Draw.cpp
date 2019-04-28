#include "Draw.h"
#include "SDL.h"
#include <string>
#include <SDL_image.h>
#include <iostream>
Draw::Draw(SDL_Renderer * rend) {
	render = rend;
}

Draw::Draw(int width, int height, const char * name) {
	SDL_Window *win = SDL_CreateWindow(name, 20, 50, width, height, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	*this = Draw(render);
	//render = 
}

SDL_Texture* Draw::loadImage(std::string path)
{

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

typedef int32_t s32;

void DrawCircle(SDL_Renderer *Renderer, s32 _x, s32 _y, s32 radius)
{
	s32 x = radius - 1;
	s32 y = 0;
	s32 tx = 1;
	s32 ty = 1;
	s32 err = tx - (radius << 1); // shifting bits left by 1 effectively
								  // doubles the value. == tx - diameter
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
		SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
		SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
		SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
		SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
		SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
		SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
		SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		else if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}

void Draw::drawImage(SDL_Texture *tex, double x, double y, double width, double height, double angle) {
	angle = angle / M_PI * 180;

	SDL_Rect pos;
	pos.x = x - width / 2;
	pos.y = y - height / 2;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

	pos.w = width;
	pos.h = height;

	SDL_RenderCopyEx(render,
		tex,
		NULL,
		&pos,
		angle,
		NULL,
		SDL_FLIP_NONE);
}
void Draw::drawLine(double x1, double y1, double x2, double y2, Color color) {
	//SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_ADD);
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(render, x1, y1, x2, y2);
}
void Draw::drawStrokeRect(double x, double y, double width, double height, Color color) {
	//SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_ADD);
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	SDL_RenderDrawRect(render, rect);
	delete rect;
}
void Draw::drawFillRect(double x, double y, double width, double height, Color color) {
	//SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	SDL_RenderFillRect(render, rect);
	delete rect;
}
void Draw::drawCircle(double x, double y, double r, Color color) {
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
	DrawCircle(render, x, y, r);
}

void Draw::clear() {
	SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(render);
}
void Draw::fill(Color c) {
	SDL_SetRenderDrawColor(render, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(render);
}
void Draw::push() {
	SDL_RenderPresent(render);
}