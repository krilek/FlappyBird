#ifndef PIPE_H
#define PIPE_H
#include "Bird.h"
#include "Score.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct {
    unsigned mTopHeight;
    unsigned mBottomHeight;
    unsigned mFreeSpace;
    unsigned mWidth;
    unsigned mHeight;
    float mPosX;
    unsigned mVelocity;
    SDL_Rect mBoundsTop;
    SDL_Rect mBoundsBottom;
    bool mActive;
    bool mScored;
} Pipe;
bool pipeScored(Pipe* p, Bird* b, Score* s);
//void pipeShow(Pipe* p);
void pipeConstruct(Pipe* p, unsigned modifier);
void pipeUpdate(Pipe* p, double dTime, unsigned modifier);
#endif