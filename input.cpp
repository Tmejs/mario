#include "include\SDL.h"
#include "State.h"
#include "Util.h"
#include "Mario.h"
#include "Game.h"
#include "Input.h"


// Main program input loop
bool I::handleInput()
{
	bool quit = false;
	// Event handler
	SDL_Event e;

	// Event management
	while (SDL_PollEvent(&e) != 0)
	{
		// Exit game on ESC pressed
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}

		if (e.type == SDL_KEYDOWN)
		{
			// Mario steering keys
			if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT || (e.key.keysym.sym == SDLK_UP)))
			{
				S::mario.handleEvent(e);
			}

			// New game key
			if (e.key.keysym.sym == SDLK_n)
			{
				G::newGame();
			}

			// Save game key
			if (e.key.keysym.sym == SDLK_s)
			{
				if(S::currentView == GAME)	G::saveState();
			}
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			// Mario steering keys
			if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT || (e.key.keysym.sym == SDLK_UP)))
			{	
				S::mario.handleEvent(e);
			}
		}
	}

	return quit;
}
