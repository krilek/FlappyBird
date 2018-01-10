#ifndef ENGINE_H
#define ENGINE_H
#include "Bird.h"
#include "Pipe.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int PIPES_AMOUNT = 5;
typedef struct {
    SDL_Surface* mPipeSprite;
    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    bool mQuit;
    Bird bird;
    Pipe pipes[5];
    long long unsigned mTimeNow;
    long long unsigned mTimeLast;
} Engine;

#endif