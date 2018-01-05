#include "Engine.h"
void construct(Engine *game){
    game->mWindow = NULL;
    game->mWindowSurface = NULL;
}
bool init(Engine *game)
{
	bool success = true;

	//Start SDL
	if( SDL_Init(SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		game->mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( game->mWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			game->mWindowSurface = SDL_GetWindowSurface( game->mWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	// //Load left surface
	// gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
	// if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	// {
	// 	printf( "Failed to load left image!\n" );
	// 	success = false;
	// }

	return success;
}

void close(Engine *game)
{
	//Deallocate surfaces
	// for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	// {
	// 	SDL_FreeSurface( gKeyPressSurfaces[ i ] );
	// 	gKeyPressSurfaces[ i ] = NULL;
	// }

	//Destroy window
	SDL_DestroyWindow( game->mWindow );
	game->mWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}