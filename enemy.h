#ifndef ENEMY_H
#define ENEMY_H
#include "Collision.h"
#include "Direction.h"

// Movement constants (the higher the faster)
#define ENEMY_X_AXIS_VELOCITY  1
#define ENEMY_Y_AXIS_VELOCITY  30

#define RELATIVE_ENEMY_VELOCITY_Y_AXIS _velY / ENEMY_GRAVITY

struct SDL_Rect;

class Enemy
{
public:
	// Counts for each animation
	static const int WALK_ANIMATION_FRAMES = 2;
	static const int DEATH_ANIMATION_FRAMES = 1;

	// The lower the faster
	static const int WALK_ANIMATION_SPEED = 6;

	// Movement constants (the higher the faster)
	static const int X_AXIS_VELOCITY = ENEMY_X_AXIS_VELOCITY;
	static const int Y_AXIS_VELOCITY = ENEMY_Y_AXIS_VELOCITY;

	// The higher the more slows Mario y axis velocity
	static const int ENEMY_GRAVITY = 5;

	// SDL_Rect defining where specific frames are in the sprite sheet
	SDL_Rect frames[WALK_ANIMATION_FRAMES + DEATH_ANIMATION_FRAMES];

	Enemy(int x, int y);
	~Enemy();

	// Utility functions
	void initFrames();
	void render();
	void update();
	Collision collisionCheck();

	// Returns SDL_Rect of current frame
	SDL_Rect currentFrame();

	// Handles walking movement and animation
	void walk();
	void animateWalk();

	// Handles jumping movement and animation
	void jump();
	void animateJump();

	void kill();

	// Getters
	int posX();
	int posY();
	SDL_Rect getRect();
	bool isAlive();

	// Setters
	void posX(int);
	void posY(int);
private:
	Collision _collisionInfo;
	Direction _lastDirection;
	int _currentFrame;
	int _posX;
	int _posY;
	int _velX;
	int _velY;
	unsigned int _animationCount;
	bool _isAlive;
};


#endif // !ENEMY_H

