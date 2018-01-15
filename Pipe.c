#include "Pipe.h"
bool pipeScored(Pipe* p, Bird* b, Score* s){
    if(p->mScored == false && p->mPosX + p->mWidth < b->mPos.x){
        s->mAcctualScore++;
        p->mScored = true;
    }
}
void pipeUpdate(Pipe* p, double dTime, unsigned modifier)
{
    if (p->mActive == true) {
        p->mPosX -= p->mVelocity * dTime;
        p->mBoundsBottom.x = p->mPosX;
        p->mBoundsTop.x = p->mPosX;
        if (p->mPosX + p->mWidth < 0) {
            p->mActive = false;
            pipeRandomizeSpace(p, modifier);
        }
    }
}
void pipeConstruct(Pipe* p, unsigned modifier)
{
    p->mWidth = 70;
    p->mVelocity = 125;
    p->mHeight = 400;
    p->mActive = false;
    p->mFreeSpace = 200;
    pipeRandomizeSpace(p, modifier);
}
void pipeRandomizeSpace(Pipe* p, unsigned modifier)
{
    p->mPosX = SCREEN_WIDTH;
    p->mScored = false;
    //Generate center point for empty space
    //Between 100 and screen_height -100
    srand(time(NULL) * modifier);
    int center = rand() % (SCREEN_HEIGHT - 200) + 100;
    p->mBottomHeight = SCREEN_HEIGHT - (center + p->mFreeSpace / 2);
    p->mTopHeight = center - p->mFreeSpace / 2;

    p->mBoundsBottom.x = p->mPosX;
    p->mBoundsBottom.y = center + p->mFreeSpace / 2;
    p->mBoundsBottom.w = p->mWidth;
    p->mBoundsBottom.h = p->mHeight;

    p->mBoundsTop.x = p->mPosX;
    p->mBoundsTop.y = center - p->mFreeSpace / 2 - p->mHeight;
    // p->mBoundsTop.y = SCREEN_HEIGHT - (p->mBoundsBottom.y + p->mFreeSpace + p->mTopHeight);
    p->mBoundsTop.w = p->mWidth;
    p->mBoundsTop.h = p->mHeight;
}

bool pipeColides(Pipe* p, Bird* b)
{
    if ((b->mBounds.x + b->mBounds.w >= p->mBoundsTop.x && b->mBounds.x <= p->mBoundsTop.x + p->mBoundsTop.w
            || b->mBounds.x + b->mBounds.w >= p->mBoundsBottom.x && b->mBounds.x <= p->mBoundsBottom.x + p->mBoundsBottom.w)
        && (b->mBounds.y + b->mBounds.h >= p->mBoundsTop.y && b->mBounds.y <= p->mBoundsTop.y + p->mBoundsTop.h
               || b->mBounds.y + b->mBounds.h >= p->mBoundsBottom.y && b->mBounds.y <= p->mBoundsBottom.y + p->mBoundsBottom.h)) {
        SDL_SetTextureColorMod(b->mSprite, 0xFF, 0x00, 0x00);
        return true;
    }
    return false;
}