#include "Bird.h"
bool birdUpdate(Bird* b, double dTime)
{
    //Apply gravity to velocity pulling towards bottom
    b->mVelocity += b->mGravity;
    b->mSinceLastJump += dTime;
    if (b->mJumped && b->mSinceLastJump > 0.2) {
        //If player jumped, subtract from user velocity
        b->mVelocity += b->mLift;
        b->mSinceLastJump = 0;
        b->mJumped = false;
    }
    //Limit speed of falling
    b->mVelocity = limit(b->mVelocity, 400);
    b->mVelocity = limit(b->mVelocity, -500);

    double dY = b->mVelocity * dTime;
    b->mPos.y += dY;
    //When out of window return collision
    if (b->mPos.y + b->mBounds.h / 2 > SCREEN_HEIGHT) {
        b->mPos.y = SCREEN_HEIGHT - b->mBounds.h / 2;
        b->mVelocity = limit(b->mVelocity, 0);
        return true;
    }
    if (b->mPos.y + b->mBounds.h / 2 < 0) {
        b->mPos.y = 0 - (b->mBounds.h / 2);
        b->mVelocity = limit(b->mVelocity, 0);
        return true;
    }
    //Update boundaries
    b->mBounds.y = (int)(b->mPos.y);
    b->mBounds.x = (int)(b->mPos.x);
    return false;
}

void birdJump(Bird* b)
{
    //Just change flag
    //Should be removed in future
    b->mJumped = true;
}

void birdConstruct(Bird* b)
{
    b->mBounds.w = 50;
    b->mBounds.h = 50;
    b->mPos.x = 50;
    b->mPos.y = SCREEN_HEIGHT / 2 - b->mBounds.h / 2;
    b->mBounds.x = b->mPos.x;
    b->mBounds.y = b->mPos.y;
    b->mGravity = 0.7;
    b->mVelocity = 0;
    b->mLift = -800;
    b->mJumped = false;
}