#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <curl/curl.h>
#include "json/cJSON.h"
typedef struct {
    unsigned mAcctualScore;
    SDL_Surface* mScoreSurface;
    SDL_Rect mBounds;
    TTF_Font* mFont;
    SDL_Color mTextColor;
    FILE* mCachedScores;
} Score;

void scoreUpdate(Score* s);
void scoreConstruct(Score* s);
void scoreSaveToAFile(Score* s, FILE* f);
#endif