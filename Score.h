#ifndef SCORE_H
#define SCORE_H
#define MAX_NICKNAME_LENGTH 50
#define MAX_SCORE_DIGITS 6+1
#include "dep/include/SDL2/SDL.h"
#include "dep/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dep/include/curl/curl.h"
#include "Text.h"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
typedef struct {
    char mPlayerName[MAX_NICKNAME_LENGTH];
    unsigned mAcctualScore;
    Text mScoreText;
    bool mScoreSaved;
    FILE* mCachedScores;
} Score;

void scoreUpdate(Score* s);
void scoreConstruct(Score* s);
void scoreSaveToAFile(Score* s, FILE* f);
bool scoreReplaceInFile(Score* s, FILE* f, size_t lenOfScore);
bool scoreFindInFile(Score* s, FILE* f);
bool scoreAddNewToFile(Score* s, FILE* f);
size_t parseLine(char* line, char* name, char* score, char* currentPlayerNick);
bool uploadScoreToServer(Score* s);
bool scoreGetHighscores(Score* s, FILE* f);
#endif