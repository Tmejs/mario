// PP_MARIO.cpp : Defines the entry point for the console application.
//
#include "include\SDL.h"
#include "State.h"
#include "Texture.h"
#include "Mario.h"
#include "Util.h"
#include "Input.h"
#include "Game.h"
#include <windows.h>
int main(int argc, char* argv[])
{
	if (G::init())
	{
		// End flag
		bool quit = false;

		// Game loop
		while (!quit)
		{
			
			// handleInput only returns true on ESC pressed 
			quit = I::handleInput();
			Sleep(20);
			// Update game state
			S::update();

			// Render those changes
			U::renderEverything();
		}
	}
	
    return 0;
}

