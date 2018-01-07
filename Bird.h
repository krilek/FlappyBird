#ifndef BIRD_H
#define BIRD_H
#include "Engine.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct{
	SDL_Rect mBounds;
	Vector2f mPos;
	SDL_Surface *mSprite;
	bool mJumped;
	float mSpeed;
    float mVelocity;
    float mGravity;
    float mLift;
    float mSinceLastJump;
}Bird;

void birdUpdate(Bird *b, double dTime);
void birdJump(Bird *b);
void birdConstruct(Bird *b);
#endif