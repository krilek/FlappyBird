#ifndef ENGINE_H
#define ENGINE_H
#include "Bird.h"
#include "Pipe.h"
#include "Score.h"
#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
const int SCREEN_HEIGHT;
const int SCREEN_WIDTH;
const int PIPES_AMOUNT;
typedef enum g_state{
    START,
    PLAYING,
    PAUSED,
    GAME_OVER,
    QUITTING
} GAME_STATE;

typedef struct {
    SDL_Texture* mPipeSprite;
    SDL_Surface* TESTING;
    SDL_Renderer* mRenderer;
    SDL_Window* gWindow;
    bool mQuit;
    GAME_STATE mState;
    Bird bird;
    Pipe pipes[50];
    Score score;
    Text gameOver;
    Text startGame;
    Text highScores;
    long long unsigned mTimeNow;
    long long unsigned mTimeLast;
    double mSecondsSinceStart;
    unsigned mPipeGenerationTimeLast;
    size_t mWhichPipeToStart;
} Engine;

double limit(double x, double limit);
bool loadMedia(Engine* e);
bool initGame(Engine* e);
// Frees media and shuts down SDL
void closeGame(Engine* e);
void handleInput(Engine* e, SDL_Event* event);
void updateGame(Engine* e);
void renderFrame(Engine* e);
// Loads image to gpu memory
SDL_Texture* loadTexture(char* path, Engine* e);


#endif