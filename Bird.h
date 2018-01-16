#ifndef BIRD_H
#define BIRD_H
#include "dep/include/SDL2/SDL.h"
#include <stdbool.h>
#include <stdio.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
double limit(double x, double limit);
typedef struct {
    float x;
    float y;
} Vector2f;

typedef struct {
    SDL_Rect mBounds;
    Vector2f mPos;
    SDL_Texture* mSprite;
    bool mJumped;
    float mSpeed;
    float mVelocity;
    float mGravity;
    float mLift;
    float mSinceLastJump;
} Bird;

bool birdUpdate(Bird* b, double dTime);
void birdJump(Bird* b);
void birdConstruct(Bird* b);
#endif