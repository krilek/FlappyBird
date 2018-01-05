#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    //The window we'll be rendering to
    SDL_Window* mWindow;
        
    //The surface contained by the window
    SDL_Surface* mWindowSurface;
}Engine;

//Starts up SDL and creates window
bool init(Engine *game);

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

#endif