#include "Engine.h"
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int PIPES_AMOUNT = 5;
double limit(double x, double limit)
{
    if (x < 0 && limit < 0 && x < limit)
        return limit;
    if (x > 0 && limit > 0 && x > limit)
        return limit;
    if (limit == 0)
        return limit;
    return x;
}

bool loadMedia(Engine* e)
{
    // Loading success flag
    bool success = true;
    // Load bird image
    e->bird.mSprite = loadTexture("graphics/fbird.png", e);
    if (e->bird.mSprite == NULL) {
        success = false;
    }
    e->score.mScoreText.mFont = TTF_OpenFont("graphics/fBirdFont.TTF", 24);
    if (e->score.mScoreText.mFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    } else {
        SDL_Color tempColor;
        tempColor.r = 255;
        tempColor.g = 255;
        tempColor.b = 255;
        tempColor.a = 255;
        e->score.mScoreText.mTextSurface = TTF_RenderText_Solid(e->score.mScoreText.mFont, "0", tempColor);
        if (e->score.mScoreText.mTextSurface == NULL) {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
        e->score.mScoreText.mBounds.w = e->score.mScoreText.mTextSurface->w;
        e->score.mScoreText.mBounds.h = e->score.mScoreText.mTextSurface->h;
    }

    e->mPipeSprite = loadTexture("graphics/pipe.png", e);
    //Load pipe image
    if (e->mPipeSprite == NULL) {
        success = false;
    }
    return success;
}

SDL_Texture* loadTexture(char* path, Engine* e)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* tempSurface = IMG_Load(path);
    if (tempSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path,
            IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(e->mRenderer, tempSurface);
        if (texture == NULL) {
            printf("Unable to create texture from surface: %s! SDL_image Error: %s\n", path, IMG_GetError());
        }
        SDL_FreeSurface(tempSurface);
    }
    return texture;
}
void closeGame(Engine* e)
{
    //Deallocate all textures
    SDL_DestroyTexture(e->bird.mSprite);
    e->bird.mSprite = NULL;
    SDL_DestroyTexture(e->mPipeSprite);
    e->mPipeSprite = NULL;
    //Deallocate renderer
    SDL_DestroyRenderer(e->mRenderer);
    e->mRenderer = NULL;
    // Destroy window
    SDL_DestroyWindow(e->gWindow);
    e->gWindow = NULL;
    // Deallocate font
    TTF_CloseFont(e->score.mScoreText.mFont);
    e->score.mScoreText.mFont = NULL;
    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void updateGame(Engine* e)
{
    // Calculate delta time
    e->mTimeLast = e->mTimeNow;
    e->mTimeNow = SDL_GetPerformanceCounter();
    double deltaTime = ((e->mTimeNow - e->mTimeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) / 1000;
    e->mSecondsSinceStart += deltaTime;
    //
    // printf("Time SDL: %d, Time engine: %f Pipe: %d\n", SDL_GetTicks(), e->mSecondsSinceStart, e->mWhichPipeToStart);
    //
    unsigned currentTime = SDL_GetTicks();
    if (e->mState == PLAYING) {
        //TODO: Fix all timing + pausing problems
        if (e->mWhichPipeToStart < PIPES_AMOUNT && currentTime > e->mPipeGenerationTimeLast + 2000) {
            if (e->pipes[e->mWhichPipeToStart].mActive == false) {
                e->pipes[e->mWhichPipeToStart].mActive = true;
                e->mWhichPipeToStart++;
                e->mPipeGenerationTimeLast = currentTime;
            }
            e->mWhichPipeToStart %= PIPES_AMOUNT;
        }
        // Update bird
        if(birdUpdate(&e->bird, deltaTime)){
            e->mState = GAME_OVER;
        }

        for (unsigned i = 0; i < PIPES_AMOUNT; i++) {
            pipeUpdate(&e->pipes[i], deltaTime, i + 1);
            if(pipeColides(&e->pipes[i], &e->bird)){
                e->mState = GAME_OVER;
            }
            pipeScored(&e->pipes[i], &e->bird, &e->score);
        }
        scoreUpdate(&e->score);
    }else if(e->mState == GAME_OVER){
        if(e->score.mScoreSaved == false){
            scoreSaveToAFile(&e->score, e->score.mCachedScores);
        }
    }
}

void renderFrame(Engine* e)
{
    //Clear the screen
    SDL_RenderClear(e->mRenderer);
    //Copy pipes to a renderer
    for (int i = 0; i < PIPES_AMOUNT; i++) {
        if (e->pipes[i].mActive) {
            SDL_RenderCopyEx(e->mRenderer, e->mPipeSprite, NULL, &e->pipes[i].mBoundsTop, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(e->mRenderer, e->mPipeSprite, NULL, &e->pipes[i].mBoundsBottom, 0, NULL, SDL_FLIP_VERTICAL);
        }
    }

    //Copy bird to a renderer
    SDL_RenderCopy(e->mRenderer, e->bird.mSprite, NULL, &e->bird.mBounds);
    SDL_SetTextureColorMod(e->bird.mSprite, 0xFF, 0xFF, 0xFF);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(e->mRenderer, e->score.mScoreText.mTextSurface);
    if (textTexture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    } else {
        SDL_RenderCopy(e->mRenderer, textTexture, NULL, &e->score.mScoreText.mBounds);
        SDL_DestroyTexture(textTexture);
    }
    // Update the renderer
    SDL_RenderPresent(e->mRenderer);
}

bool initGame(Engine* e)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        e->gWindow = SDL_CreateWindow("FlappyBird", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (e->gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            e->mRenderer = SDL_CreateRenderer(e->gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (e->mRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                if (TTF_Init() == -1) {
                    printf("TTF_SDL could not initialize: TTF_Error: %s\n", TTF_GetError());
                    success = false;
                } else {

                    SDL_SetRenderDrawColor(e->mRenderer, 0x00, 0x00, 0x00, 0x00);
                    e->mTimeLast = 0;
                    e->mTimeNow = SDL_GetPerformanceCounter();
                    e->mSecondsSinceStart = 0.0;
                    e->mWhichPipeToStart = 0;
                    e->mPipeGenerationTimeLast = 0;
                    e->mState = PAUSED;
                    scoreConstruct(&e->score);
                    //Download newest highscores
                    scoreGetHighscores(&e->score, e->score.mCachedScores);
                    birdConstruct(&e->bird);
                    for (int i = 0; i < PIPES_AMOUNT; i++) {
                        pipeConstruct(&e->pipes[i], i + 1);
                    }
                }
            }
        }
    }
    return success;
}

void handleInput(Engine* e, SDL_Event* event)
{
    while (SDL_PollEvent(event) != 0) {
        // User requests quit
        if (event->type == SDL_QUIT) {
            e->mState = QUITTING;
        }
        // User presses a key
        else if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
            case SDLK_SPACE:
                birdJump(&e->bird);
                break;
            case SDLK_ESCAPE:
                if (e->mState == PAUSED) {
                    e->mState = PLAYING;
                } else {
                    e->mState = PAUSED;
                }
                break;
            }

        } else if (event->type == SDL_KEYUP) {
            switch (event->key.keysym.sym) {
            case SDLK_SPACE:
                e->bird.mJumped = false;
                break;
            }
        }
    }
}