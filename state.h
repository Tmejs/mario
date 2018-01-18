#ifndef STATE_H
#define STATE_H

#include "Collision.h";



struct SDL_Window;
struct SDL_Renderer;
class Texture;
class Enemy;
class Mario;
class Level;
typedef enum view {
	GAME,
	MENU,
	GAME_OVER
} View;

namespace S {
	//extern unsigned short hp;
	//extern unsigned short time;
	//extern unsigned int viewX;
	//extern bool isPlaying;

	extern Enemy** enemies;
	extern int enemiesCount;
	extern Mario mario;
	extern Level* level;
	extern Uint32 startTime, coinsCount, whichLevel, livesLeft;
	extern int offsetX;
	extern View currentView;

	extern void update();
	extern void updateHeader();
	extern void updateLevelPosition();
	extern void updateEnemies();
	extern void loseLife();
	extern Collision isEnemyCollided();
	extern void killEnemy();
}

#endif // !STATE_H


