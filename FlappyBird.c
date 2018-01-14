#include "FlappyBird.h"

int main(int argc, char* args[])
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
            while (gameEngine.mState != QUITTING) {
                // Handle events on queue
                handleInput(&gameEngine, &e);
                
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
