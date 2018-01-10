#ifndef PIPE_H
#define PIPE_H
#include <SDL2/SDL.h>

typedef struct {
    unsigned mTopHeight;
    unsigned mBottomHeight;
    unsigned mFreeSpace;
    unsigned mWidth;
    unsigned mVelocity;
    SDL_Rect mBounds;
    bool mActive;
    SDL_Surface* mSpriteTop;
    SDL_Surface* mSpriteBottom;
} Pipe;

#endif