#ifndef GAME_H
#define GAME_H
class Texture;

namespace G
{

	extern SDL_Window* window;
	extern SDL_Renderer* wRenderer;
	extern Texture spriteSheet, charset, header, gameOver;

	extern bool init();
	extern bool initWindow();
	extern bool loadGraphics();

	// Free memory and ends game
	extern void exit();

	// Loads level from file
	extern bool loadLevel(int which);
	extern void nextLevel();
	extern void restartLevel();
	extern void newGame();

	extern void saveState();


};

struct SDL_Rect;
namespace SpritesRect {
	extern SDL_Rect blockCasual, levelEndingFlag;

	extern void init();
};

#endif // !GAME_H



