#include "Text.h"
const int MAX_TEXT_LENGTH = 200;
void textUpdate(Text* t, TTF_Font* f, unsigned posY)
{
    //Get rid of existing surface
    if (t->mTextSurface != NULL) {
        SDL_FreeSurface(t->mTextSurface);
        t->mTextSurface = NULL;
    }
    t->mTextSurface = TTF_RenderText_Blended_Wrapped(f, t->mText, t->mTextColor, 640);
    if (t->mTextSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }else{
        t->mBounds.w = t->mTextSurface->w;
        t->mBounds.h = t->mTextSurface->h;
    }
    //Update width of a surface
    //TTF_SizeText(f, t->mText, &t->mBounds.w, &t->mBounds.h);
    //Update position of a surface

    t->mBounds.x = SCREEN_WIDTH / 2 - t->mBounds.w / 2;
    t->mBounds.y = posY;
}
bool textConstruct(Text* t, char txt[200], TTF_Font* f){
    strcpy(t->mText, txt);
    t->mTextColor.r = 255;
    t->mTextColor.g = 255;
    t->mTextColor.b = 255;
    t->mTextColor.a = 255;
    t->mTextSurface = TTF_RenderText_Blended_Wrapped(f, t->mText, t->mTextColor, 640);
    if (t->mTextSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }else{
        t->mBounds.w = t->mTextSurface->w;
        t->mBounds.h = t->mTextSurface->h;
    }
    
    t->mBounds.x = 0;
    t->mBounds.y = 0;
    return true;
}