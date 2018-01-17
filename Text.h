#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
const int MAX_TEXT_LENGTH;
typedef struct {
    char mText[200];
    SDL_Surface* mTextSurface;
    SDL_Rect mBounds;
    SDL_Color mTextColor;
} Text;

void textSetText(Text* t);
bool textConstruct(Text* t, char txt[200], TTF_Font* f);
void textUpdate(Text* t, TTF_Font* f, unsigned posY);
#endif