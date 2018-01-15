#include "Score.h"

void scoreUpdate(Score* s)
{
    printf("%d\n", s->mAcctualScore);
    //Get rid of existing surface
    if(s->mScoreText.mTextSurface != NULL){
        SDL_FreeSurface(s->mScoreText.mTextSurface);
        s->mScoreText.mTextSurface = NULL;
    }
    char scoreText[10];
    sprintf(scoreText, "%d", s->mAcctualScore);
    s->mScoreText.mTextSurface = TTF_RenderText_Solid(s->mScoreText.mFont, scoreText, s->mScoreText.mTextColor);
    //Update width of a surface
    TTF_SizeText(s->mScoreText.mFont, scoreText, &s->mScoreText.mBounds.w, &s->mScoreText.mBounds.h);
    //Update position of a surface
    s->mScoreText.mBounds.x = SCREEN_WIDTH / 2 - s->mScoreText.mBounds.w / 2;
    if(s->mScoreText.mTextSurface == NULL){
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
void scoreConstruct(Score* s)
{
    strcpy(s->mPlayerName, "Krilek");
    s->mAcctualScore = 0;
    s->mScoreText.mBounds.w = 50;
    s->mScoreText.mBounds.h = 50;
    s->mScoreText.mBounds.x = SCREEN_WIDTH / 2 - s->mScoreText.mBounds.w / 2;
    s->mScoreText.mBounds.y = 50;
    s->mScoreText.mTextColor.r = 255;
    s->mScoreText.mTextColor.g = 255;
    s->mScoreText.mTextColor.b = 255;
    s->mScoreText.mTextColor.a = 255;
    s->mScoreSaved = false;
    textConstruct(&s->mScoreText, "0");
}
void scoreSaveToAFile(Score* s, FILE* f){
    char output[200];
    sprintf(output, "%s=%d", s->mPlayerName, s->mAcctualScore);
    for(int i=0;i<strlen(output);i++){
        putc(output[i], f);
    }
    s->mScoreSaved = true;
    //TODO: ZRÓB CZYSZCZENIE DO KOŃCA LINII
    // printf("%s", output);
}