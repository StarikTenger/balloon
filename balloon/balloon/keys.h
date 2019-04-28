#pragma once
#include <SDL.h>

enum Commands {
	NONE,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	SPACE,
	SHIFT,
	W, A, S, D,
	E, Q, P, R, F
};


inline Commands getKey(SDL_Keycode key) {
	switch (key) {
	case SDLK_RIGHT:
		return RIGHT;
	case SDLK_LEFT:
		return LEFT;
	case SDLK_DOWN:
		return DOWN;
	case SDLK_UP:
		return UP;
	case SDLK_SPACE:
		return SPACE;
	case SDLK_LSHIFT:
		return SHIFT;

		//WASD
	case SDLK_w:
		return W;
	case SDLK_a:
		return A;
	case SDLK_s:
		return S;
	case SDLK_d:
		return D;
		//symbols
	case SDLK_r:
		return R;
	case SDLK_f:
		return F;
	case SDLK_q:
		return Q;
	case SDLK_e:
		return E;
	}
	return NONE;
}
