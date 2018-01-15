#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <curl/curl.h>
#include "json/cJSON.h"
#include "Text.h"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct {
    char mPlayerName[20];
    unsigned mAcctualScore;
    Text mScoreText;
    FILE* mCachedScores;
} Score;

void scoreUpdate(Score* s);
void scoreConstruct(Score* s);
void scoreSaveToAFile(Score* s, FILE* f);
#endif