#ifndef MARIO_H
#define MARIO_H

#include "Collision.h"
#include "Direction.h"

// Movement constants (the higher the faster)
#define MARIO_X_AXIS_VELOCITY  2
#define MARIO_Y_AXIS_VELOCITY  30

#define RELATIVE_VELOCITY_Y_AXIS _velY / MARIO_GRAVITY

struct SDL_Rect;

class Mario
{
public:
	// Counts for each animation
	static const int STAND_ANIMATION_FRAMES = 1;
	static const int JUMP_ANIMATION_FRAMES = 1;
	static const int WALK_ANIMATION_FRAMES = 4;

	// The lower the faster
	static const int WALK_ANIMATION_SPEED = 6;

	// Movement constants (the higher the faster)
	static const int X_AXIS_VELOCITY = MARIO_X_AXIS_VELOCITY;
	static const int Y_AXIS_VELOCITY = MARIO_Y_AXIS_VELOCITY;

	// The higher the more slows Mario y axis velocity
	static const int MARIO_GRAVITY = 5;

	// SDL_Rect defining where specific frames are in the sprite sheet
	SDL_Rect frames[STAND_ANIMATION_FRAMES + WALK_ANIMATION_FRAMES + JUMP_ANIMATION_FRAMES];

	Mario();
	~Mario();

	// Utility functions
	void initFrames();
	void render();
	void update();
	void resetSpeed();

	// Returns SDL_Rect of current frame
	SDL_Rect currentFrame();

	// Handles walking movement and animation
	void walk();
	void animateWalk();

	// Handles jumping movement and animation
	void beginJump();
	void jump();
	void animateJump();
	
	// Handles animation when not moving
	void stand();

	void handleEvent(SDL_Event& );

	// Getters
	int posX();
	int posY();
	SDL_Rect getRect();

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
	bool _isJumping;
};


#endif // !MARIO_H


