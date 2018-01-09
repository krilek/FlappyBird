#include "Bird.h"
void birdUpdate(Bird *b, double dTime){
    b->mVelocity += b->mGravity;
    b->mSinceLastJump += dTime;
    // if(b->mVelocity < -50) b->mVelocity = -50;
    // if(b->mVelocity > 50) b->mVelocity = 50;
    // b->mVelocity *= 0.6;
    if(b->mJumped && b->mSinceLastJump > 0.2){
        b->mVelocity += b->mLift;
        b->mSinceLastJump = 0;
        b->mJumped = false;
    }
    printf("VEL: %f\n", b->mVelocity);

    double dY = b->mVelocity * dTime;
	b->mPos.y += dY;
	if(b->mPos.y + b->mGBounds.h > SCREEN_HEIGHT){
        b->mPos.y = SCREEN_HEIGHT - b->mGBounds.h;
        b->mVelocity = 0;
    }
	if(b->mPos.y < 0){
         b->mPos.y = 0;
         b->mVelocity = 0;
    }
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
    b->mGBounds.w = 50;
    b->mGBounds.h = 50;
	b->mBounds.x = b->mPos.x;
	b->mBounds.y = b->mPos.y;
    b->mGravity = 0.9;
    b->mVelocity = 0;
    b->mLift = -800;
    b->mJumped = false;
}