#ifndef BIRD_H
#define BIRD_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

typedef struct {
    float x;
    float y;
} Vector2f;

typedef struct {
    SDL_Rect mBounds;
    SDL_Rect mGBounds;
    Vector2f mPos;
    SDL_Surface* mSprite;
    bool mJumped;
    float mSpeed;
    float mVelocity;
    float mGravity;
    float mLift;
    float mSinceLastJump;
} Bird;

void birdUpdate(Bird* b, double dTime);
void birdJump(Bird* b);
void birdConstruct(Bird* b);
#endif