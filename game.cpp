#include "include\SDL.h"
#include <cstdio>
#include "State.h"
#include "Constants.h"
#include "Texture.h"
#include "Mario.h"
#include "Level.h"
#include "Block.h"
#include "Enemy.h"
#include "Game.h"

#define FILE_HEADERS 4
#define FILE_LEVEL_BEGIN FILE_HEADERS + 2

#define MAX_PATH_LETTERS 40

namespace G 
{
	// Window variables
	SDL_Window* window = NULL;
	SDL_Renderer* wRenderer = NULL;

	// Texture with graphics for game
	Texture spriteSheet, charset, gameOver;

	// Texture with state information: time, lives, current level
	Texture header;
	
	bool init()
	{
		// Success flag
		bool success = true;

		// SDL initialization
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			printf("SDL_Init error: %s\n", SDL_GetError());
			success = false;
		}
		else 
		{
			// Initialize game window
			if (!initWindow()) success = false;

			// Check if graphics loads properly
			else if (!loadGraphics()) success = false;

			// Everything successfuly loaded and initiated
			else newGame();	
		}

		return success;
	}

	bool initWindow()
	{
		bool success = true;

		// Creating game window
		window = SDL_CreateWindow("Super Mario Bros.", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Creation check
		if (window == NULL)
		{
			printf("Window Create error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Creating renderer for game window
			wRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			// Creation check
			if (wRenderer == NULL)
			{
				printf("Renderer: %s", SDL_GetError());
				success = false;
			}
		}

		return success;
	}

	bool loadGraphics()
	{
		bool success = true;

		if (!spriteSheet.load("img/Mario.bmp")) success = false;
		if (!charset.load("img/cs8x8.bmp")) success = false;
		if (!gameOver.load("img/Over.bmp")) success = false;

		// Initiate SDL_Rect for each sprite
		SpritesRect::init();

		return success;
	}

	void exit()
	{
		// Freeing memmory via SDL functions
		SDL_DestroyRenderer(G::wRenderer);
		G::wRenderer = NULL;

		SDL_DestroyWindow(G::window);
		G::window = NULL;

		SDL_Quit();
	}

	bool loadLevel(int which)
	{
		bool success = true;

		// Formats filePath to represent path to given level
		char filePath[MAX_PATH_LETTERS];
		sprintf(filePath, "levels/%d.txt", which);

		// Opens local file at given path
		FILE* file;
		file = fopen(filePath, "r");

		// Represents number of different block within level
		unsigned int blockCount = 0;
		Uint32 time;
		unsigned int width;
		int marioX, marioY;

		// Deleting enemies array
		if (S::enemiesCount > 0)
		{
			for (int i = 0; i < S::enemiesCount; i++)
			{
				delete S::enemies[i];
			}
			delete S::enemies;
		}


		// Reset state
		S::coinsCount = 0;
		S::enemiesCount = 0;
		S::whichLevel = which;
		S::offsetX = 0;

		// File presence check
		if (file == NULL)
		{
			success = false;
		}
		else
		{
			// Retrive level width, Mario position, time for level completion
			fscanf(file, "%u %d %d %u ", &width, &marioX, &marioY, &time);
			
			// Extend level with additional blocks
			width += LEVEL_ENDING_BLOCKS;

			// Skip unnecessary line only for file editing ( + '\n' + '\0' )
			char* formatLine = new char[width + 2];
			fgets(formatLine, width + 2, file);
			delete[] formatLine;

			// String representing each line in level
			char* levelLine[LEVEL_HEIGHT];

			// Loop main puropse - count all blocks
			for (int i = 0; i < LEVEL_HEIGHT; i++)
			{
				// Create individual line string
				levelLine[i] = new char[width + 1];

				// Insert whole line into levelLine buffer with additional '\0' character
				fgets(levelLine[i], width+1, file);

				// Count all blocks within file
				for (int j = 0; j < SDL_strlen(levelLine[i])  ; j++)
				{
					if (levelLine[i][j] == 'E') S::enemiesCount++;
					else if (levelLine[i][j] != ' ' && levelLine[i][j] != '\n') blockCount++;
				}
			}
			
			Block** levelBlocks = new Block*[blockCount + LEVEL_ENDING_BLOCKS];
			S::enemies = new Enemy*[S::enemiesCount];
			unsigned int k = 0, l = 0;

			// Loop main purpose - create blocks
			for (unsigned int i = 0; i < LEVEL_HEIGHT; i++)
			{
				for (unsigned int j = 0; j < SDL_strlen(levelLine[i]); j++)
				{
					// Create specific blocks
					if (levelLine[i][j] == '#')
					{
						Block* casual = new Casual(j * BLOCK_WIDTH, i* BLOCK_HEIGHT);
						levelBlocks[k] = casual;
						k++;
					}
					else if (levelLine[i][j] == 'E')
					{
						Enemy* enemy = new Enemy(j * BLOCK_WIDTH, i* BLOCK_HEIGHT);
						S::enemies[l] = enemy;
						l++;
					}
				}
			}

			// Adding level ending
			for (unsigned int i = 1; i <= LEVEL_ENDING_BLOCKS; i++)
			{
				Block* casual = new Casual((width - i) * BLOCK_WIDTH, (LEVEL_HEIGHT - 1)* BLOCK_HEIGHT);
				levelBlocks[k] = casual;
				k++;
			}

			// Free previous level and set new one to current state
			if (S::level != NULL) delete S::level;
			S::level = new Level(time, width * BLOCK_WIDTH, levelBlocks, blockCount + LEVEL_ENDING_BLOCKS);

			// Freeing each line
			for (int i = 0; i < LEVEL_HEIGHT; i++)
			{
				delete levelLine[i];
			}

			// Set Mario starting position
			S::mario.posX(marioX * BLOCK_WIDTH);
			S::mario.posY(marioY * BLOCK_HEIGHT);

			// Reset timer
			S::startTime = SDL_GetTicks();

			// End reading
			fclose(file);
		}
		return success;
	}

	void nextLevel()
	{
		if (!loadLevel(S::whichLevel + 1))
		{
			// TODO display menu
			S::currentView = GAME_OVER;
		}
	}

	void restartLevel()
	{
		if (!loadLevel(S::whichLevel))
		{
			printf("Something went wrong with restarting a level");
		}
	}

	void newGame()
	{
		if (!loadLevel(1))
		{
			printf("Unable to load file");
		}

		// Restart state
		S::livesLeft = 3;
		S::currentView = GAME;
	}

	void saveState()
	{
		// Opens local file at given path
		FILE* file;
		file = fopen("save.txt", "w");

		// File presence check
		if (file == NULL)
		{
			printf("Failed to save state. File opening");
		}
		else
		{

		}
	}
}

namespace SpritesRect {
	SDL_Rect blockCasual, levelEndingFlag;

	// Set sprites posiiton within spritesheet
	void init()
	{
		blockCasual.x = 373;
		blockCasual.y = 124;
		blockCasual.w = 16;
		blockCasual.h = 16;

		levelEndingFlag.x = 260;
		levelEndingFlag.y = 46;
		levelEndingFlag.w = 24;
		levelEndingFlag.h = 168;

	}
}
