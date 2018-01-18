#ifndef UTIL_H
#define UTIL_H

struct SDL_Surface;
class Texture;
namespace U {

	// Funkcje z szablonu
	extern void drawString(SDL_Surface *, int, int, const char *, SDL_Surface *);
	extern void drawSurface(SDL_Surface *, SDL_Surface *, int x, int y);
	extern void drawPixel(SDL_Surface *, int, int, Uint32);
	extern void drawLine(SDL_Surface *, int, int, int, int, int, Uint32);
	extern void drawRectangle(SDL_Surface *, int, int, int, int, Uint32, Uint32);

	extern void drawString(Texture* target, int x, int y, const char* text);

	extern void renderEverything();
	extern void renderEnemies();

}

#endif // !UTIL_H

