#include "Bird.h"
#include "Engine.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//Loads individual image
SDL_Surface* loadSurface(char* path);

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    //Quit SDL
    SDL_Quit();
    construct(gPtr);
    //Start up SDL and create window
    if (!init(gPtr)) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;
            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN) {
                        //Select surfaces based on key press
                        // switch( e.key.keysym.sym )
                        // {

                        // 	// case SDLK_UP:
                        // 	// gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                        // 	// break;

                        // 	// case SDLK_DOWN:
                        // 	// gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                        // 	// break;

                        // 	// case SDLK_LEFT:
                        // 	// gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                        // 	// break;

                        // 	// case SDLK_RIGHT:
                        // 	// gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        // 	// break;

                        // 	// default:
                        // 	// gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                        // 	// break;
                        // }
                    }
                }

                //Apply the current image
                // SDL_BlitSurface( gCurrentSurface, NULL, game->mWindowSurface, NULL );

                //Update the surface
                SDL_UpdateWindowSurface(g.mWindowSurface);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

SDL_Surface* loadSurface(char* path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }

    return loadedSurface;
}
