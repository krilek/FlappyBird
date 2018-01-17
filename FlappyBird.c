#include "FlappyBird.h"

int main(int argc, char* args[])
{
    Engine gameEngine;
    if (argc > 1) {
        if (strcmp(args[1], "-h") == 0) {
            printHelp();
            return 0;
        }
        if (strcmp(args[1], "-n") == 0) {
            if (argc > 2) {
                if (strlen(args[2]) < MAX_NICKNAME_LENGTH) {
                    strcpy(gameEngine.score.mPlayerName, args[2]);
                }
            } else {
                printf("You must specify nickname");
            }
        }
    } else {
        printHelp();
        return 0;
    }
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
            //Before closing game upload score to server
            if (gameEngine.score.mScoreSaved == false) {
                scoreSaveToAFile(&gameEngine.score, gameEngine.score.mCachedScores);
            }
        }
    }
    //Upload scores before closing game
    uploadScoreToServer(&gameEngine.score);
    // Free resources and close SDL
    closeGame(&gameEngine);

    return 0;
}

void printHelp()
{
    printf("==========================\n");
    printf("  Flappy Bird created by  \n");
    printf("          Krilek          \n");
    printf("  To start game:          \n");
    printf("  Use parameter -n nick   \n");
    printf("  For example:            \n");
    printf("  flappyBird -n Krilek    \n");
    printf("  To print help use -h    \n");
    printf("==========================\n");
}