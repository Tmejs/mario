#include "include/SDL.h"
#include "Texture.h"
#include <stdio.h>
#include "Constants.h"
#include "Mario.h"
#include "Level.h"
#include "Util.h"
#include "Game.h"
#include "Enemy.h"
#include "State.h"
#include "Collision.h"

namespace S {
	Mario mario;
	Enemy** enemies = NULL;
	int enemiesCount = 0;
	Level* level = NULL;
	Uint32 startTime = 0, coinsCount = 0, whichLevel = 1, livesLeft = 3;
	int offsetX = 0;
	View currentView = MENU;

	void update()
	{
		updateEnemies();
		mario.update();
		updateLevelPosition();
		updateHeader();

		// Time end check
		if (TIME_LEFT == 0) 
		{
			S::mario.resetSpeed();
			loseLife();
		}
		if (LEVEL_PASSED)
		{
			S::mario.resetSpeed();
			G::nextLevel();
		}
	}

	void updateHeader()
	{
		// Create new texture
		G::header.newTexture(HEADER_WIDTH, HEADER_HEIGHT);

		if (!G::header.isLoaded())
		{
			printf("Unable to create header texture");
		}
		else
		{
			// Restarts current texture
			G::header.renderOnTexture();
			SDL_SetRenderDrawColor(G::wRenderer, 0, 0, 0, 255);
			SDL_RenderClear(G::wRenderer);

			// Time handling
			Uint32 time = TIME_LEFT;
			char timeString[TIME_MAX_DIGITS + 1];
			SDL_uitoa(time, timeString, 10);

			// Coin count handling
			char coinsString[COINS_MAX_DIGITS + 1];
			SDL_uitoa(S::coinsCount, coinsString, 10);

			// Lives handling 
			char livesString[2];
			SDL_uitoa(S::livesLeft, livesString, 10);

			// Level handling
			char levelString[LEVEL_MAX_DIGITS + 1];
			SDL_uitoa(S::whichLevel, levelString, 10);

			// Draw current state info
			U::drawString(&G::header, HEADER_TIME_X, HEADER_TIME_Y, "Time:");
			U::drawString(&G::header, HEADER_TIME_X + HEADER_TIME_W, HEADER_TIME_Y, timeString);

			U::drawString(&G::header, HEADER_COINS_X, HEADER_COINS_Y, "Coins:");
			U::drawString(&G::header, HEADER_COINS_X + HEADER_COINS_W, HEADER_COINS_Y, coinsString);

			U::drawString(&G::header, HEADER_LIVES_X, HEADER_LIVES_Y, "Lives:");
			U::drawString(&G::header, HEADER_LIVES_X + HEADER_LIVES_W, HEADER_LIVES_Y, livesString);

			U::drawString(&G::header, HEADER_LEVEL_X, HEADER_LEVEL_Y, "Level:");
			U::drawString(&G::header, HEADER_LEVEL_X + HEADER_LEVEL_W, HEADER_LEVEL_Y, levelString);
		}
	}

	void updateLevelPosition()
	{
		if (mario.posX() >= OFFSET_CHANGE_START && offsetX + SCREEN_WIDTH < S::level->width())
		{
			offsetX += OFFSET_CHANGE_SPEED;
		}
	}

	void updateEnemies()
	{
		for (int i = 0; i < enemiesCount; i++)
		{
			enemies[i]->update();
		}
	}

	void loseLife()
	{
		livesLeft--;
		if (livesLeft)
		{
			G::restartLevel();
		}
		else
		{
			livesLeft = 3;
			S::currentView = GAME_OVER;
		}
	}

	Collision isEnemyCollided()
	{
		Collision collision;
		for (int i = 0; i < enemiesCount; i++)
		{
			if (S::enemies[i]->isAlive())
			{
				collision = enemies[i]->collisionCheck();
				if (collision.c) return collision;
			}
		}
		return collision;
	}
	void killEnemy()
	{
		Collision collision;
		for (int i = 0; i < enemiesCount; i++)
		{
			if (S::enemies[i]->isAlive())
			{
				collision = enemies[i]->collisionCheck();
				if (collision.c) enemies[i]->kill();
			}
		}
	}
}
