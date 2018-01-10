#include "FlappyBird.h"

Engine gameEngine;
bool loadMedia(Engine* e);
bool initGame(Engine* e);
// Frees media and shuts down SDL
void closeGame(Engine* e);
void updateGame(Engine* e);
void renderFrame(Engine* e);
// Loads image to gpu memory
SDL_Surface* loadSurface(char* path, Engine* e);

int main()
{
    Engine gameEngine;
    // Start up SDL and create window
    if (!initGame(&gameEngine)) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!loadMedia(&gameEngine)) {
            printf("Failed to load media!\n");
        } else {
            // Event handler
            SDL_Event e;

            // While application is running
            while (!gameEngine.mQuit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        gameEngine.mQuit = true;
                    }
                    // User presses a key
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                        case SDLK_SPACE:
                            birdJump(&gameEngine.bird);
                            break;
                        }
                    } else if (e.type == SDL_KEYUP) {
                        switch (e.key.keysym.sym) {
                        case SDLK_SPACE:
                            gameEngine.bird.mJumped = false;
                            break;
                        }
                    }
                }
                // Update part
                updateGame(&gameEngine);

                // Render part
                renderFrame(&gameEngine);
            }
        }
    }
    // Free resources and close SDL
    closeGame(&gameEngine);

    return 0;
}
void updateGame(Engine* e)
{
    // Calculate delta time
    e->mTimeLast = e->mTimeNow;
    e->mTimeNow = SDL_GetPerformanceCounter();
    double deltaTime = ((e->mTimeNow - e->mTimeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;
    // Update bird
    birdUpdate(&e->bird, deltaTime);
}

void renderFrame(Engine* e)
{
    SDL_FillRect(e->gScreenSurface, NULL, 0x000000);
    SDL_BlitScaled(e->bird.mSprite, NULL, e->gScreenSurface, &e->bird.mBounds);
    // SDL_BlitSurface(e->pipe.mSprite, NULL, e->gScreenSurface, e->pipe.mBounds);

    // Update the surface
    SDL_UpdateWindowSurface(e->gWindow);
}

bool initGame(Engine* e)
{
    e->mQuit = false;
    e->mTimeLast = 0;
    e->mTimeNow = SDL_GetPerformanceCounter();
    birdConstruct(&e->bird);
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        e->gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (e->gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            e->gScreenSurface = SDL_GetWindowSurface(e->gWindow);
        }
    }
    return success;
}

bool loadMedia(Engine* e)
{
    // Loading success flag
    bool success = true;
    // Load bird image
    e->bird.mSprite = loadSurface("graphics/fbird.png", e);
    if (e->bird.mSprite == NULL) {
        success = false;
    }
    // //Load pipe image
    for (int i = 0; i < 5; i++) {
        e->pipes[i].mSpriteTop = loadSurface("graphics/pipeT.png", e);
        e->pipes[i].mSpriteBottom = loadSurface("graphics/pipeB.png", e);
        if (e->pipes[i].mSpriteTop == NULL || e->pipes[i].mSpriteBottom == NULL) {
            success = false;
        }
    }
    return success;
}

SDL_Surface* loadSurface(char* path, Engine* e)
{
    // The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path,
            IMG_GetError());
    } else {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, e->gScreenSurface->format, NULL);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path,
                SDL_GetError());
        }
        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

void closeGame(Engine* e)
{
    // Deallocate surface
    SDL_FreeSurface(e->bird.mSprite);
    e->bird.mSprite = NULL;
    // SDL_FreeSurface(e->mPipe);
    // e->mPipe = NULL;

    // Destroy window
    SDL_DestroyWindow(e->gWindow);
    e->gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}
