#include "Bird.h"
void birdUpdate(Bird *b, double dTime){
    b->mSinceLastJump += dTime;
    if(b->mJumped && b->mSinceLastJump > 1){
        b->mVelocity += b->mLift;
        b->mJumped = false;
        b->mSinceLastJump = 0;
    }
    b->mVelocity += b->mGravity;
    // if(b->mVelocity < -50) b->mVelocity = -50;
    // if(b->mVelocity > 50) b->mVelocity = 50;
    printf("%f\n", b->mVelocity);
    b->mVelocity *= 0.9;
    double dY = b->mVelocity * dTime;
	b->mPos.y += dY;
	if(b->mPos.y > SCREEN_HEIGHT - b->mBounds.h / 2) b->mPos.y -= dY;
	// if(b->mPos.y < 0) b->mPos.y += dS;
	// b->mPos.x += dS;
	// if(b->mPos.x > SCREEN_WIDTH - b->mBounds.w) b->mPos.x -= dS;
	

	b->mBounds.y = (int)(b->mPos.y);
	b->mBounds.x = (int)(b->mPos.x);
}

void birdJump(Bird *b){
    b->mJumped = true;
    // b->mVelocity += b->mLift;
}

void birdConstruct(Bird *b){
    b->mBounds.w = 50;
	b->mBounds.h = 50;
	b->mPos.x = 50;
	b->mPos.y = SCREEN_HEIGHT / 2 - b->mBounds.h / 2 ;
	b->mBounds.x = b->mPos.x;
	b->mBounds.y = b->mPos.y;
	b->mSpeed = 100;
    b->mGravity = 20;
    b->mVelocity = 0;
    b->mLift = -400;
    b->mJumped = false;
}