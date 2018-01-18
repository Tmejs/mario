#include "include\SDL.h"
#include "Block.h"
#include "Texture.h"
#include "Constants.h"
#include <cstdio>
#include "State.h"
#include "Mario.h"
#include "Collision.h"
#include "Game.h"
#include "Level.h"

Level::Level(Uint32 t, unsigned int w, Block ** bM, unsigned int bC)
{
	_time = t;
	_width = w;
	_blockMap = bM;
	_blockCount = bC;
	createLevelFloor();
}

Level::~Level()
{
	// Freeing each block
	for (int i = 0; i < _blockCount; i++)
	{
		delete _blockMap[i];
		_blockMap[i] = NULL;
	}

	// Freeing whole array
	delete[] _blockMap;

	// Free texture floor texture
	_floor.free();
}

Collision Level::isLevelCollided(SDL_Rect first)
{
	Collision collision;
	SDL_Rect second;
	second.w = BLOCK_WIDTH;
	second.h = BLOCK_HEIGHT;

	// Loop for checking colission with each block
	for (int i = 0; i < _blockCount; i++)
	{
		second.x = _blockMap[i]->posX();
		second.y = _blockMap[i]->posY();
		
		if (SDL_HasIntersection(&first, &second))
		{
			collision.x = second.x;
			collision.y = second.y;
			collision.c = true;			
		}
	}

	return collision;
}

void Level::createLevelFloor()
{
	// Creates new Texture and SDL_Texture with given width
	_floor.newTexture(_width, SCREEN_HEIGHT);

	if (!_floor.isLoaded())
	{
		printf("Unable to create floor texture");
	}
	else
	{
		// Starts rendering on this texture
		_floor.renderOnTexture();

		// Sets lightblue as background
		SDL_SetRenderDrawColor(G::wRenderer, 20, 150, 255, 255);
		SDL_RenderClear(G::wRenderer);

		// Loop for rendering each block to level texture
		for (int i = 0; i < _blockCount; i++)
		{
			// Render depending on block type
			if (_blockMap[i]->whichType() == "Casual" )
			{
				G::spriteSheet.render(_blockMap[i]->posX(),
					_blockMap[i]->posY() + SKY, SDL_FLIP_NONE, &SpritesRect::blockCasual);
			}
		}
		// Render level ending flag
		G::spriteSheet.render(END_FLAG_POSITION_X, END_FLAG_POSITION_Y, SDL_FLIP_NONE, &SpritesRect::levelEndingFlag);
		
		// Set render back to window
		SDL_SetRenderTarget(G::wRenderer, NULL);
	}

}

Uint32 Level::time()
{
	return _time;
}

unsigned int Level::width()
{
	return _width;
}

unsigned int Level::blockCount()
{
	return _blockCount;
}

Block ** Level::blockMap()
{
	return _blockMap;
}

void Level::render()
{
	_floor.render(-S::offsetX, 0, SDL_FLIP_NONE, NULL);
}
