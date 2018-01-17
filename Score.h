#ifndef SCORE_H
#define SCORE_H
#define MAX_NICKNAME_LENGTH 50
#define MAX_SCORE_DIGITS 6+1
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#include "Text.h"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct {
    char mPlayerName[MAX_NICKNAME_LENGTH];
    unsigned mAcctualScore;
    unsigned mCurrentHighScore;
    Text mScoreText;
    unsigned mPosY;
    FILE* mCachedScores;
} Score;

void scoreUpdate(Score* s, TTF_Font* f);
bool scoreConstruct(Score* s, TTF_Font* f);
void scoreSaveToAFile(Score* s, FILE* f);
bool scoreReplaceInFile(Score* s, FILE* f, size_t lenOfScore);
bool scoreFindInFile(Score* s, FILE* f);
bool scoreAddNewToFile(Score* s, FILE* f);
size_t parseLine(char* line, char* name, char* score, char* currentPlayerNick);
bool uploadScoreToServer(Score* s);
bool scoreGetHighscores(Score* s, FILE* f);
#endif