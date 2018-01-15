#include "Text.h"
const int MAX_TEXT_LENGTH = 200;
void textSetText(Text* t){

}
void textConstruct(Text* t, char txt[200]){
    strcpy(t->mText, txt);
    t->mBounds.w = 50;
    t->mBounds.h = 50;
    t->mBounds.x = SCREEN_WIDTH / 2 - t->mBounds.w / 2;
    t->mBounds.y = 50;
    t->mTextColor.r = 255;
    t->mTextColor.g = 255;
    t->mTextColor.b = 255;
    t->mTextColor.a = 255;
}