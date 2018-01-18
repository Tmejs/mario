#include "include\SDL.h"
#include "Game.h"
#include "State.h"
#include "Mario.h"
#include "Texture.h"
#include "Constants.h"
#include "Level.h"
#include "Enemy.h"
#include <stdio.h>
#include "Util.h"

namespace U {

	// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
	// charset to bitmapa 128x128 zawierajπca znaki
	void drawString(SDL_Surface *screen, int x, int y, const char *text,
		SDL_Surface *charset) {
		int px, py, c;
		SDL_Rect s, d;
		s.w = 8;
		s.h = 8;
		d.w = 8;
		d.h = 8;
		while (*text) {
			c = *text & 255;
			px = (c % 16) * 8;
			py = (c / 16) * 8;
			s.x = px;
			s.y = py;
			d.x = x;
			d.y = y;
			SDL_BlitSurface(charset, &s, screen, &d);
			x += 8;
			text++;
		};
	}


	// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
	// (x, y) to punkt úrodka obrazka sprite na ekranie
	void drawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
		SDL_Rect dest;
		dest.x = x - sprite->w / 2;
		dest.y = y - sprite->h / 2;
		dest.w = sprite->w;
		dest.h = sprite->h;
		SDL_BlitSurface(sprite, NULL, screen, &dest);
	}


	// rysowanie pojedynczego pixela
	void drawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		*(Uint32 *)p = color;
	}


	// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
	// bπdü poziomie (gdy dx = 1, dy = 0)
	void drawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
		for (int i = 0; i < l; i++) {
			drawPixel(screen, x, y, color);
			x += dx;
			y += dy;
		};
	}


	// rysowanie prostokπta o d≥ugoúci bokÛw l i k
	void drawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
		Uint32 outlineColor, Uint32 fillColor) {
		int i;
		drawLine(screen, x, y, k, 0, 1, outlineColor);
		drawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
		drawLine(screen, x, y, l, 1, 0, outlineColor);
		drawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
		for (i = y + 1; i < y + k - 1; i++)
			drawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	}

	void drawString(Texture* target, int x, int y, const char * text)
	{
		target->renderOnTexture();

		int px, py, c;
		SDL_Rect s;
		s.w = 8;
		s.h = 8;
		while (*text) 
		{
			c = *text & 255;
			px = (c % 16) * 8;
			py = (c / 16) * 8;
			s.x = px;
			s.y = py;
			G::charset.render(x, y, SDL_FLIP_NONE, &s);
			x += 8;
			text++;
		}

		// Set render back to window
		SDL_SetRenderTarget(G::wRenderer, NULL);
	}

	void renderEverything()
	{


		if (S::currentView == GAME)
		{
			// Restarts previous view
			SDL_SetRenderDrawColor(G::wRenderer, 20, 150, 255, 255);
			SDL_RenderClear(G::wRenderer);

			// Render z-index manegement
			S::level->render();
			renderEnemies();
			S::mario.render();
			G::header.render();
		}
		else if (S::currentView == MENU)
		{

		}
		else if (S::currentView == GAME_OVER)
		{
			// Restarts previous view
			SDL_SetRenderDrawColor(G::wRenderer, 255, 255, 255, 255);
			SDL_RenderClear(G::wRenderer);

			// Render positioning
			SDL_Rect window;
			window.x = 0;
			window.y = 0;
			window.w = SCREEN_WIDTH;
			window.h = SCREEN_HEIGHT;

			G::gameOver.render(0, 0, SDL_FLIP_NONE, &window);
		}



		// Render everything on window
		SDL_RenderPresent(G::wRenderer);
	}

	void renderEnemies()
	{
		for (int i = 0; i < S::enemiesCount; i++)
		{
			if(S::enemies[i]->isAlive()) S::enemies[i]->render();
		}
	}




}