#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
const int MAX_TEXT_LENGTH;
typedef struct {
    char mText[200];
    SDL_Surface* mTextSurface;
    SDL_Rect mBounds;
    TTF_Font* mFont;
    SDL_Color mTextColor;
} Text;

void textSetText(Text* t);
void textConstruct(Text* t, char txt[200]);
#endif