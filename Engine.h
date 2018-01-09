#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Bird.h"
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

typedef struct{
	SDL_Surface *mPipeSprite;
	SDL_Window *gWindow;
	SDL_Surface *gScreenSurface;
	bool mQuit;
	Bird bird;
	long long unsigned mTimeNow;
	long long unsigned mTimeLast;
}Engine;

#endif