#include "Engine.h"

void scoreUpdate(Score* s)
{
    printf("%d\n", s->mAcctualScore);
    //Get rid of existing surface
    if(s->mScoreSurface != NULL){
        SDL_FreeSurface(s->mScoreSurface);
        s->mScoreSurface = NULL;
    }
    char scoreText[10];
    sprintf(scoreText, "%d", s->mAcctualScore);
    s->mScoreSurface = TTF_RenderText_Solid(s->mFont, scoreText, s->mTextColor);
    //Update width of a surface
    TTF_SizeText(s->mFont, scoreText, &s->mBounds.w, &s->mBounds.h);
    //Update position of a surface
    s->mBounds.x = SCREEN_WIDTH / 2 - s->mBounds.w / 2;
    if(s->mScoreSurface == NULL){
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
void scoreConstruct(Score* s)
{
    s->mAcctualScore = 0;
    s->mBounds.w = 50;
    s->mBounds.h = 50;
    s->mBounds.x = SCREEN_WIDTH / 2 - s->mBounds.w / 2;
    s->mBounds.y = 50;
    s->mTextColor.r = 255;
    s->mTextColor.g = 255;
    s->mTextColor.b = 255;
    s->mTextColor.a = 255;
}
void scoreSaveToAFile(Score* s, FILE* f){
       
}