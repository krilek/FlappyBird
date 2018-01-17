#include "Engine.h"
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int PIPES_AMOUNT = 5;

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
                    e->mState = START;
                    //Download newest highscores
                    scoreGetHighscores(&e->score, e->score.mCachedScores);
                    birdConstruct(&e->bird);
                    e->mFont = TTF_OpenFont("graphics/fBirdFont.TTF", 24);
                    if (e->mFont == NULL) {
                        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                        success = false;
                    } else {
                        if (!(scoreConstruct(&e->score, e->mFont) && textConstruct(&e->gameOver, "Oh snap! You lose!\nPress Enter to start again!\nPress Escape to exit!", e->mFont) && textConstruct(&e->startGame, "Flappy Bird\nCreated by Krilek\nPress Enter to start game", e->mFont))) {
                            success = false;
                        }
                            textUpdate(&e->gameOver, e->mFont, SCREEN_HEIGHT/2);
                    }
                    for (int i = 0; i < PIPES_AMOUNT; i++) {
                        pipeConstruct(&e->pipes[i], i + 1);
                    }
                }
            }
        }
    }
    return success;
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
    e->mPipeSprite = loadTexture("graphics/pipe.png", e);
    //Load pipe image
    if (e->mPipeSprite == NULL) {
        success = false;
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
                if(e->mState == GAME_OVER){
                    e->mState = QUITTING;
                }
                break;
            case SDLK_RETURN:
                if(e->mState == START){
                    e->mState = PLAYING;
                }
                if(e->mState == GAME_OVER){
                    resetGame(e);
                    e->mState = PLAYING;
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

void updateGame(Engine* e)
{
    // Calculate delta time
    e->mTimeLast = e->mTimeNow;
    e->mTimeNow = SDL_GetPerformanceCounter();
    double deltaTime = ((e->mTimeNow - e->mTimeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) / 1000;
    e->mSecondsSinceStart += deltaTime;
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
        if (birdUpdate(&e->bird, deltaTime)) {
            e->mState = GAME_OVER;
        }

        for (unsigned i = 0; i < PIPES_AMOUNT; i++) {
            pipeUpdate(&e->pipes[i], deltaTime, i + 1);
            if (pipeColides(&e->pipes[i], &e->bird)) {
                e->mState = GAME_OVER;
            }
            pipeScored(&e->pipes[i], &e->bird, &e->score);
        }
        scoreUpdate(&e->score, e->mFont);
    } else if (e->mState == GAME_OVER) {
        //Update process highscore
        if (e->score.mAcctualScore > e->score.mCurrentHighScore) {
            e->score.mCurrentHighScore = e->score.mAcctualScore;
        }
        //This is not nessesary because text doesn't change but deadline is comming
        // textUpdate(&e->gameOver, e->mFont, SCREEN_HEIGHT/2);
    }
}
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
void renderFrame(Engine* e)
{
    //Clear the screen
    SDL_RenderClear(e->mRenderer);
    if (e->mState == PLAYING || e->mState == GAME_OVER) {
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
        if (e->mState != GAME_OVER) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(e->mRenderer, e->score.mScoreText.mTextSurface);
            if (textTexture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            } else {
                SDL_RenderCopy(e->mRenderer, textTexture, NULL, &e->score.mScoreText.mBounds);
                SDL_DestroyTexture(textTexture);
            }
        } else {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(e->mRenderer, e->gameOver.mTextSurface);
            if (textTexture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            } else {
                SDL_RenderCopy(e->mRenderer, textTexture, NULL, &e->gameOver.mBounds);
                SDL_DestroyTexture(textTexture);
            }
        }
    } else if (e->mState == START) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(e->mRenderer, e->startGame.mTextSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_RenderCopy(e->mRenderer, textTexture, NULL, &e->startGame.mBounds);
            SDL_DestroyTexture(textTexture);
        }
    }
    // Update the renderer
    SDL_RenderPresent(e->mRenderer);
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
    TTF_CloseFont(e->mFont);
    e->mFont = NULL;
    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void resetGame(Engine* e){
    birdConstruct(&e->bird);
    e->mTimeLast = 0;
    e->mTimeNow = SDL_GetPerformanceCounter();
    e->mSecondsSinceStart = 0.0;
    e->mWhichPipeToStart = 0;
    e->mPipeGenerationTimeLast = 0;
    for (int i = 0; i < PIPES_AMOUNT; i++) {
        pipeConstruct(&e->pipes[i], i + 1);
    }
    scoreConstruct(&e->score, e->mFont);
}